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
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_9__ {scalar_t__ data; } ;
typedef  TYPE_1__ ldns_rbnode_t ;
struct TYPE_10__ {int /*<<< orphan*/  names; int /*<<< orphan*/ * hashed_names; int /*<<< orphan*/ * _nsec3params; } ;
typedef  TYPE_2__ ldns_dnssec_zone ;
typedef  int /*<<< orphan*/  ldns_dnssec_name ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ *) ; 
 TYPE_1__* LDNS_RBTREE_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dname_compare_v ; 
 int /*<<< orphan*/  ldns_dnssec_name_make_hashed_name (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_hashed_names_node_free ; 
 int /*<<< orphan*/ * ldns_rbtree_create (int /*<<< orphan*/ ) ; 
 TYPE_1__* ldns_rbtree_first (int /*<<< orphan*/ ) ; 
 TYPE_1__* ldns_rbtree_next (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ldns_dnssec_zone_hashed_names_from_nsec3(
		ldns_dnssec_zone* zone, ldns_rr* nsec3rr)
{
	ldns_rbnode_t* current_node;
	ldns_dnssec_name* current_name;

	assert(zone != NULL);
	assert(nsec3rr != NULL);

	if (zone->hashed_names) {
		ldns_traverse_postorder(zone->hashed_names,
				ldns_hashed_names_node_free, NULL);
		LDNS_FREE(zone->hashed_names);
	}
	zone->_nsec3params = nsec3rr;

	/* So this is a NSEC3 zone.
	* Calculate hashes for all names already in the zone
	*/
	zone->hashed_names = ldns_rbtree_create(ldns_dname_compare_v);
	if (zone->hashed_names == NULL) {
		return;
	}
	for ( current_node  = ldns_rbtree_first(zone->names)
	    ; current_node != LDNS_RBTREE_NULL
	    ; current_node  = ldns_rbtree_next(current_node)
	    ) {
		current_name = (ldns_dnssec_name *) current_node->data;
		ldns_dnssec_name_make_hashed_name(zone, current_name, nsec3rr);

	}
}