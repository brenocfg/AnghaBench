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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_RDF_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_STATUS_CRYPTO_TSIG_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ LDNS_STATUS_RES_NO_NS ; 
 scalar_t__ LDNS_STATUS_RES_QUERY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_tsig_sign (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rdf_get_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_resolver_nameserver_count (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_prepare_query_pkt (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_resolver_send_pkt (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_tsig_algorithm (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_tsig_keydata (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_tsig_keyname (int /*<<< orphan*/ *) ; 

ldns_status
ldns_resolver_send(ldns_pkt **answer, ldns_resolver *r, const ldns_rdf *name,
		ldns_rr_type t, ldns_rr_class c, uint16_t flags)
{
	ldns_pkt *query_pkt;
	ldns_pkt *answer_pkt;
	ldns_status status;

	assert(r != NULL);
	assert(name != NULL);

	answer_pkt = NULL;

	/* do all the preprocessing here, then fire of an query to
	 * the network */

	if (0 == t) {
		t= LDNS_RR_TYPE_A;
	}
	if (0 == c) {
		c= LDNS_RR_CLASS_IN;
	}
	if (0 == ldns_resolver_nameserver_count(r)) {
		return LDNS_STATUS_RES_NO_NS;
	}
	if (ldns_rdf_get_type(name) != LDNS_RDF_TYPE_DNAME) {
		return LDNS_STATUS_RES_QUERY;
	}

	status = ldns_resolver_prepare_query_pkt(&query_pkt, r, name,
	                                         t, c, flags);
	if (status != LDNS_STATUS_OK) {
		return status;
	}

	/* if tsig values are set, tsign it */
	/* TODO: make last 3 arguments optional too? maybe make complete
	         rr instead of separate values in resolver (and packet)
	  Jelte
	  should this go in pkt_prepare?
	*/
	if (ldns_resolver_tsig_keyname(r) && ldns_resolver_tsig_keydata(r)) {
#ifdef HAVE_SSL
		status = ldns_pkt_tsig_sign(query_pkt,
		                            ldns_resolver_tsig_keyname(r),
		                            ldns_resolver_tsig_keydata(r),
		                            300, ldns_resolver_tsig_algorithm(r), NULL);
		if (status != LDNS_STATUS_OK) {
			ldns_pkt_free(query_pkt);
			return LDNS_STATUS_CRYPTO_TSIG_ERR;
		}
#else
		ldns_pkt_free(query_pkt);
	        return LDNS_STATUS_CRYPTO_TSIG_ERR;
#endif /* HAVE_SSL */
	}

	status = ldns_resolver_send_pkt(&answer_pkt, r, query_pkt);
	ldns_pkt_free(query_pkt);

	/* allows answer to be NULL when not interested in return value */
	if (answer) {
		*answer = answer_pkt;
	}
	return status;
}