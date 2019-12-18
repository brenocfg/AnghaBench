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
struct TYPE_5__ {scalar_t__ x; scalar_t__ y; int size; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static tree_t *tree_merge (tree_t *L, tree_t *R) {
  if (!L) { return R; }
  if (!R) { return L; }
  assert (L->x < R->x);
  if (L->y > R->y) {
    L->right = tree_merge (L->right, R);
    L->size = 1 + (L->left ? L->left->size : 0) + (L->right ? L->right->size : 0);
    return L;
  } else {
    R->left = tree_merge (L, R->left);
    R->size = 1 + (R->left ? R->left->size : 0) + (R->right ? R->right->size : 0);
    return R;
  }
}