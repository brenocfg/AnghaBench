#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; struct TYPE_4__* left; struct TYPE_4__* right; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */

__attribute__((used)) static tree_t *tree_get (tree_t *T, int p) {
  if (!T) {
    return 0;
  }
  if (T->left && p < T->left->size) {
    return tree_get (T->left, p);
  }
  if (p == (T->left ? T->left->size : 0)) {
    return T;
  }
  return tree_get (T->right, p - 1 - (T->left ? T->left->size : 0));
}