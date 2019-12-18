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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int LDNS_RD ; 
 scalar_t__ LDNS_RDF_TYPE_A ; 
 scalar_t__ LDNS_RDF_TYPE_AAAA ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_PTR ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_rr_list_by_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rdf_address_reverse (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_resolver_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

ldns_rr_list *
ldns_get_rr_list_name_by_addr(ldns_resolver *res, const ldns_rdf *addr,
		ldns_rr_class c, uint16_t flags)
{
	ldns_pkt *pkt;
	ldns_rr_list *names;
	ldns_rdf *name;

	names = NULL;

	if (!res || !addr) {
		return NULL;
	}

	if (ldns_rdf_get_type(addr) != LDNS_RDF_TYPE_A &&
			ldns_rdf_get_type(addr) != LDNS_RDF_TYPE_AAAA) {
		return NULL;
	}

	name = ldns_rdf_address_reverse(addr);
	
	/* add the RD flags, because we want an answer */
	pkt = ldns_resolver_query(res, name, LDNS_RR_TYPE_PTR, c, flags | LDNS_RD);
	ldns_rdf_deep_free(name);
	if (pkt) {
		/* extract the data we need */
		names = ldns_pkt_rr_list_by_type(pkt, 
				LDNS_RR_TYPE_PTR, LDNS_SECTION_ANSWER);
		ldns_pkt_free(pkt);
	}
	return names;
}