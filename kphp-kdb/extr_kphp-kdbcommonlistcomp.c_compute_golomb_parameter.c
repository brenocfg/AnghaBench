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
 int /*<<< orphan*/  assert (int) ; 
 int* golomb_crit ; 

__attribute__((used)) static int compute_golomb_parameter (int N, int K) {
  assert (K > 0 && K <= N);
  long long t = (long long) 2*5278688*N / K;
  if (t <= 165137325) {
    int i = 0;
    do {
      if ((int) t <= golomb_crit[i]) {
        return i + 1;
      }
    } while (++i <= 8);
    return 10;
  }
  return (int) ((t + (7615537-5278688)) / (2*7615537));
}