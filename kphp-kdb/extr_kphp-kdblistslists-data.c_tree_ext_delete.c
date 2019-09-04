#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* right; struct TYPE_10__* left; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_ext_small_t ;
typedef  int /*<<< orphan*/  object_id_t ;

/* Variables and functions */
 TYPE_1__* DeletedSubnode ; 
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  assert (int) ; 
 int object_id_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tree_ext_merge (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  tree_ext_relax (TYPE_1__*) ; 

__attribute__((used)) static tree_ext_small_t *tree_ext_delete (tree_ext_small_t *T, object_id_t x) {
  assert (T != NIL);
  int p = object_id_compare (x, T->x);
  if (!p) {
    tree_ext_small_t *N = tree_ext_merge (T->left, T->right);
    DeletedSubnode = T;
    return N;
  }
  if (p < 0) {
    T->left = tree_ext_delete (T->left, x);
  } else {
    T->right = tree_ext_delete (T->right, x);
  }
  tree_ext_relax (T);
  return T;
}