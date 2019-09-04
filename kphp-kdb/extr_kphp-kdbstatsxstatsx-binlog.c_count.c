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
 int COUNTERS_PRIME ; 
 int* Counters ; 
 int* T ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  qsort_i (int /*<<< orphan*/ ,int) ; 

void count (void) {
  int i, n = 0;
  for (i = 0; i < COUNTERS_PRIME; i++) {
    if (Counters[i]) {
      Counters[n] = Counters[i];
      T[n] = T[i];
      n++;
    }
  }
  if (n > 0) {
    qsort_i (0, n - 1);
    for (i = n - 1; i >= 0 && i >= n - 100; i--) {
      printf ("%d\t%d\n", Counters[i], T[i]);
    }
  }
}