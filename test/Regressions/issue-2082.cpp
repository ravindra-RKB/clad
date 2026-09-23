// RUN: %clang_cc1 -verify -plugin clad -fplugin-arg-clad-warn-unused %s

#include "clad/Differentiator/Differentiator.h"

struct Ref {
  // expected-note@+1 2 {{reference member 'a' declared here}}
  double& a;
};

double f(double x) {
  // expected-error@+1 {{parameter or variable 'r' has unsupported reference data member}}
  Ref r{x};
  return r.a * 2.0;
}

// expected-error@+1 {{parameter or variable 'r' has unsupported reference data member}}
double g(Ref r) {
  return r.a * 2.0;
}

void test() {
  // expected-error@+1 {{cannot differentiate}}
  auto df = clad::gradient(f);
  // expected-error@+1 {{cannot differentiate}}
  auto dg = clad::gradient(g);
}
