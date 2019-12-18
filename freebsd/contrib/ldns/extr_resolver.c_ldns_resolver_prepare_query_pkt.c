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
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  scalar_t__ ldns_status ;
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int LDNS_CD ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_INT32 ; 
 scalar_t__ LDNS_RR_TYPE_IXFR ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 scalar_t__ LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_native2rdf_int32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_pkt_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_ixfr_request_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_query_new (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ldns_pkt_set_cd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_do (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_udp_size (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ldns_pkt_set_random_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_set_timestamp (int /*<<< orphan*/ *,struct timeval) ; 
 int /*<<< orphan*/ * ldns_rdf_clone (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_resolver_debug (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_dnssec (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_dnssec_cd (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_edns_udp_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_get_ixfr_serial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_set_edns_udp_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_new () ; 
 int /*<<< orphan*/  ldns_rr_push_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_set_question (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_rr_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_str2rdf_dname (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

ldns_status
ldns_resolver_prepare_query_pkt(ldns_pkt **query_pkt, ldns_resolver *r,
                                const ldns_rdf *name, ldns_rr_type t,
                                ldns_rr_class c, uint16_t flags)
{
	struct timeval now;
	ldns_rr* soa = NULL;

	/* prepare a question pkt from the parameters
	 * and then send this */
	if (t == LDNS_RR_TYPE_IXFR) {
		ldns_rdf *owner_rdf;
		ldns_rdf *mname_rdf;
		ldns_rdf *rname_rdf;
		ldns_rdf *serial_rdf;
		ldns_rdf *refresh_rdf;
		ldns_rdf *retry_rdf;
		ldns_rdf *expire_rdf;
		ldns_rdf *minimum_rdf;
		soa = ldns_rr_new();

		if (!soa) {
			return LDNS_STATUS_ERR;
		}
		owner_rdf = ldns_rdf_clone(name);
		if (!owner_rdf) {
			ldns_rr_free(soa);
			return LDNS_STATUS_ERR;
		}
		ldns_rr_set_owner(soa, owner_rdf);
		ldns_rr_set_type(soa, LDNS_RR_TYPE_SOA);
		ldns_rr_set_class(soa, c);
		ldns_rr_set_question(soa, false);
		if (ldns_str2rdf_dname(&mname_rdf, ".") != LDNS_STATUS_OK) {
			ldns_rr_free(soa);
			return LDNS_STATUS_ERR;
		} else	ldns_rr_push_rdf(soa, mname_rdf);
		if (ldns_str2rdf_dname(&rname_rdf, ".") != LDNS_STATUS_OK) {
			ldns_rr_free(soa);
			return LDNS_STATUS_ERR;
		} else	ldns_rr_push_rdf(soa, rname_rdf);
		serial_rdf = ldns_native2rdf_int32(LDNS_RDF_TYPE_INT32, ldns_resolver_get_ixfr_serial(r));
		if (!serial_rdf) {
			ldns_rr_free(soa);
			return LDNS_STATUS_ERR;
		} else	ldns_rr_push_rdf(soa, serial_rdf);
		refresh_rdf = ldns_native2rdf_int32(LDNS_RDF_TYPE_INT32, 0);
		if (!refresh_rdf) {
			ldns_rr_free(soa);
			return LDNS_STATUS_ERR;
		} else	ldns_rr_push_rdf(soa, refresh_rdf);
		retry_rdf = ldns_native2rdf_int32(LDNS_RDF_TYPE_INT32, 0);
		if (!retry_rdf) {
			ldns_rr_free(soa);
			return LDNS_STATUS_ERR;
		} else	ldns_rr_push_rdf(soa, retry_rdf);
		expire_rdf = ldns_native2rdf_int32(LDNS_RDF_TYPE_INT32, 0);
		if (!expire_rdf) {
			ldns_rr_free(soa);
			return LDNS_STATUS_ERR;
		} else	ldns_rr_push_rdf(soa, expire_rdf);
		minimum_rdf = ldns_native2rdf_int32(LDNS_RDF_TYPE_INT32, 0);
		if (!minimum_rdf) {
			ldns_rr_free(soa);
			return LDNS_STATUS_ERR;
		} else	ldns_rr_push_rdf(soa, minimum_rdf);

		*query_pkt = ldns_pkt_ixfr_request_new(ldns_rdf_clone(name),
			c, flags, soa);
	} else {
		*query_pkt = ldns_pkt_query_new(ldns_rdf_clone(name), t, c, flags);
	}
	if (!*query_pkt) {
		ldns_rr_free(soa);
		return LDNS_STATUS_ERR;
	}

	/* set DO bit if necessary */
	if (ldns_resolver_dnssec(r)) {
		if (ldns_resolver_edns_udp_size(r) == 0) {
			ldns_resolver_set_edns_udp_size(r, 4096);
		}
		ldns_pkt_set_edns_do(*query_pkt, true);
		if (ldns_resolver_dnssec_cd(r) || (flags & LDNS_CD)) {
			ldns_pkt_set_cd(*query_pkt, true);
		}
	}

	/* transfer the udp_edns_size from the resolver to the packet */
	if (ldns_resolver_edns_udp_size(r) != 0) {
		ldns_pkt_set_edns_udp_size(*query_pkt, ldns_resolver_edns_udp_size(r));
	}

	/* set the timestamp */
	now.tv_sec = time(NULL);
	now.tv_usec = 0;
	ldns_pkt_set_timestamp(*query_pkt, now);


	if (ldns_resolver_debug(r)) {
		ldns_pkt_print(stdout, *query_pkt);
	}

	/* only set the id if it is not set yet */
	if (ldns_pkt_id(*query_pkt) == 0) {
		ldns_pkt_set_random_id(*query_pkt);
	}

	return LDNS_STATUS_OK;
}