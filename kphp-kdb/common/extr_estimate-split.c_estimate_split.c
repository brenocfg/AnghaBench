#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 double exp (int) ; 
 int log (int) ; 
 int sqrt (double) ; 

int estimate_split (int N, int K) {
  double x, a, tp, ta;
  int i;
  if (N <= 0 || K <= 0) {
    return 0;
  }
  if (K == 1) {
    return N;
  }
  if (N >= 100 && N >= 100*K) {	// if necessary, N/K >= 100 may be replaced by any value <= 500
    x = (double) N / K;
    return (int) (x + 7*sqrt(x) + 1);
  }
  a = exp (N*log (1 - 1.0/K));
  x = a;
  i = 0;
  tp = 1 - 1e-9/K;
  ta = 1e-9/K/N;
  while (x < tp && i < N && !(a < ta && i*K > N)) {
    a *= N-i;
    a /= (K-1)*++i;
    x += a;
  }
  return i;
}