#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x; scalar_t__ y; struct TYPE_5__* left; struct TYPE_5__* right; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_tree_node (TYPE_1__*) ; 

__attribute__((used)) static tree_t *tree_delete (tree_t *T, int x) {
  tree_t *Root = T, **U = &Root, *L, *R;

  while (T && x != T->x) {
    U = (x < T->x) ? &T->left : &T->right;
    T = *U;
  }

  if (!T) {
    return Root;
  }

  L = T->left;
  R = T->right;
  free_tree_node (T);

  while (L && R) {
    if (L->y > R->y) {
      *U = L;
      U = &L->right;
      L = *U;
    } else {
      *U = R;
      U = &R->left;
      R = *U;
    }
  }

  *U = L ? L : R;

  return Root;
}