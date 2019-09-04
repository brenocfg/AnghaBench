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
struct TYPE_5__ {long long x; int size; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */

__attribute__((used)) static void tree_split (tree_t **L, tree_t **R, tree_t *T, long long x) {
  if (!T) { *L = *R = 0; return; }
  if (x < T->x) {
    *R = T;
    tree_split (L, &T->left, T->left, x);
  } else {
    *L = T;
    tree_split (&T->right, R, T->right, x);
  }
  T->size = 1 + (T->left ? T->left->size : 0) + (T->right ? T->right->size : 0);
}