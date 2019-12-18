#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int (* cmp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_2__* root; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ ldns_rbtree_t ;
struct TYPE_10__ {struct TYPE_10__* right; struct TYPE_10__* left; int /*<<< orphan*/  color; struct TYPE_10__* parent; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ ldns_rbnode_t ;

/* Variables and functions */
 TYPE_2__* LDNS_RBTREE_NULL ; 
 int /*<<< orphan*/  RED ; 
 int /*<<< orphan*/  ldns_rbtree_insert_fixup (TYPE_1__*,TYPE_2__*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ldns_rbnode_t *
ldns_rbtree_insert (ldns_rbtree_t *rbtree, ldns_rbnode_t *data)
{
	/* XXX Not necessary, but keeps compiler quiet... */
	int r = 0;

	/* We start at the root of the tree */
	ldns_rbnode_t	*node = rbtree->root;
	ldns_rbnode_t	*parent = LDNS_RBTREE_NULL;

	/* Lets find the new parent... */
	while (node != LDNS_RBTREE_NULL) {
		/* Compare two keys, do we have a duplicate? */
		if ((r = rbtree->cmp(data->key, node->key)) == 0) {
			return NULL;
		}
		parent = node;

		if (r < 0) {
			node = node->left;
		} else {
			node = node->right;
		}
	}

	/* Initialize the new node */
	data->parent = parent;
	data->left = data->right = LDNS_RBTREE_NULL;
	data->color = RED;
	rbtree->count++;

	/* Insert it into the tree... */
	if (parent != LDNS_RBTREE_NULL) {
		if (r < 0) {
			parent->left = data;
		} else {
			parent->right = data;
		}
	} else {
		rbtree->root = data;
	}

	/* Fix up the red-black properties... */
	ldns_rbtree_insert_fixup(rbtree, data);

	return data;
}