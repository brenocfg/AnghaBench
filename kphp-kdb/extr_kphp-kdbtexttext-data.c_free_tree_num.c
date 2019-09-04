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
struct TYPE_5__ {struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ tree_num_t ;

/* Variables and functions */
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  free_tree_num_node (TYPE_1__*) ; 

__attribute__((used)) static void free_tree_num (tree_num_t *T) {
  if (T != NIL) {
    free_tree_num (T->left);
    free_tree_num (T->right);
    free_tree_num_node (T);
  }
}