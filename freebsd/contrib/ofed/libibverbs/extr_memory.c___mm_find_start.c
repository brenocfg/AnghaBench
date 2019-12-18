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
struct ibv_mem_node {uintptr_t start; uintptr_t end; struct ibv_mem_node* left; struct ibv_mem_node* right; } ;

/* Variables and functions */
 struct ibv_mem_node* mm_root ; 

__attribute__((used)) static struct ibv_mem_node *__mm_find_start(uintptr_t start, uintptr_t end)
{
	struct ibv_mem_node *node = mm_root;

	while (node) {
		if (node->start <= start && node->end >= start)
			break;

		if (node->start < start)
			node = node->right;
		else
			node = node->left;
	}

	return node;
}