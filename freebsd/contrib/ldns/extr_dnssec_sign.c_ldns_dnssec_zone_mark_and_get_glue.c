#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rdf ;
struct TYPE_10__ {scalar_t__ data; } ;
typedef  TYPE_1__ ldns_rbnode_t ;
struct TYPE_11__ {int /*<<< orphan*/  names; } ;
typedef  TYPE_2__ ldns_dnssec_zone ;
struct TYPE_12__ {int is_glue; int /*<<< orphan*/  rrsets; } ;
typedef  TYPE_3__ ldns_dnssec_name ;

/* Variables and functions */
 TYPE_1__* LDNS_RBTREE_NULL ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 scalar_t__ LDNS_STATUS_NULL ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_dname_is_subdomain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dnssec_addresses_on_glue_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_dnssec_name_name (TYPE_3__*) ; 
 scalar_t__ ldns_dnssec_rrsets_contains_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ldns_rbtree_first (int /*<<< orphan*/ ) ; 
 TYPE_1__* ldns_rbtree_next (TYPE_1__*) ; 

ldns_status
ldns_dnssec_zone_mark_and_get_glue(ldns_dnssec_zone *zone, 
	ldns_rr_list *glue_list)
{
	ldns_rbnode_t    *node;
	ldns_dnssec_name *name;
	ldns_rdf         *owner;
	ldns_rdf         *cut = NULL; /* keeps track of zone cuts */
	/* When the cut is caused by a delegation, below_delegation will be 1.
	 * When caused by a DNAME, below_delegation will be 0.
	 */
	int below_delegation = -1; /* init suppresses comiler warning */
	ldns_status s;

	if (!zone || !zone->names) {
		return LDNS_STATUS_NULL;
	}
	for (node = ldns_rbtree_first(zone->names); 
			node != LDNS_RBTREE_NULL; 
			node = ldns_rbtree_next(node)) {
		name = (ldns_dnssec_name *) node->data;
		owner = ldns_dnssec_name_name(name);

		if (cut) { 
			/* The previous node was a zone cut, or a subdomain
			 * below a zone cut. Is this node (still) a subdomain
			 * below the cut? Then the name is occluded. Unless
			 * the name contains a SOA, after which we are 
			 * authoritative again.
			 *
			 * FIXME! If there are labels in between the SOA and
			 * the cut, going from the authoritative space (below
			 * the SOA) up into occluded space again, will not be
			 * detected with the contruct below!
			 */
			if (ldns_dname_is_subdomain(owner, cut) &&
					!ldns_dnssec_rrsets_contains_type(
					name->rrsets, LDNS_RR_TYPE_SOA)) {

				if (below_delegation && glue_list) {
					s = ldns_dnssec_addresses_on_glue_list(
						name->rrsets, glue_list);
					if (s != LDNS_STATUS_OK) {
						return s;
					}
				}
				name->is_glue = true; /* Mark occluded name! */
				continue;
			} else {
				cut = NULL;
			}
		}

		/* The node is not below a zone cut. Is it a zone cut itself?
		 * Everything below a SOA is authoritative of course; Except
		 * when the name also contains a DNAME :).
		 */
		if (ldns_dnssec_rrsets_contains_type(
				name->rrsets, LDNS_RR_TYPE_NS)
			    && !ldns_dnssec_rrsets_contains_type(
				name->rrsets, LDNS_RR_TYPE_SOA)) {
			cut = owner;
			below_delegation = 1;
			if (glue_list) { /* record glue on the zone cut */
				s = ldns_dnssec_addresses_on_glue_list(
					name->rrsets, glue_list);
				if (s != LDNS_STATUS_OK) {
					return s;
				}
			}
		} else if (ldns_dnssec_rrsets_contains_type(
				name->rrsets, LDNS_RR_TYPE_DNAME)) {
			cut = owner;
			below_delegation = 0;
		}
	}
	return LDNS_STATUS_OK;
}