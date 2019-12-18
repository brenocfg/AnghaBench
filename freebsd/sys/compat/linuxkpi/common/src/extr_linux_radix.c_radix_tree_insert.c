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
struct radix_tree_root {int gfp_mask; int height; struct radix_tree_node* rnode; } ;
struct radix_tree_node {scalar_t__ count; struct radix_tree_node** slots; } ;

/* Variables and functions */
 int E2BIG ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_RADIX ; 
 int M_ZERO ; 
 int RADIX_TREE_MAX_HEIGHT ; 
 int /*<<< orphan*/  free (struct radix_tree_node*,int /*<<< orphan*/ ) ; 
 struct radix_tree_node* malloc (int,int /*<<< orphan*/ ,int) ; 
 unsigned long radix_max (struct radix_tree_root*) ; 
 int radix_pos (unsigned long,int) ; 

int
radix_tree_insert(struct radix_tree_root *root, unsigned long index, void *item)
{
	struct radix_tree_node *node;
	struct radix_tree_node *temp[RADIX_TREE_MAX_HEIGHT - 1];
	int height;
	int idx;

	/* bail out upon insertion of a NULL item */
	if (item == NULL)
		return (-EINVAL);

	/* get root node, if any */
	node = root->rnode;

	/* allocate root node, if any */
	if (node == NULL) {
		node = malloc(sizeof(*node), M_RADIX, root->gfp_mask | M_ZERO);
		if (node == NULL)
			return (-ENOMEM);
		root->rnode = node;
		root->height++;
	}

	/* expand radix tree as needed */
	while (radix_max(root) < index) {

		/* check if the radix tree is getting too big */
		if (root->height == RADIX_TREE_MAX_HEIGHT)
			return (-E2BIG);

		/*
		 * If the root radix level is not empty, we need to
		 * allocate a new radix level:
		 */
		if (node->count != 0) {
			node = malloc(sizeof(*node), M_RADIX, root->gfp_mask | M_ZERO);
			if (node == NULL)
				return (-ENOMEM);
			node->slots[0] = root->rnode;
			node->count++;
			root->rnode = node;
		}
		root->height++;
	}

	/* get radix tree height index */
	height = root->height - 1;

	/* walk down the tree until the first missing node, if any */
	for ( ; height != 0; height--) {
		idx = radix_pos(index, height);
		if (node->slots[idx] == NULL)
			break;
		node = node->slots[idx];
	}

	/* allocate the missing radix levels, if any */
	for (idx = 0; idx != height; idx++) {
		temp[idx] = malloc(sizeof(*node), M_RADIX,
		    root->gfp_mask | M_ZERO);
		if (temp[idx] == NULL) {
			while(idx--)
				free(temp[idx], M_RADIX);
			/* Check if we should free the root node as well. */
			if (root->rnode->count == 0) {
				free(root->rnode, M_RADIX);
				root->rnode = NULL;
				root->height = 0;
			}
			return (-ENOMEM);
		}
	}

	/* setup new radix levels, if any */
	for ( ; height != 0; height--) {
		idx = radix_pos(index, height);
		node->slots[idx] = temp[height - 1];
		node->count++;
		node = node->slots[idx];
	}

	/*
	 * Insert and adjust count if the item does not already exist.
	 */
	idx = radix_pos(index, 0);
	if (node->slots[idx])
		return (-EEXIST);
	node->slots[idx] = item;
	node->count++;

	return (0);
}