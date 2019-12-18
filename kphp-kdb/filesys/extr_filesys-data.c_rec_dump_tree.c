#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int block_offset; int block_length; struct TYPE_3__* right; struct TYPE_3__* left; } ;
typedef  TYPE_1__ filesys_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void rec_dump_tree (filesys_tree_t *T, int depth) {
  if (T != NULL) {
    fprintf (stderr, "[%d] [%u, %u)\n", depth, T->block_offset, T->block_offset + T->block_length);
    rec_dump_tree (T->left, depth + 1);
    rec_dump_tree (T->right, depth + 1);
  }
}