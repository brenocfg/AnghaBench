#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  cmp; } ;
typedef  TYPE_1__ ldns_rbtree_t ;
struct TYPE_14__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ ldns_rbnode_t ;

/* Variables and functions */
 TYPE_2__* LDNS_RBTREE_NULL ; 
 TYPE_1__* ldns_rbtree_create (int /*<<< orphan*/ ) ; 
 TYPE_2__* ldns_rbtree_delete (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ldns_rbtree_first (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_rbtree_insert (TYPE_1__*,TYPE_2__*) ; 

ldns_rbtree_t *
ldns_rbtree_split(ldns_rbtree_t *tree,
			   size_t elements)
{
	ldns_rbtree_t *new_tree;
	ldns_rbnode_t *cur_node;
	ldns_rbnode_t *move_node;
	size_t count = 0;

	new_tree = ldns_rbtree_create(tree->cmp);

	cur_node = ldns_rbtree_first(tree);
	while (count < elements && cur_node != LDNS_RBTREE_NULL) {
		move_node = ldns_rbtree_delete(tree, cur_node->key);
		(void)ldns_rbtree_insert(new_tree, move_node);
		cur_node = ldns_rbtree_first(tree);
		count++;
	}

	return new_tree;
}