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
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 scalar_t__ LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_MEM_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_dname_new_frm_str (char const*) ; 
 scalar_t__ ldns_pkt_ancount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_answer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_authority (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_query_new (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_random_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_clone (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rdf_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_resolver_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_free (int /*<<< orphan*/ *) ; 
 int ldns_resolver_nameserver_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ldns_resolver_nameservers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_push_nameserver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_send_pkt (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_set_random (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_pop_rr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ldns_status
ldns_update_soa_zone_mname(const char *fqdn, ldns_resolver *r,
    ldns_rr_class c, ldns_rdf **zone_rdf, ldns_rdf **mname_rdf)
{
	ldns_rr		*soa_rr, *rr;
	ldns_rdf	*soa_zone = NULL, *soa_mname = NULL;
	ldns_rdf	*ipaddr, *fqdn_rdf, *tmp;
	ldns_rdf	**nslist;
	ldns_pkt	*query, *resp;
	ldns_resolver   *tmp_r;
	size_t		i;

	/* 
	 * XXX Ok, this cannot be the best way to find this...?
	 * XXX (I run into weird cache-related stuff here)
	 */

	/* Step 1 - first find a nameserver that should know *something* */
	fqdn_rdf = ldns_dname_new_frm_str(fqdn);
	query = ldns_pkt_query_new(fqdn_rdf, LDNS_RR_TYPE_SOA, c, LDNS_RD);
	if (!query) {
		return LDNS_STATUS_ERR;
	}
	fqdn_rdf = NULL;

	ldns_pkt_set_random_id(query);
	if (ldns_resolver_send_pkt(&resp, r, query) != LDNS_STATUS_OK) {
		ldns_pkt_free(query);
		return LDNS_STATUS_ERR;
	}
	ldns_pkt_free(query);
	if (!resp) {
		return LDNS_STATUS_ERR;
	}

	/* XXX Is it safe to only look in authority section here? */
	while ((soa_rr = ldns_rr_list_pop_rr(ldns_pkt_authority(resp)))) {
		if (ldns_rr_get_type(soa_rr) != LDNS_RR_TYPE_SOA
				|| ldns_rr_rdf(soa_rr, 0) == NULL)
			continue;
		/* [RFC1035 3.3.13] */
		soa_mname = ldns_rdf_clone(ldns_rr_rdf(soa_rr, 0));
		break;
	}
	ldns_pkt_free(resp);
	if (!soa_rr) {
		return LDNS_STATUS_ERR;
	}

	/* Step 2 - find SOA MNAME IP address, add to resolver */
	query = ldns_pkt_query_new(soa_mname, LDNS_RR_TYPE_A, c, LDNS_RD);
	if (!query) {
		return LDNS_STATUS_ERR;
	}
	soa_mname = NULL;

	ldns_pkt_set_random_id(query);
	if (ldns_resolver_send_pkt(&resp, r, query) != LDNS_STATUS_OK) {
		ldns_pkt_free(query);
		return LDNS_STATUS_ERR;
	}
	ldns_pkt_free(query);
	if (!resp) {
		return LDNS_STATUS_ERR;
	}

	if (ldns_pkt_ancount(resp) == 0) {
		ldns_pkt_free(resp);
		return LDNS_STATUS_ERR;
	}

	/* XXX There may be more than one answer RR here. */
	rr = ldns_rr_list_pop_rr(ldns_pkt_answer(resp));
	ipaddr = ldns_rr_rdf(rr, 0);

	/* Put the SOA mname IP first in the nameserver list. */
	if (!(tmp_r = ldns_resolver_clone(r))) {
		return LDNS_STATUS_MEM_ERR;
	}
	nslist = ldns_resolver_nameservers(tmp_r);
	for (i = 0; i < ldns_resolver_nameserver_count(tmp_r); i++) {
		if (ldns_rdf_compare(ipaddr, nslist[i]) == 0) {
			if (i) {
				tmp = nslist[0];
				nslist[0] = nslist[i];
				nslist[i] = tmp;
			}
			break;
		}
	}
	if (i >= ldns_resolver_nameserver_count(tmp_r)) {
		/* SOA mname was not part of the resolver so add it first. */
		(void) ldns_resolver_push_nameserver(tmp_r, ipaddr);
		nslist = ldns_resolver_nameservers(tmp_r);
		i = ldns_resolver_nameserver_count(tmp_r) - 1;
		tmp = nslist[0];
		nslist[0] = nslist[i];
		nslist[i] = tmp;
	}
	ldns_pkt_free(resp);

	/* Make sure to ask the first in the list, i.e SOA mname */
	ldns_resolver_set_random(tmp_r, false);

	/* Step 3 - Redo SOA query, sending to SOA MNAME directly. */
	fqdn_rdf = ldns_dname_new_frm_str(fqdn);
	query = ldns_pkt_query_new(fqdn_rdf, LDNS_RR_TYPE_SOA, c, LDNS_RD);
	if (!query) {
		ldns_resolver_free(tmp_r);
		return LDNS_STATUS_ERR;
	}
	fqdn_rdf = NULL;

	ldns_pkt_set_random_id(query);
	if (ldns_resolver_send_pkt(&resp, tmp_r, query) != LDNS_STATUS_OK) {
		ldns_pkt_free(query);
		ldns_resolver_free(tmp_r);
		return LDNS_STATUS_ERR;
	}
	ldns_resolver_free(tmp_r);
	ldns_pkt_free(query);
	if (!resp) {
		return LDNS_STATUS_ERR;
	}

	/* XXX Is it safe to only look in authority section here, too? */
	while ((soa_rr = ldns_rr_list_pop_rr(ldns_pkt_authority(resp)))) {
		if (ldns_rr_get_type(soa_rr) != LDNS_RR_TYPE_SOA
				|| ldns_rr_rdf(soa_rr, 0) == NULL)
			continue;
		/* [RFC1035 3.3.13] */
		soa_mname = ldns_rdf_clone(ldns_rr_rdf(soa_rr, 0));
		soa_zone = ldns_rdf_clone(ldns_rr_owner(soa_rr));
		break;
	}
	ldns_pkt_free(resp);
	if (!soa_rr) {
		return LDNS_STATUS_ERR;
	}

	/* That seems to have worked, pass results to caller. */
	*zone_rdf = soa_zone;
	*mname_rdf = soa_mname;
	return LDNS_STATUS_OK;
}