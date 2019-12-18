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
struct TYPE_7__ {struct TYPE_7__* right; struct TYPE_7__* left; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_ext_small_t ;
typedef  int /*<<< orphan*/  object_id_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 scalar_t__ object_id_less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_ext_relax (TYPE_1__*) ; 

__attribute__((used)) static void tree_ext_split (tree_ext_small_t **L, tree_ext_small_t **R, tree_ext_small_t *T, object_id_t x) {
  if (T == NIL) { *L = *R = NIL; return; }
  if (object_id_less (x, T->x)) {
    *R = T;
    tree_ext_split (L, &T->left, T->left, x);
  } else {
    *L = T;
    tree_ext_split (&T->right, R, T->right, x);
  }
  tree_ext_relax (T);
}