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

/* Variables and functions */
 int /*<<< orphan*/  ldns_rbtree_insert_vref ; 
 int /*<<< orphan*/  ldns_traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ldns_rbtree_join(ldns_rbtree_t *tree1, ldns_rbtree_t *tree2)
{
	ldns_traverse_postorder(tree2, ldns_rbtree_insert_vref, tree1);
}