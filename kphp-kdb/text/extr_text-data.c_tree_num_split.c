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
struct TYPE_7__ {int x; struct TYPE_7__* right; struct TYPE_7__* left; } ;
typedef  TYPE_1__ tree_num_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  tree_num_relax (TYPE_1__*) ; 

__attribute__((used)) static void tree_num_split (tree_num_t **L, tree_num_t **R, tree_num_t *T, int x) {
  if (T == NIL) { *L = *R = NIL; return; }
  if (T->x >= x) {
    *R = T;
    tree_num_split (L, &T->left, T->left, x);
  } else {
    *L = T;
    tree_num_split (&T->right, R, T->right, x);
  }
  tree_num_relax (T);
}