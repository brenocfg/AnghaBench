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
typedef  int /*<<< orphan*/  ldns_rbtree_t ;
struct TYPE_7__ {scalar_t__ color; struct TYPE_7__* right; struct TYPE_7__* left; struct TYPE_7__* parent; } ;
typedef  TYPE_1__ ldns_rbnode_t ;

/* Variables and functions */
 scalar_t__ BLACK ; 
 TYPE_1__* LDNS_RBTREE_NULL ; 
 scalar_t__ RED ; 
 int /*<<< orphan*/  ldns_rbtree_rotate_left (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_rbtree_rotate_right (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void ldns_rbtree_delete_fixup(ldns_rbtree_t* rbtree, ldns_rbnode_t* child, ldns_rbnode_t* child_parent)
{
	ldns_rbnode_t* sibling;
	int go_up = 1;

	/* determine sibling to the node that is one-black short */
	if(child_parent->right == child) sibling = child_parent->left;
	else sibling = child_parent->right;

	while(go_up)
	{
		if(child_parent == LDNS_RBTREE_NULL)
		{
			/* removed parent==black from root, every path, so ok */
			return;
		}

		if(sibling->color == RED)
		{	/* rotate to get a black sibling */
			child_parent->color = RED;
			sibling->color = BLACK;
			if(child_parent->right == child)
				ldns_rbtree_rotate_right(rbtree, child_parent);
			else	ldns_rbtree_rotate_left(rbtree, child_parent);
			/* new sibling after rotation */
			if(child_parent->right == child) sibling = child_parent->left;
			else sibling = child_parent->right;
		}

		if(child_parent->color == BLACK 
			&& sibling->color == BLACK
			&& sibling->left->color == BLACK
			&& sibling->right->color == BLACK)
		{	/* fixup local with recolor of sibling */
			if(sibling != LDNS_RBTREE_NULL)
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
		if(sibling != LDNS_RBTREE_NULL)
			sibling->color = RED;
		child_parent->color = BLACK;
		return;
	}

	/* get a new sibling, by rotating at sibling. See which child
	   of sibling is red */
	if(child_parent->right == child
		&& sibling->color == BLACK
		&& sibling->right->color == RED
		&& sibling->left->color == BLACK)
	{
		sibling->color = RED;
		sibling->right->color = BLACK;
		ldns_rbtree_rotate_left(rbtree, sibling);
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
		ldns_rbtree_rotate_right(rbtree, sibling);
		/* new sibling after rotation */
		if(child_parent->right == child) sibling = child_parent->left;
		else sibling = child_parent->right;
	}

	/* now we have a black sibling with a red child. rotate and exchange colors. */
	sibling->color = child_parent->color;
	child_parent->color = BLACK;
	if(child_parent->right == child)
	{
		sibling->left->color = BLACK;
		ldns_rbtree_rotate_right(rbtree, child_parent);
	}
	else
	{
		sibling->right->color = BLACK;
		ldns_rbtree_rotate_left(rbtree, child_parent);
	}
}