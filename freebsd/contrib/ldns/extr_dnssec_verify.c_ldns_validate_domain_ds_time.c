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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RD ; 
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_rr_list_by_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_resolver_query (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_verify_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ldns_rr_list *
ldns_validate_domain_ds_time(
		const ldns_resolver *res, 
		const ldns_rdf * domain,
		const ldns_rr_list * keys,
		time_t check_time)
{
	ldns_pkt * dspkt;
	uint16_t key_i;
	ldns_rr_list * rrset = NULL;
	ldns_rr_list * sigs = NULL;
	ldns_rr_list * trusted_keys = NULL;

	/* Fetch DS for the domain */
	dspkt = ldns_resolver_query(res, domain,
		LDNS_RR_TYPE_DS, LDNS_RR_CLASS_IN, LDNS_RD);
	if (dspkt) {
		rrset = ldns_pkt_rr_list_by_type(dspkt,
								   LDNS_RR_TYPE_DS,
								   LDNS_SECTION_ANSWER);
		sigs = ldns_pkt_rr_list_by_type(dspkt,
								  LDNS_RR_TYPE_RRSIG,
								  LDNS_SECTION_ANSWER);

		/* Validate sigs */
		if (ldns_verify_time(rrset, sigs, keys, check_time, NULL)
			       	== LDNS_STATUS_OK) {
			trusted_keys = ldns_rr_list_new();
			for (key_i=0; key_i<ldns_rr_list_rr_count(rrset); key_i++) {
				ldns_rr_list_push_rr(trusted_keys,
								 ldns_rr_clone(ldns_rr_list_rr(rrset,
														 key_i)
											)
								 );
			}
		}

		ldns_rr_list_deep_free(rrset);
		ldns_rr_list_deep_free(sigs);
		ldns_pkt_free(dspkt);

	} else {
		/* LDNS_STATUS_CRYPTO_NO_DS */
	}

	return trusted_keys;
}