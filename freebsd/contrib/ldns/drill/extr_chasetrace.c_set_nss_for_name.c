#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_dnssec_zone ;
struct TYPE_4__ {TYPE_2__* rrs; } ;
typedef  TYPE_1__ ldns_dnssec_rrsets ;
struct TYPE_5__ {int /*<<< orphan*/  rr; struct TYPE_5__* next; } ;
typedef  TYPE_2__ ldns_dnssec_rrs ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  add_rr_list_to_referrals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * ldns_dname_left_chop (int /*<<< orphan*/ *) ; 
 TYPE_1__* ldns_dnssec_zone_find_rrset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_get_rr_list_addr_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rdf_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_nameserver_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_resolver_pop_nameserver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_push_nameserver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_push_nameserver_rr_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool set_nss_for_name(
    ldns_resolver *res, ldns_dnssec_zone *referrals, ldns_rdf *name,
    ldns_resolver *local_res, ldns_rr_class c)
{
	ldns_dnssec_rrsets *nss = NULL;
	ldns_dnssec_rrs *nss_rrs;
	ldns_dnssec_rrsets *as = NULL;
	ldns_dnssec_rrs *as_rrs;
	ldns_rdf *lookup = ldns_rdf_clone(name);
	ldns_rdf *new_lookup;
	ldns_rdf *addr;
	ldns_rr_list *addrs;

	/* nss will become the rrset of as much of "name" as possible */
	for (;;) {
		nss = ldns_dnssec_zone_find_rrset(
		    referrals, lookup, LDNS_RR_TYPE_NS);
		if (nss != NULL) {
			ldns_rdf_deep_free(lookup);
			break;
		}
		new_lookup = ldns_dname_left_chop(lookup);
		ldns_rdf_deep_free(lookup);
		lookup = new_lookup;
		if (!lookup) {
			error("No referrals for name found");
			return false;
		}
	}

	/* remove the old nameserver from the resolver */
	while ((addr = ldns_resolver_pop_nameserver(res)))
		ldns_rdf_deep_free(addr);

	/* Find and add the address records for the rrset as name-servers */
	for (nss_rrs = nss->rrs; nss_rrs; nss_rrs = nss_rrs->next) {

		if ((as = ldns_dnssec_zone_find_rrset(
		    referrals, ldns_rr_rdf(nss_rrs->rr, 0), LDNS_RR_TYPE_A)))
			for (as_rrs = as->rrs; as_rrs; as_rrs = as_rrs->next)
				(void) ldns_resolver_push_nameserver(
				    res, ldns_rr_rdf(as_rrs->rr, 0));

		if ((as = ldns_dnssec_zone_find_rrset(
		    referrals, ldns_rr_rdf(nss_rrs->rr, 0), LDNS_RR_TYPE_AAAA)))
			for (as_rrs = as->rrs; as_rrs; as_rrs = as_rrs->next)
				(void) ldns_resolver_push_nameserver(
				    res, ldns_rr_rdf(as_rrs->rr, 0));
	}
	/* Is our resolver equipped with name-servers? Good! We're done */
	if (ldns_resolver_nameserver_count(res) > 0)
		return true;

	/* Lookup addresses with local resolver add add to "referrals" database */
	addrs = ldns_rr_list_new();
	for (nss_rrs = nss->rrs; nss_rrs; nss_rrs = nss_rrs->next) {
		ldns_rr_list *addrs_by_name =
		    ldns_get_rr_list_addr_by_name(
			local_res, ldns_rr_rdf(nss_rrs->rr, 0), c, 0);
		ldns_rr_list_cat(addrs, addrs_by_name);
		ldns_rr_list_free(addrs_by_name);
	}

	if (ldns_rr_list_rr_count(addrs) == 0)
		error("Could not find the nameserver ip addr; abort");

	else if (ldns_resolver_push_nameserver_rr_list(res, addrs) !=
	    LDNS_STATUS_OK)

		error("Error adding new nameservers");
	else {
		ldns_rr_list_deep_free(addrs);
		return true;
	}
	add_rr_list_to_referrals(referrals, addrs);
	ldns_rr_list_deep_free(addrs);
	return false;
}