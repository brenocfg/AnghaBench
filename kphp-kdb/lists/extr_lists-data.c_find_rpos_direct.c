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
typedef  int /*<<< orphan*/  object_id_t ;
struct TYPE_3__ {int N; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ listree_direct_t ;

/* Variables and functions */
 int /*<<< orphan*/  OARR_ENTRY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ object_id_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_rpos_direct (listree_direct_t *LD, object_id_t object_id) {
  int l = -1, r = LD->N, x;

  /* A[N-i-1]<x<=A[N-i] means A[l] < x <= A[r]; i = N - r */
  while (r - l > 1) {
    x = (l + r) / 2;
    if (object_id_compare (object_id, OARR_ENTRY (LD->A, x)) <= 0) {
      r = x;
    } else {
      l = x;
    }
  }
  assert (r >= 0 && r <= LD->N);
  return LD->N - r;
}