#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* parent; struct TYPE_5__* left; struct TYPE_5__* right; } ;
typedef  TYPE_1__ ldns_rbnode_t ;

/* Variables and functions */
 TYPE_1__* LDNS_RBTREE_NULL ; 

ldns_rbnode_t *
ldns_rbtree_previous(ldns_rbnode_t *node)
{
	ldns_rbnode_t *parent;

	if (node->left != LDNS_RBTREE_NULL) {
		/* One left, then keep on going right... */
		for (node = node->left;
			node->right != LDNS_RBTREE_NULL;
			node = node->right);
	} else {
		parent = node->parent;
		while (parent != LDNS_RBTREE_NULL && node == parent->left) {
			node = parent;
			parent = parent->parent;
		}
		node = parent;
	}
	return node;
}