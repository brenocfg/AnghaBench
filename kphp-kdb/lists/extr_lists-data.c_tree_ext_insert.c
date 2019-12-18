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
struct TYPE_9__ {int y; struct TYPE_9__* right; struct TYPE_9__* left; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_ext_small_t ;
typedef  int /*<<< orphan*/  object_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ object_id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ object_id_less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_ext_relax (TYPE_1__*) ; 
 int /*<<< orphan*/  tree_ext_split (TYPE_1__**,TYPE_1__**,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree_ext_small_t *tree_ext_insert (tree_ext_small_t *T, object_id_t x, int y, tree_ext_small_t *N) {
  if (T->y > y) {
    if (object_id_less (x, T->x)) {
      T->left = tree_ext_insert (T->left, x, y, N);
    } else {
//    assert (x > T->x);
      T->right = tree_ext_insert (T->right, x, y, N);
    }
    tree_ext_relax (T);
    return T;
  }
  assert (object_id_equal (N->x, x) && N->y == y);
  tree_ext_split (&N->left, &N->right, T, x);
  tree_ext_relax (N);
  return N;
}