#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int N; int* A; int last_A; } ;
typedef  TYPE_1__ listree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int find_rpos (listree_t *U, int local_id) {
  int l = -1, r = U->N, x;

  if (!U->A && local_id > U->last_A) {
    return 0;
  }
 
  if (!U->A && U->N) {
    return -2;
  }

  /* A[N-i-1]<x<=A[N-i] means A[l] < x <= A[r]; i = N - r */
  while (r - l > 1) {
    x = (l + r) / 2;
    if (local_id <= U->A[x]) {
      r = x;
    } else {
      l = x;
    }
  }
  assert (r >= 0 && r <= U->N);
  return U->N - r;
}