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

__attribute__((used)) static struct ibv_mem_node *__mm_next(struct ibv_mem_node *node)
{
	if (node->right) {
		node = node->right;
		while (node->left)
			node = node->left;
	} else {
		while (node->parent && node == node->parent->right)
			node = node->parent;

		node = node->parent;
	}

	return node;
}