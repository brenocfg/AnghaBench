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
struct TYPE_5__ {unsigned int block_offset; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ filesys_tree_t ;

/* Variables and functions */

__attribute__((used)) static void tree_split (filesys_tree_t **L, filesys_tree_t **R, filesys_tree_t *T, unsigned int block_offset) {
  if (!T) {
    *L = *R = NULL;
    return;
  }
  if (block_offset < T->block_offset) {
    *R = T;
    tree_split (L, &T->left, T->left, block_offset);
  } else {
    *L = T;
    tree_split (&T->right, R, T->right, block_offset);
  }
}