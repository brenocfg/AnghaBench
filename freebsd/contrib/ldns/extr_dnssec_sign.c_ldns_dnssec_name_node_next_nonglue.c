#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_1__ ldns_rbnode_t ;
struct TYPE_9__ {int /*<<< orphan*/  is_glue; } ;
typedef  TYPE_2__ ldns_dnssec_name ;

/* Variables and functions */
 TYPE_1__* LDNS_RBTREE_NULL ; 
 TYPE_1__* ldns_rbtree_next (TYPE_1__*) ; 

ldns_rbnode_t *
ldns_dnssec_name_node_next_nonglue(ldns_rbnode_t *node)
{
	ldns_rbnode_t *next_node = NULL;
	ldns_dnssec_name *next_name = NULL;
	bool done = false;

	if (node == LDNS_RBTREE_NULL) {
		return NULL;
	}
	next_node = node;
	while (!done) {
		if (next_node == LDNS_RBTREE_NULL) {
			return NULL;
		} else {
			next_name = (ldns_dnssec_name *)next_node->data;
			if (!next_name->is_glue) {
				done = true;
			} else {
				next_node = ldns_rbtree_next(next_node);
			}
		}
	}
	return next_node;
}