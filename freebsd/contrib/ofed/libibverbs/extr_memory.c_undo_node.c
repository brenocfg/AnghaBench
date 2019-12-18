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
struct ibv_mem_node {uintptr_t start; scalar_t__ refcnt; } ;

/* Variables and functions */
 struct ibv_mem_node* __mm_next (struct ibv_mem_node*) ; 
 struct ibv_mem_node* __mm_prev (struct ibv_mem_node*) ; 
 struct ibv_mem_node* merge_ranges (struct ibv_mem_node*,struct ibv_mem_node*) ; 
 struct ibv_mem_node* split_range (struct ibv_mem_node*,uintptr_t) ; 

__attribute__((used)) static struct ibv_mem_node *undo_node(struct ibv_mem_node *node,
				      uintptr_t start, int inc)
{
	struct ibv_mem_node *tmp = NULL;

	/*
	 * This condition can be true only if we merged this
	 * node with the previous one, so we need to split them.
	*/
	if (start > node->start) {
		tmp = split_range(node, start);
		if (tmp) {
			node->refcnt += inc;
			node = tmp;
		} else
			return NULL;
	}

	tmp  =  __mm_prev(node);
	if (tmp && tmp->refcnt == node->refcnt)
		node = merge_ranges(node, tmp);

	tmp  =  __mm_next(node);
	if (tmp && tmp->refcnt == node->refcnt)
		node = merge_ranges(tmp, node);

	return node;
}