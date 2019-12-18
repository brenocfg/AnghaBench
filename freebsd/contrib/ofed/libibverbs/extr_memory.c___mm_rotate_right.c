#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ibv_mem_node {struct ibv_mem_node* parent; struct ibv_mem_node* right; struct ibv_mem_node* left; } ;

/* Variables and functions */
 struct ibv_mem_node* mm_root ; 

__attribute__((used)) static void __mm_rotate_right(struct ibv_mem_node *node)
{
	struct ibv_mem_node *tmp;

	tmp = node->left;

	node->left = tmp->right;
	if (node->left)
		node->left->parent = node;

	if (node->parent) {
		if (node->parent->right == node)
			node->parent->right = tmp;
		else
			node->parent->left = tmp;
	} else
		mm_root = tmp;

	tmp->parent = node->parent;

	tmp->right = node;
	node->parent = tmp;
}