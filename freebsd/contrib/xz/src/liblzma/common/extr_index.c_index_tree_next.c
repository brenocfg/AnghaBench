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
struct TYPE_3__ {struct TYPE_3__ const* parent; struct TYPE_3__ const* right; struct TYPE_3__ const* left; } ;
typedef  TYPE_1__ const index_tree_node ;

/* Variables and functions */

__attribute__((used)) static void *
index_tree_next(const index_tree_node *node)
{
	if (node->right != NULL) {
		node = node->right;
		while (node->left != NULL)
			node = node->left;

		return (void *)(node);
	}

	while (node->parent != NULL && node->parent->right == node)
		node = node->parent;

	return (void *)(node->parent);
}