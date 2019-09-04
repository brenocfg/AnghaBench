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
typedef  int /*<<< orphan*/  tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int tree_merge_array (int /*<<< orphan*/ *,int*,int,int**,int*,int,int /*<<< orphan*/ ) ; 

int tree_merge_arr (tree_t *T, int *a1, int l1, int **a2, int *l2, int cur_day) {
  int r = tree_merge_array (T, a1, l1, a2, l2, cur_day, 0);
  while (*l2) {
    assert (r < l1);
    a1[2 * r + 0] = (*a2)[0];
    a1[2 * r + 1] = (*a2)[1];
    (*l2)--;
    (*a2)+=2;
    r++;
  }
  return r;
}