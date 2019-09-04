#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int y; scalar_t__ x; struct TYPE_9__* right; struct TYPE_9__* left; } ;
typedef  TYPE_1__ tree_ext_global_t ;
typedef  scalar_t__ global_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tree_ext_global_relax (TYPE_1__*) ; 
 int /*<<< orphan*/  tree_ext_global_split (TYPE_1__**,TYPE_1__**,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static tree_ext_global_t *tree_ext_global_insert (tree_ext_global_t *T, global_id_t x, int y, tree_ext_global_t *N) {
  if (T->y > y) {
    if (x < T->x) {
      T->left = tree_ext_global_insert (T->left, x, y, N);
    } else {
//    assert (x > T->x);
      T->right = tree_ext_global_insert (T->right, x, y, N);
    }
    tree_ext_global_relax (T);
    return T;
  }
  assert (N->x == x && N->y == y);
  tree_ext_global_split (&N->left, &N->right, T, x);
  tree_ext_global_relax (N);
  return N;
}