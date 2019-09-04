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
 int /*<<< orphan*/ ** C ; 
 int const lrand48 () ; 
 int max_port ; 
 int min_port ; 

int choose_random_tid (void) {
  const int n = max_port - min_port + 1;
  int tid = lrand48 () % n, steps = n;
  while (--steps >= 0) {
    if (C[min_port + tid] == NULL) {
      return min_port + tid;
    }
    tid = (tid + 1) % n;
  }
  return -1;
}