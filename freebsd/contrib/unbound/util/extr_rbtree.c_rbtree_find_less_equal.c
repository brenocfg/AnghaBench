#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* cmp ) (void const*,int /*<<< orphan*/ ) ;TYPE_2__* root; } ;
typedef  TYPE_1__ rbtree_type ;
struct TYPE_8__ {struct TYPE_8__* right; struct TYPE_8__* left; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ rbnode_type ;

/* Variables and functions */
 TYPE_2__* RBTREE_NULL ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_rbtree_cmp (int (*) (void const*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  log_assert (TYPE_2__**) ; 
 int stub1 (void const*,int /*<<< orphan*/ ) ; 

int
rbtree_find_less_equal(rbtree_type *rbtree, const void *key,
	rbnode_type **result)
{
	int r;
	rbnode_type *node;

	log_assert(result);
	
	/* We start at root... */
	node = rbtree->root;

	*result = NULL;
	fptr_ok(fptr_whitelist_rbtree_cmp(rbtree->cmp));

	/* While there are children... */
	while (node != RBTREE_NULL) {
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