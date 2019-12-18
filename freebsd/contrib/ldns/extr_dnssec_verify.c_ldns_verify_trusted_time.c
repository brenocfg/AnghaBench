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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_NO_RRSIG ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_fetch_valid_domain_keys_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_dnssec_anchors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,int) ; 
 int ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_signame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ldns_status
ldns_verify_trusted_time(
		ldns_resolver *res, 
		ldns_rr_list *rrset, 
		ldns_rr_list * rrsigs, 
		time_t check_time,
		ldns_rr_list * validating_keys
		)
{
	uint16_t sig_i; uint16_t key_i;
	ldns_rr * cur_sig; ldns_rr * cur_key;
	ldns_rr_list * trusted_keys = NULL;
	ldns_status result = LDNS_STATUS_ERR;

	if (!res || !rrset || !rrsigs) {
		return LDNS_STATUS_ERR;
	}

	if (ldns_rr_list_rr_count(rrset) < 1) {
		return LDNS_STATUS_ERR;
	}

	if (ldns_rr_list_rr_count(rrsigs) < 1) {
		return LDNS_STATUS_CRYPTO_NO_RRSIG;
	}
  
	/* Look at each sig */
	for (sig_i=0; sig_i < ldns_rr_list_rr_count(rrsigs); sig_i++) {

		cur_sig = ldns_rr_list_rr(rrsigs, sig_i);
		/* Get a valid signer key and validate the sig */
		if ((trusted_keys = ldns_fetch_valid_domain_keys_time(
					res, 
					ldns_rr_rrsig_signame(cur_sig), 
					ldns_resolver_dnssec_anchors(res), 
					check_time,
					&result))) {

			for (key_i = 0;
				key_i < ldns_rr_list_rr_count(trusted_keys);
				key_i++) {
				cur_key = ldns_rr_list_rr(trusted_keys, key_i);

				if ((result = ldns_verify_rrsig_time(rrset,
								cur_sig, 
								cur_key,
								check_time))
				    == LDNS_STATUS_OK) {
					if (validating_keys) {
						ldns_rr_list_push_rr(validating_keys,
										 ldns_rr_clone(cur_key));
					}
					ldns_rr_list_deep_free(trusted_keys);
					return LDNS_STATUS_OK;
				} 
			}
		}
	}

	ldns_rr_list_deep_free(trusted_keys);
	return result;
}