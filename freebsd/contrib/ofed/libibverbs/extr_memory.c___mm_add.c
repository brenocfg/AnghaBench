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
struct ibv_mem_node {scalar_t__ start; int /*<<< orphan*/  color; struct ibv_mem_node* right; struct ibv_mem_node* left; struct ibv_mem_node* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_RED ; 
 int /*<<< orphan*/  __mm_add_rebalance (struct ibv_mem_node*) ; 
 struct ibv_mem_node* mm_root ; 

__attribute__((used)) static void __mm_add(struct ibv_mem_node *new)
{
	struct ibv_mem_node *node, *parent = NULL;

	node = mm_root;
	while (node) {
		parent = node;
		if (node->start < new->start)
			node = node->right;
		else
			node = node->left;
	}

	if (parent->start < new->start)
		parent->right = new;
	else
		parent->left = new;

	new->parent = parent;
	new->left   = NULL;
	new->right  = NULL;

	new->color = IBV_RED;
	__mm_add_rebalance(new);
}