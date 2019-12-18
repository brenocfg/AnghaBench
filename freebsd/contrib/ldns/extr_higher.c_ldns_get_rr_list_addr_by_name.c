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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int LDNS_RD ; 
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_RESOLV_INETANY ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int /*<<< orphan*/ * ldns_get_rr_list_hosts_frm_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_rr_list_by_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rdf_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_resolver_ip6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_resolver_query (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ldns_resolver_set_ip6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rr_list_cat_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ ) ; 

ldns_rr_list *
ldns_get_rr_list_addr_by_name(ldns_resolver *res, const ldns_rdf *name,
		ldns_rr_class c, uint16_t flags)
{
	ldns_pkt *pkt;
	ldns_rr_list *aaaa;
	ldns_rr_list *a;
	ldns_rr_list *result = NULL;
	ldns_rr_list *hostsfilenames;
	size_t i;
	uint8_t ip6;

	a = NULL; 
	aaaa = NULL; 
	result = NULL;

	if (!res) {
		return NULL;
	}
	if (ldns_rdf_get_type(name) != LDNS_RDF_TYPE_DNAME) {
		return NULL;
	}

	ip6 = ldns_resolver_ip6(res); /* we use INET_ANY here, save
					 what was there */

	ldns_resolver_set_ip6(res, LDNS_RESOLV_INETANY);
	
	hostsfilenames = ldns_get_rr_list_hosts_frm_file(NULL);
	for (i = 0; i < ldns_rr_list_rr_count(hostsfilenames); i++) {
		if (ldns_rdf_compare(name, 
					ldns_rr_owner(ldns_rr_list_rr(hostsfilenames, 
							i))) == 0) {
			if (!result) {
				result = ldns_rr_list_new();
			}
			ldns_rr_list_push_rr(result, 
					ldns_rr_clone(ldns_rr_list_rr(hostsfilenames, i)));
		}
	}
	ldns_rr_list_deep_free(hostsfilenames);

	if (result) {
		return result;
	}

	/* add the RD flags, because we want an answer */
	pkt = ldns_resolver_query(res, name, LDNS_RR_TYPE_AAAA, c, flags | LDNS_RD);
	if (pkt) {
		/* extract the data we need */
		aaaa = ldns_pkt_rr_list_by_type(pkt, LDNS_RR_TYPE_AAAA, 
			LDNS_SECTION_ANSWER);
		ldns_pkt_free(pkt);
	} 

	pkt = ldns_resolver_query(res, name, LDNS_RR_TYPE_A, c, flags | LDNS_RD);
	if (pkt) {
		/* extract the data we need */
		a = ldns_pkt_rr_list_by_type(pkt, LDNS_RR_TYPE_A, LDNS_SECTION_ANSWER);
		ldns_pkt_free(pkt);
	} 
	ldns_resolver_set_ip6(res, ip6);

	if (aaaa && a) {
		result = ldns_rr_list_cat_clone(aaaa, a);
		ldns_rr_list_deep_free(aaaa);
		ldns_rr_list_deep_free(a);
		return result;
	}
	
	if (aaaa) {
		result = ldns_rr_list_clone(aaaa);
	}
	
	if (a) {
		result = ldns_rr_list_clone(a);
	}

	ldns_rr_list_deep_free(aaaa);
	ldns_rr_list_deep_free(a);
	return result;
}