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
typedef  int /*<<< orphan*/  const ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RD ; 
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_calc_keytag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* ldns_pkt_rr_list_by_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rdf2native_int16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_resolver_query (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_clone (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_compare_ds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_keytag (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_verify_rrsig_time (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ldns_rr_list *
ldns_validate_domain_dnskey_time(
		const ldns_resolver * res,
		const ldns_rdf * domain,
		const ldns_rr_list * keys,
		time_t check_time
		)
{
	ldns_pkt * keypkt;
	ldns_rr * cur_key;
	uint16_t key_i; uint16_t key_j; uint16_t key_k;
	uint16_t sig_i; ldns_rr * cur_sig;

	ldns_rr_list * domain_keys = NULL;
	ldns_rr_list * domain_sigs = NULL;
	ldns_rr_list * trusted_keys = NULL;

	/* Fetch keys for the domain */
	keypkt = ldns_resolver_query(res, domain,
		LDNS_RR_TYPE_DNSKEY, LDNS_RR_CLASS_IN, LDNS_RD);
	if (keypkt) {
		domain_keys = ldns_pkt_rr_list_by_type(keypkt,
									    LDNS_RR_TYPE_DNSKEY,
									    LDNS_SECTION_ANSWER);
		domain_sigs = ldns_pkt_rr_list_by_type(keypkt,
									    LDNS_RR_TYPE_RRSIG,
									    LDNS_SECTION_ANSWER);

		/* Try to validate the record using our keys */
		for (key_i=0; key_i< ldns_rr_list_rr_count(domain_keys); key_i++) {
      
			cur_key = ldns_rr_list_rr(domain_keys, key_i);
			for (key_j=0; key_j<ldns_rr_list_rr_count(keys); key_j++) {
				if (ldns_rr_compare_ds(ldns_rr_list_rr(keys, key_j),
								   cur_key)) {
          
					/* Current key is trusted -- validate */
					trusted_keys = ldns_rr_list_new();
          
					for (sig_i=0;
						sig_i<ldns_rr_list_rr_count(domain_sigs);
						sig_i++) {
						cur_sig = ldns_rr_list_rr(domain_sigs, sig_i);
						/* Avoid non-matching sigs */
						if (ldns_rdf2native_int16(
							   ldns_rr_rrsig_keytag(cur_sig))
						    == ldns_calc_keytag(cur_key)) {
							if (ldns_verify_rrsig_time(
									domain_keys,
									cur_sig,
									cur_key,
									check_time)
							    == LDNS_STATUS_OK) {
                
								/* Push the whole rrset 
								   -- we can't do much more */
								for (key_k=0;
									key_k<ldns_rr_list_rr_count(
											domain_keys);
									key_k++) {
									ldns_rr_list_push_rr(
									    trusted_keys,
									    ldns_rr_clone(
										   ldns_rr_list_rr(
											  domain_keys,
											  key_k)));
								}
                
								ldns_rr_list_deep_free(domain_keys);
								ldns_rr_list_deep_free(domain_sigs);
								ldns_pkt_free(keypkt);
								return trusted_keys;
							}
						}
					}
	  
					/* Only push our trusted key */
					ldns_rr_list_push_rr(trusted_keys,
									 ldns_rr_clone(cur_key));
				}
			}
		}

		ldns_rr_list_deep_free(domain_keys);
		ldns_rr_list_deep_free(domain_sigs);
		ldns_pkt_free(keypkt);

	} else {
		/* LDNS_STATUS_CRYPTO_NO_DNSKEY */
	}
    
	return trusted_keys;
}