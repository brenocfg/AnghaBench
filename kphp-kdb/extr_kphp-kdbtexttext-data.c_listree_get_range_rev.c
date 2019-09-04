#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  delta; } ;
typedef  TYPE_1__ tree_ext_t ;
struct TYPE_6__ {int /*<<< orphan*/  N; int /*<<< orphan*/  A; TYPE_1__* root; } ;
typedef  TYPE_2__ listree_t ;

/* Variables and functions */
 int RA ; 
 scalar_t__ listree_get_range_rec_rev (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 

int listree_get_range_rev (listree_t *U, int k, int n) {
  tree_ext_t *T = U->root;
  int M = U->N + T->delta;
  n += k;
  if (k < 0) { 
    k = 0; 
  }
  if (n > M) {
    n = M;
  }
  if (n <= k) {
    return 0;
  }
  RA += n - k;
  if (listree_get_range_rec_rev (U->A, T, U->N, M - n, M - k - 1) < 0) {
    return -2;
  } else {
    RA += n - k;
    return n - k;
  }
}