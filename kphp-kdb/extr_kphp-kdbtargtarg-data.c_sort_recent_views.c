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

void sort_recent_views (long long *A, long B) {
  if (B <= 0) {
    return;
  }
  long i = 0, j = B;			       
  long long h = A[j >> 1], t;
  do {
    while (A[i] > h) {
      ++i;
    }
    while (h > A[j]) {
      --j;
    }
    if (i <= j) {
      t = A[i]; A[i] = A[j]; A[j] = t;
      ++i; --j;
    }
  } while (i <= j);
  sort_recent_views (A, j);
  sort_recent_views (A + i, B - i);
}