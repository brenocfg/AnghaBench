#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_rbtree_t ;
typedef  int /*<<< orphan*/  ldns_rbnode_t ;

/* Variables and functions */
 scalar_t__ ldns_rbtree_find_less_equal (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ **) ; 

ldns_rbnode_t *
ldns_rbtree_search (ldns_rbtree_t *rbtree, const void *key)
{
	ldns_rbnode_t *node;

	if (ldns_rbtree_find_less_equal(rbtree, key, &node)) {
		return node;
	} else {
		return NULL;
	}
}