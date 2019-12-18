#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_rbnode_t ;
struct TYPE_4__ {int /*<<< orphan*/ * hashed_names; int /*<<< orphan*/  _nsec3params; } ;
typedef  TYPE_1__ ldns_dnssec_zone ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/ * ldns_dname_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_zone_hashed_names_from_nsec3 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rbtree_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ldns_rbnode_t *
ldns_dnssec_zone_find_nsec3_original(ldns_dnssec_zone *zone, ldns_rr *rr) {
	ldns_rdf *hashed_name;

	hashed_name = ldns_dname_label(ldns_rr_owner(rr), 0);
	if (hashed_name == NULL) {
		return NULL;
	}
	if (ldns_rr_get_type(rr) == LDNS_RR_TYPE_NSEC3 && ! zone->_nsec3params){

		ldns_dnssec_zone_hashed_names_from_nsec3(zone, rr);
	}
	if (zone->hashed_names == NULL) {
		ldns_rdf_deep_free(hashed_name);
		return NULL;
	}
	return  ldns_rbtree_search(zone->hashed_names, hashed_name);
}