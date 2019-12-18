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
typedef  int /*<<< orphan*/  ldns_zone ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_dname_is_subdomain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rdf_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_owner (int /*<<< orphan*/ *) ; 
 size_t ldns_zone_rr_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_zone_rrs (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_zone_soa (int /*<<< orphan*/  const*) ; 

ldns_rr_list *
ldns_zone_glue_rr_list(const ldns_zone *z)
{
	/* when do we find glue? It means we find an IP address
	 * (AAAA/A) for a nameserver listed in the zone
	 *
	 * Alg used here:
	 * first find all the zonecuts (NS records)
	 * find all the AAAA or A records (can be done it the 
	 * above loop).
	 *
	 * Check if the aaaa/a list are subdomains under the
	 * NS domains.
	 * If yes -> glue, if no -> not glue
	 */

	ldns_rr_list *zone_cuts;
	ldns_rr_list *addr;
	ldns_rr_list *glue;
	ldns_rr *r, *ns, *a;
	ldns_rdf *dname_a, *ns_owner;
	size_t i,j;

	zone_cuts = NULL;
	addr = NULL;
	glue = NULL;

	/* we cannot determine glue in a 'zone' without a SOA */
	if (!ldns_zone_soa(z)) {
		return NULL;
	}

	zone_cuts = ldns_rr_list_new();
	if (!zone_cuts) goto memory_error;
	addr = ldns_rr_list_new();
	if (!addr) goto memory_error;
	glue = ldns_rr_list_new();
	if (!glue) goto memory_error;

	for(i = 0; i < ldns_zone_rr_count(z); i++) {
		r = ldns_rr_list_rr(ldns_zone_rrs(z), i);
		if (ldns_rr_get_type(r) == LDNS_RR_TYPE_A ||
				ldns_rr_get_type(r) == LDNS_RR_TYPE_AAAA) {
			/* possibly glue */
			if (!ldns_rr_list_push_rr(addr, r)) goto memory_error;
			continue;
		}
		if (ldns_rr_get_type(r) == LDNS_RR_TYPE_NS) {
			/* multiple zones will end up here -
			 * for now; not a problem
			 */
			/* don't add NS records for the current zone itself */
			if (ldns_rdf_compare(ldns_rr_owner(r), 
						ldns_rr_owner(ldns_zone_soa(z))) != 0) {
				if (!ldns_rr_list_push_rr(zone_cuts, r)) goto memory_error;
			}
			continue;
		}
	}

	/* will sorting make it quicker ?? */
	for(i = 0; i < ldns_rr_list_rr_count(zone_cuts); i++) {
		ns = ldns_rr_list_rr(zone_cuts, i);
		ns_owner = ldns_rr_owner(ns);

		for(j = 0; j < ldns_rr_list_rr_count(addr); j++) {
			a = ldns_rr_list_rr(addr, j);
			dname_a = ldns_rr_owner(a);

			if (ldns_dname_is_subdomain(dname_a, ns_owner) ||
				ldns_dname_compare(dname_a, ns_owner) == 0) {
				/* GLUE! */
				if (!ldns_rr_list_push_rr(glue, a)) goto memory_error;
			}
		}
	}
	
	ldns_rr_list_free(addr);
	ldns_rr_list_free(zone_cuts);

	if (ldns_rr_list_rr_count(glue) == 0) {
		ldns_rr_list_free(glue);
		return NULL;
	} else {
		return glue;
	}

memory_error:
	if (zone_cuts) {
		LDNS_FREE(zone_cuts);
	}
	if (addr) {
		ldns_rr_list_free(addr);
	}
	if (glue) {
		ldns_rr_list_free(glue);
	}
	return NULL;
}