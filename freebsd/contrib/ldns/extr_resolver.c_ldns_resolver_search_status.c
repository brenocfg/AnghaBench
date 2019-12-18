#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_resolver ;
struct TYPE_10__ {int member_0; void* member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ const ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_RCODE_NOERROR ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_DNAME ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_dname_absolute (TYPE_1__ const*) ; 
 TYPE_1__ const* ldns_dname_cat_clone (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_get_rcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_free (TYPE_1__ const*) ; 
 scalar_t__ ldns_resolver_dnsrch (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_query_status (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ const** ldns_resolver_searchlist (int /*<<< orphan*/ *) ; 
 size_t ldns_resolver_searchlist_count (int /*<<< orphan*/ *) ; 

ldns_status
ldns_resolver_search_status(ldns_pkt** pkt,
		ldns_resolver *r, const  ldns_rdf *name,
		ldns_rr_type t, ldns_rr_class c, uint16_t flags)
{
	ldns_rdf *new_name;
	ldns_rdf **search_list;
	size_t i;
	ldns_status s = LDNS_STATUS_OK;
	ldns_rdf root_dname = { 1, LDNS_RDF_TYPE_DNAME, (void *)"" };

	if (ldns_dname_absolute(name)) {
		/* query as-is */
		return ldns_resolver_query_status(pkt, r, name, t, c, flags);
	} else if (ldns_resolver_dnsrch(r)) {
		search_list = ldns_resolver_searchlist(r);
		for (i = 0; i <= ldns_resolver_searchlist_count(r); i++) {
			if (i == ldns_resolver_searchlist_count(r)) {
				new_name = ldns_dname_cat_clone(name,
						&root_dname);
			} else {
				new_name = ldns_dname_cat_clone(name,
						search_list[i]);
			}

			s = ldns_resolver_query_status(pkt, r,
					new_name, t, c, flags);
			ldns_rdf_free(new_name);
			if (pkt && *pkt) {
				if (s == LDNS_STATUS_OK && 
						ldns_pkt_get_rcode(*pkt) ==
						LDNS_RCODE_NOERROR) {

					return LDNS_STATUS_OK;
				}
				ldns_pkt_free(*pkt);
				*pkt = NULL;
			}
		}
	}
	return s;
}