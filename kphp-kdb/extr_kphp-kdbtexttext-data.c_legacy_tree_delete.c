#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ y; struct TYPE_7__* left; struct TYPE_7__* right; } ;
typedef  TYPE_1__ ltree_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_ltree_node (TYPE_1__*) ; 
 int /*<<< orphan*/  legacy_tree_equal (TYPE_1__*,long long,int) ; 
 scalar_t__ legacy_tree_less (long long,int,TYPE_1__*) ; 

__attribute__((used)) static ltree_t *legacy_tree_delete (ltree_t *T, long long x, int z) {
  ltree_t *Root = T, **U = &Root, *L, *R;

  while (T && !legacy_tree_equal (T, x, z)) {
    U = legacy_tree_less (x, z, T) ? &T->left : &T->right;
    T = *U;
  }

  if (!T) {
    return Root;
  }

  L = T->left;
  R = T->right;
  free_ltree_node (T);

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