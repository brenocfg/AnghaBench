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
struct TYPE_6__ {int (* cmp ) (void const*,int /*<<< orphan*/ ) ;TYPE_2__* root; } ;
typedef  TYPE_1__ ldns_rbtree_t ;
struct TYPE_7__ {struct TYPE_7__* right; struct TYPE_7__* left; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ ldns_rbnode_t ;

/* Variables and functions */
 TYPE_2__* LDNS_RBTREE_NULL ; 
 int stub1 (void const*,int /*<<< orphan*/ ) ; 

int
ldns_rbtree_find_less_equal(ldns_rbtree_t *rbtree, const void *key, ldns_rbnode_t **result)
{
	int r;
	ldns_rbnode_t *node;

	/* We start at root... */
	node = rbtree->root;

	*result = NULL;

	/* While there are children... */
	while (node != LDNS_RBTREE_NULL) {
		r = rbtree->cmp(key, node->key);
		if (r == 0) {
			/* Exact match */
			*result = node;
			return 1;
		} 
		if (r < 0) {
			node = node->left;
		} else {
			/* Temporary match */
			*result = node;
			node = node->right;
		}
	}
	return 0;
}