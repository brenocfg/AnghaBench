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
typedef  TYPE_1__ tree_ext_global_t ;

/* Variables and functions */
 TYPE_1__* NILG ; 
 int /*<<< orphan*/  free_tree_ext_global_node (TYPE_1__*) ; 

__attribute__((used)) static void free_tree_ext_global (tree_ext_global_t *T) {
  if (T != NILG) {
    free_tree_ext_global (T->left);
    free_tree_ext_global (T->right);
    free_tree_ext_global_node (T);
  }
}