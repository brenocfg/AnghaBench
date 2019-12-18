#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rbtree_type ;
struct TYPE_7__ {scalar_t__ color; struct TYPE_7__* right; struct TYPE_7__* left; struct TYPE_7__* parent; } ;
typedef  TYPE_1__ rbnode_type ;

/* Variables and functions */
 scalar_t__ BLACK ; 
 TYPE_1__* RBTREE_NULL ; 
 scalar_t__ RED ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  rbtree_rotate_left (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rbtree_rotate_right (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void rbtree_delete_fixup(rbtree_type* rbtree, rbnode_type* child,
	rbnode_type* child_parent)
{
	rbnode_type* sibling;
	int go_up = 1;

	/* determine sibling to the node that is one-black short */
	if(child_parent->right == child) sibling = child_parent->left;
	else sibling = child_parent->right;

	while(go_up)
	{
		if(child_parent == RBTREE_NULL)
		{
			/* removed parent==black from root, every path, so ok */
			return;
		}

		if(sibling->color == RED)
		{	/* rotate to get a black sibling */
			child_parent->color = RED;
			sibling->color = BLACK;
			if(child_parent->right == child)
				rbtree_rotate_right(rbtree, child_parent);
			else	rbtree_rotate_left(rbtree, child_parent);
			/* new sibling after rotation */
			if(child_parent->right == child) sibling = child_parent->left;
			else sibling = child_parent->right;
		}

		if(child_parent->color == BLACK 
			&& sibling->color == BLACK
			&& sibling->left->color == BLACK
			&& sibling->right->color == BLACK)
		{	/* fixup local with recolor of sibling */
			if(sibling != RBTREE_NULL)
				sibling->color = RED;

			child = child_parent;
			child_parent = child_parent->parent;
			/* prepare to go up, new sibling */
			if(child_parent->right == child) sibling = child_parent->left;
			else sibling = child_parent->right;
		}
		else go_up = 0;
	}

	if(child_parent->color == RED
		&& sibling->color == BLACK
		&& sibling->left->color == BLACK
		&& sibling->right->color == BLACK) 
	{
		/* move red to sibling to rebalance */
		if(sibling != RBTREE_NULL)
			sibling->color = RED;
		child_parent->color = BLACK;
		return;
	}
	log_assert(sibling != RBTREE_NULL);

	/* get a new sibling, by rotating at sibling. See which child
	   of sibling is red */
	if(child_parent->right == child
		&& sibling->color == BLACK
		&& sibling->right->color == RED
		&& sibling->left->color == BLACK)
	{
		sibling->color = RED;
		sibling->right->color = BLACK;
		rbtree_rotate_left(rbtree, sibling);
		/* new sibling after rotation */
		if(child_parent->right == child) sibling = child_parent->left;
		else sibling = child_parent->right;
	}
	else if(child_parent->left == child
		&& sibling->color == BLACK
		&& sibling->left->color == RED
		&& sibling->right->color == BLACK)
	{
		sibling->color = RED;
		sibling->left->color = BLACK;
		rbtree_rotate_right(rbtree, sibling);
		/* new sibling after rotation */
		if(child_parent->right == child) sibling = child_parent->left;
		else sibling = child_parent->right;
	}

	/* now we have a black sibling with a red child. rotate and exchange colors. */
	sibling->color = child_parent->color;
	child_parent->color = BLACK;
	if(child_parent->right == child)
	{
		log_assert(sibling->left->color == RED);
		sibling->left->color = BLACK;
		rbtree_rotate_right(rbtree, child_parent);
	}
	else
	{
		log_assert(sibling->right->color == RED);
		sibling->right->color = BLACK;
		rbtree_rotate_left(rbtree, child_parent);
	}
}