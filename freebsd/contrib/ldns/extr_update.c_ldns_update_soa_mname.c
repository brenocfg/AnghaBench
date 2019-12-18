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
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RD ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 scalar_t__ LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_pkt_answer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_query_new (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_random_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_clone (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_send_pkt (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_pop_rr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ldns_status
ldns_update_soa_mname(ldns_rdf *zone, ldns_resolver *r,
    ldns_rr_class c, ldns_rdf **mname)
{
	ldns_rr		*soa_rr;
	ldns_pkt	*query, *resp;

	/* Nondestructive, so clone 'zone' here */
	query = ldns_pkt_query_new(ldns_rdf_clone(zone), LDNS_RR_TYPE_SOA,
	    c, LDNS_RD);
	if (!query) {
		return LDNS_STATUS_ERR;
	}

	ldns_pkt_set_random_id(query);
	if (ldns_resolver_send_pkt(&resp, r, query) != LDNS_STATUS_OK) {
		ldns_pkt_free(query);
		return LDNS_STATUS_ERR;
	}
	ldns_pkt_free(query);
	if (!resp) {
		return LDNS_STATUS_ERR;
	}

	/* Expect a SOA answer. */
	*mname = NULL;
	while ((soa_rr = ldns_rr_list_pop_rr(ldns_pkt_answer(resp)))) {
		if (ldns_rr_get_type(soa_rr) != LDNS_RR_TYPE_SOA
				|| ldns_rr_rdf(soa_rr, 0) == NULL)
			continue;
		/* [RFC1035 3.3.13] */
		*mname = ldns_rdf_clone(ldns_rr_rdf(soa_rr, 0));
		break;
	}
	ldns_pkt_free(resp);

	return *mname ? LDNS_STATUS_OK : LDNS_STATUS_ERR;
}