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
typedef  int /*<<< orphan*/  rbtree_type ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 scalar_t__ rbtree_find_less_equal (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ **) ; 

rbnode_type *
rbtree_search (rbtree_type *rbtree, const void *key)
{
	rbnode_type *node;

	if (rbtree_find_less_equal(rbtree, key, &node)) {
		return node;
	} else {
		return NULL;
	}
}