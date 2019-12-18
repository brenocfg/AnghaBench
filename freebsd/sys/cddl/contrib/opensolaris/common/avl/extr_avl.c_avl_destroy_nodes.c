#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t avl_offset; int avl_numnodes; TYPE_2__* avl_root; } ;
typedef  TYPE_1__ avl_tree_t ;
struct TYPE_12__ {struct TYPE_12__** avl_child; } ;
typedef  TYPE_2__ avl_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_2__* AVL_DATA2NODE (void*,size_t) ; 
 void* AVL_NODE2DATA (TYPE_2__*,size_t) ; 
 int AVL_XBALANCE (TYPE_2__*) ; 
 uintptr_t AVL_XCHILD (TYPE_2__*) ; 
 TYPE_2__* AVL_XPARENT (TYPE_2__*) ; 
 uintptr_t CHILDBIT ; 
 void* avl_first (TYPE_1__*) ; 

void *
avl_destroy_nodes(avl_tree_t *tree, void **cookie)
{
	avl_node_t	*node;
	avl_node_t	*parent;
	int		child;
	void		*first;
	size_t		off = tree->avl_offset;

	/*
	 * Initial calls go to the first node or it's right descendant.
	 */
	if (*cookie == NULL) {
		first = avl_first(tree);

		/*
		 * deal with an empty tree
		 */
		if (first == NULL) {
			*cookie = (void *)CHILDBIT;
			return (NULL);
		}

		node = AVL_DATA2NODE(first, off);
		parent = AVL_XPARENT(node);
		goto check_right_side;
	}

	/*
	 * If there is no parent to return to we are done.
	 */
	parent = (avl_node_t *)((uintptr_t)(*cookie) & ~CHILDBIT);
	if (parent == NULL) {
		if (tree->avl_root != NULL) {
			ASSERT(tree->avl_numnodes == 1);
			tree->avl_root = NULL;
			tree->avl_numnodes = 0;
		}
		return (NULL);
	}

	/*
	 * Remove the child pointer we just visited from the parent and tree.
	 */
	child = (uintptr_t)(*cookie) & CHILDBIT;
	parent->avl_child[child] = NULL;
	ASSERT(tree->avl_numnodes > 1);
	--tree->avl_numnodes;

	/*
	 * If we just did a right child or there isn't one, go up to parent.
	 */
	if (child == 1 || parent->avl_child[1] == NULL) {
		node = parent;
		parent = AVL_XPARENT(parent);
		goto done;
	}

	/*
	 * Do parent's right child, then leftmost descendent.
	 */
	node = parent->avl_child[1];
	while (node->avl_child[0] != NULL) {
		parent = node;
		node = node->avl_child[0];
	}

	/*
	 * If here, we moved to a left child. It may have one
	 * child on the right (when balance == +1).
	 */
check_right_side:
	if (node->avl_child[1] != NULL) {
		ASSERT(AVL_XBALANCE(node) == 1);
		parent = node;
		node = node->avl_child[1];
		ASSERT(node->avl_child[0] == NULL &&
		    node->avl_child[1] == NULL);
	} else {
		ASSERT(AVL_XBALANCE(node) <= 0);
	}

done:
	if (parent == NULL) {
		*cookie = (void *)CHILDBIT;
		ASSERT(node == tree->avl_root);
	} else {
		*cookie = (void *)((uintptr_t)parent | AVL_XCHILD(node));
	}

	return (AVL_NODE2DATA(node, off));
}