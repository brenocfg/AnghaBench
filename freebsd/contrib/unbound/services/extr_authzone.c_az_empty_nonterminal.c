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
struct query_info {int /*<<< orphan*/  qname; } ;
struct auth_zone {int /*<<< orphan*/  data; } ;
struct auth_data {int /*<<< orphan*/  name; int /*<<< orphan*/  node; int /*<<< orphan*/ * rrsets; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/ * RBTREE_NULL ; 
 scalar_t__ dname_strict_subdomain_c (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rbtree_first (int /*<<< orphan*/ *) ; 
 scalar_t__ rbtree_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
az_empty_nonterminal(struct auth_zone* z, struct query_info* qinfo,
	struct auth_data* node)
{
	struct auth_data* next;
	if(!node) {
		/* no smaller was found, use first (smallest) node as the
		 * next one */
		next = (struct auth_data*)rbtree_first(&z->data);
	} else {
		next = (struct auth_data*)rbtree_next(&node->node);
	}
	while(next && (rbnode_type*)next != RBTREE_NULL && next->rrsets == NULL) {
		/* the next name has empty rrsets, is an empty nonterminal
		 * itself, see if there exists something below it */
		next = (struct auth_data*)rbtree_next(&node->node);
	}
	if((rbnode_type*)next == RBTREE_NULL || !next) {
		/* there is no next node, so something below it cannot
		 * exist */
		return 0;
	}
	/* a next node exists, if there was something below the query,
	 * this node has to be it.  See if it is below the query name */
	if(dname_strict_subdomain_c(next->name, qinfo->qname))
		return 1;
	return 0;
}