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
typedef  int /*<<< orphan*/  ltree_x_t ;
struct TYPE_5__ {scalar_t__ y; struct TYPE_5__* left; struct TYPE_5__* right; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ ltree_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_ltree_node (TYPE_1__*) ; 
 int ltree_x_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ltree_t *ltree_delete (ltree_t *T, ltree_x_t x) {
  if (!T) {
    return 0;
  }
  ltree_t *Root = T, **U = &Root, *L, *R;
  if (!T) {
    return 0;
  }

  int r;

  while ((r = ltree_x_compare (x, T->x)) != 0) {
    U = (r < 0) ? &T->left : &T->right;
    T = *U;
    if (!T) {
      return Root;
    }
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