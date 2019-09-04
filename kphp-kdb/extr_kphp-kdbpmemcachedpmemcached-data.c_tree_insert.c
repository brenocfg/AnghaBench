#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int y; struct TYPE_8__* right; struct TYPE_8__* left; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_t ;
typedef  int /*<<< orphan*/  hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* new_tree_node (int /*<<< orphan*/ *,int) ; 
 int node_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_split (TYPE_1__**,TYPE_1__**,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree_t *tree_insert (tree_t *T, hash_entry_t *x, int y) {
  tree_t *P;
  if (!T) { 
    P = new_tree_node (x, y);
    return P;
  }
  int c;
  assert (c = node_cmp (x, T->x));
  if (T->y >= y) {
    if (c < 0) {
      T->left = tree_insert (T->left, x, y);
    } else {
      T->right = tree_insert (T->right, x, y);
    }
    return T;
  }
  P = new_tree_node (x, y);
  tree_split (&P->left, &P->right, T, x);
  return P;
}