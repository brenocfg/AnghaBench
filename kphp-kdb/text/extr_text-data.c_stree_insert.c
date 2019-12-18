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
struct TYPE_5__ {int y; int x; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ stree_t ;

/* Variables and functions */
 TYPE_1__* new_stree_node (int,int) ; 

__attribute__((used)) static stree_t *stree_insert (stree_t *T, int x, int y) {
  stree_t *Root = T, **U = &Root, **L, **R;

  while (T && T->y <= y) {
    U = (x < T->x) ? &T->left : &T->right;
    T = *U;
  }

  *U = new_stree_node (x, y);


  L = &(*U)->left;
  R = &(*U)->right;

  while (T) {
    if (x < T->x) {
      *R = T;
      R = &T->left;
      T = *R;
    } else {
      *L = T;
      L = &T->right;
      T = *L;
    }
  }

  *L = *R = 0;

  return Root;
}