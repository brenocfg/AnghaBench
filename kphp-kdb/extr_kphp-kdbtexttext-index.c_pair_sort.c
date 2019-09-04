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
typedef  int /*<<< orphan*/  pair_t ;

/* Variables and functions */
 scalar_t__ pair_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pair_sort (pair_t *A, int b) {
  int i = 0, j = b;
  pair_t h, t;
  if (b <= 0) { return; }
  h = A[b >> 1];
  do {
    while (pair_cmp (&A[i], &h) < 0) { i++; }
    while (pair_cmp (&A[j], &h) > 0) { j--; }
    if (i <= j) {
      t = A[i];  A[i++] = A[j];  A[j--] = t;
    }
  } while (i <= j);
  pair_sort (A+i, b-i);
  pair_sort (A, j);
}