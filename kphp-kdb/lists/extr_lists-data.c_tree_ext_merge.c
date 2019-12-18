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
typedef  TYPE_1__ tree_ext_small_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  tree_ext_relax (TYPE_1__*) ; 

__attribute__((used)) static tree_ext_small_t *tree_ext_merge (tree_ext_small_t *L, tree_ext_small_t *R) {
  if (L == NIL) { return R; }
  if (R == NIL) { return L; }
  if (L->y > R->y) {
    L->right = tree_ext_merge (L->right, R);
    tree_ext_relax (L);
    return L;
  } else {
    R->left = tree_ext_merge (L, R->left);
    tree_ext_relax (R);
    return R;
  }
}