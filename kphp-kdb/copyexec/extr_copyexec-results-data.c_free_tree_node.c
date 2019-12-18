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
struct TYPE_4__ {struct TYPE_4__* left; struct TYPE_4__* right; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 TYPE_1__ free_tree_head ; 
 int /*<<< orphan*/  free_tree_nodes ; 

__attribute__((used)) static void free_tree_node (tree_t *T) {
  (T->right = free_tree_head.right)->left = T;
  free_tree_head.right = T;
  T->left = &free_tree_head;
  free_tree_nodes++;
}