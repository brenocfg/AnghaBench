#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* root; } ;
typedef  TYPE_1__ ldns_rbtree_t ;
struct TYPE_7__ {struct TYPE_7__* parent; struct TYPE_7__* left; struct TYPE_7__* right; } ;
typedef  TYPE_2__ ldns_rbnode_t ;

/* Variables and functions */
 TYPE_2__* LDNS_RBTREE_NULL ; 

__attribute__((used)) static void
ldns_rbtree_rotate_left(ldns_rbtree_t *rbtree, ldns_rbnode_t *node)
{
	ldns_rbnode_t *right = node->right;
	node->right = right->left;
	if (right->left != LDNS_RBTREE_NULL)
		right->left->parent = node;

	right->parent = node->parent;

	if (node->parent != LDNS_RBTREE_NULL) {
		if (node == node->parent->left) {
			node->parent->left = right;
		} else  {
			node->parent->right = right;
		}
	} else {
		rbtree->root = right;
	}
	right->left = node;
	node->parent = right;
}