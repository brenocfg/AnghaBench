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

__attribute__((used)) static void heap_sift (long long *A, long N, long long x) {
  int i = 1, j;
  long long h = A[x], u;
  while (1) {
    j = (i << 1);
    if (j > N) { 
      break; 
    }
    u = A[(long) A[j]];
    if (j < N && A[(long) A[j+1]] < u) { 
      u = A[(long) A[++j]]; 
    }
    if (u >= h) { 
      break; 
    }
    A[i] = A[j];
    i = j;
  }
  A[i] = x;
}