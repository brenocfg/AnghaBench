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
struct TYPE_3__ {int x; struct TYPE_3__* right; struct TYPE_3__* left; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int tree_merge_array (tree_t *T, int *a1, int l1, int **a2, int *l2, int cur_day, int r) {
  if (!T) {
    return r;
  }
  if (T->left) { assert (T->left->x < T->x); }
  if (T->right) { assert (T->right->x > T->x); }
  assert (*l2 >= 0);
  r = tree_merge_array (T->left, a1, l1, a2, l2, cur_day, r);
  //fprintf (stderr, "T->x = %d\n", T->x);
  while (*l2 && (*a2)[0] < T->x) {
    assert (r < l1);
    a1[2 * r + 0] = (*a2)[0];
    a1[2 * r + 1] = (*a2)[1];
    (*l2)--;
    (*a2)+=2;
    r++;
  }
  assert (r < l1);
  a1[2 * r + 0] = T->x;
  a1[2 * r + 1] = cur_day;
  r++;
  if (*l2 && (*a2)[0] == T->x) {
    (*l2)--;
    (*a2)+=2;
  }
  assert (!(*l2) || (*a2)[0] > T->x);
  return tree_merge_array (T->right, a1, l1, a2, l2, cur_day, r);
}