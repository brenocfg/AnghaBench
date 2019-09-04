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
struct TYPE_5__ {unsigned int block_offset; scalar_t__ y; struct TYPE_5__* left; struct TYPE_5__* right; } ;
typedef  TYPE_1__ filesys_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_tree_node (TYPE_1__*) ; 

__attribute__((used)) static filesys_tree_t *tree_delete (filesys_tree_t *T, unsigned int block_offset) {
  filesys_tree_t *Root = T, **U = &Root, *L, *R;
  while (block_offset != T->block_offset) {
    U = (block_offset < T->block_offset) ? &T->left : &T->right;
    T = *U;
    if (!T) { return Root; }
  }

  L = T->left;
  R = T->right;
  free_tree_node (T);
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