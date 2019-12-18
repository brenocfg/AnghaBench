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
 int /*<<< orphan*/  ldns_rbtree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ldns_rbtree_insert_vref(ldns_rbnode_t *data, void *rbtree)
{
	(void) ldns_rbtree_insert((ldns_rbtree_t *) rbtree,
						 data);
}