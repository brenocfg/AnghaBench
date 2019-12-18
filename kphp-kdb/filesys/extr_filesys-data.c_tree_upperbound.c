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
struct TYPE_4__ {unsigned int block_offset; struct TYPE_4__* left; struct TYPE_4__* right; } ;
typedef  TYPE_1__ filesys_tree_t ;

/* Variables and functions */

__attribute__((used)) static filesys_tree_t *tree_upperbound (filesys_tree_t *T, unsigned int block_offset) {
  filesys_tree_t *R = NULL;
  while (T) {
    if (block_offset > T->block_offset) {
      R = T;
      T = T->right;
    } else if (block_offset < T->block_offset) {
      T = T->left;
    } else {
      return T;
    }
  }
  return R;
}