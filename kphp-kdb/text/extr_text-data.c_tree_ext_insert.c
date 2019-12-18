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
struct TYPE_9__ {int y; int x; struct TYPE_9__* right; struct TYPE_9__* left; } ;
typedef  TYPE_1__ tree_ext_t ;

/* Variables and functions */
 TYPE_1__* new_tree_ext_node (int,int,int) ; 
 int /*<<< orphan*/  tree_ext_relax (TYPE_1__*) ; 
 int /*<<< orphan*/  tree_ext_split (TYPE_1__**,TYPE_1__**,TYPE_1__*,int) ; 

__attribute__((used)) static tree_ext_t *tree_ext_insert (tree_ext_t *T, int x, int y, int rpos) {
  tree_ext_t *P;
  if (T->y > y) {
    if (x < T->x) {
      T->left = tree_ext_insert (T->left, x, y, rpos);
    } else {
      T->right = tree_ext_insert (T->right, x, y, rpos);
    }
    tree_ext_relax (T);
    return T;
  }
  P = new_tree_ext_node (x, y, rpos);
  tree_ext_split (&P->left, &P->right, T, x);
  tree_ext_relax (P);
  return P;
}