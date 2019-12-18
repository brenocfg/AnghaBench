#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int N; struct TYPE_4__* left; int /*<<< orphan*/  z; int /*<<< orphan*/  x; struct TYPE_4__* right; } ;
typedef  TYPE_1__ tree_num_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 

int *tree_num_get_range_rev (tree_num_t *T, int *R, int from, int to) {
  if (T == NIL) {
    return R;
  }
  if (from <= T->right->N) {
    R = tree_num_get_range_rev (T->right, R, from, to);
  }
  from -= T->right->N + 1;
  to -= T->right->N + 1;
  if (to >= 0 && from <= 0) {
    *R++ = T->x;
    *R++ = T->z;
  }
  if (to > 0) {
    R = tree_num_get_range_rev (T->left, R, from, to);
  }
  return R;
}