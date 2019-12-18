#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ ldns_rbtree_t ;
struct TYPE_21__ {scalar_t__ color; struct TYPE_21__* right; struct TYPE_21__* left; struct TYPE_21__* parent; } ;
typedef  TYPE_2__ ldns_rbnode_t ;

/* Variables and functions */
 void* BLACK ; 
 TYPE_2__* LDNS_RBTREE_NULL ; 
 scalar_t__ RED ; 
 int /*<<< orphan*/  change_child_ptr (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  change_parent_ptr (TYPE_1__*,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ldns_rbtree_delete_fixup (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* ldns_rbtree_search (TYPE_1__*,void const*) ; 
 int /*<<< orphan*/  swap_int8 (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  swap_np (TYPE_2__**,TYPE_2__**) ; 

ldns_rbnode_t* 
ldns_rbtree_delete(ldns_rbtree_t *rbtree, const void *key)
{
	ldns_rbnode_t *to_delete;
	ldns_rbnode_t *child;
	if((to_delete = ldns_rbtree_search(rbtree, key)) == 0) return 0;
	rbtree->count--;

	/* make sure we have at most one non-leaf child */
	if(to_delete->left != LDNS_RBTREE_NULL &&
	   to_delete->right != LDNS_RBTREE_NULL)
	{
		/* swap with smallest from right subtree (or largest from left) */
		ldns_rbnode_t *smright = to_delete->right;
		while(smright->left != LDNS_RBTREE_NULL)
			smright = smright->left;
		/* swap the smright and to_delete elements in the tree,
		 * but the ldns_rbnode_t is first part of user data struct
		 * so cannot just swap the keys and data pointers. Instead
		 * readjust the pointers left,right,parent */

		/* swap colors - colors are tied to the position in the tree */
		swap_int8(&to_delete->color, &smright->color);

		/* swap child pointers in parents of smright/to_delete */
		change_parent_ptr(rbtree, to_delete->parent, to_delete, smright);
		if(to_delete->right != smright)
			change_parent_ptr(rbtree, smright->parent, smright, to_delete);

		/* swap parent pointers in children of smright/to_delete */
		change_child_ptr(smright->left, smright, to_delete);
		change_child_ptr(smright->left, smright, to_delete);
		change_child_ptr(smright->right, smright, to_delete);
		change_child_ptr(smright->right, smright, to_delete);
		change_child_ptr(to_delete->left, to_delete, smright);
		if(to_delete->right != smright)
			change_child_ptr(to_delete->right, to_delete, smright);
		if(to_delete->right == smright)
		{
			/* set up so after swap they work */
			to_delete->right = to_delete;
			smright->parent = smright;
		}

		/* swap pointers in to_delete/smright nodes */
		swap_np(&to_delete->parent, &smright->parent);
		swap_np(&to_delete->left, &smright->left);
		swap_np(&to_delete->right, &smright->right);

		/* now delete to_delete (which is at the location where the smright previously was) */
	}

	if(to_delete->left != LDNS_RBTREE_NULL) child = to_delete->left;
	else child = to_delete->right;

	/* unlink to_delete from the tree, replace to_delete with child */
	change_parent_ptr(rbtree, to_delete->parent, to_delete, child);
	change_child_ptr(child, to_delete, to_delete->parent);

	if(to_delete->color == RED)
	{
		/* if node is red then the child (black) can be swapped in */
	}
	else if(child->color == RED)
	{
		/* change child to BLACK, removing a RED node is no problem */
		if(child!=LDNS_RBTREE_NULL) child->color = BLACK;
	}
	else ldns_rbtree_delete_fixup(rbtree, child, to_delete->parent);

	/* unlink completely */
	to_delete->parent = LDNS_RBTREE_NULL;
	to_delete->left = LDNS_RBTREE_NULL;
	to_delete->right = LDNS_RBTREE_NULL;
	to_delete->color = BLACK;
	return to_delete;
}