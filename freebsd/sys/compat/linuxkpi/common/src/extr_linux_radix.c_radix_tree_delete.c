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
struct radix_tree_root {int height; struct radix_tree_node* rnode; } ;
struct radix_tree_node {scalar_t__ count; struct radix_tree_node** slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_RADIX ; 
 int RADIX_TREE_MAX_HEIGHT ; 
 int /*<<< orphan*/  free (struct radix_tree_node*,int /*<<< orphan*/ ) ; 
 unsigned long radix_max (struct radix_tree_root*) ; 
 size_t radix_pos (unsigned long,int) ; 

void *
radix_tree_delete(struct radix_tree_root *root, unsigned long index)
{
	struct radix_tree_node *stack[RADIX_TREE_MAX_HEIGHT];
	struct radix_tree_node *node;
	void *item;
	int height;
	int idx;

	item = NULL;
	node = root->rnode;
	height = root->height - 1;
	if (index > radix_max(root))
		goto out;
	/*
	 * Find the node and record the path in stack.
	 */
	while (height && node) {
		stack[height] = node;
		node = node->slots[radix_pos(index, height--)];
	}
	idx = radix_pos(index, 0);
	if (node)
		item = node->slots[idx];
	/*
	 * If we removed something reduce the height of the tree.
	 */
	if (item)
		for (;;) {
			node->slots[idx] = NULL;
			node->count--;
			if (node->count > 0)
				break;
			free(node, M_RADIX);
			if (node == root->rnode) {
				root->rnode = NULL;
				root->height = 0;
				break;
			}
			height++;
			node = stack[height];
			idx = radix_pos(index, height);
		}
out:
	return (item);
}