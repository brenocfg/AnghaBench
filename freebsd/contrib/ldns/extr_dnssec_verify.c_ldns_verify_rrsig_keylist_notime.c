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
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  const ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_PACKETLEN ; 
 scalar_t__ LDNS_STATUS_CRYPTO_NO_MATCHING_KEYTAG_DNSKEY ; 
 scalar_t__ LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_MEM_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_prepare_for_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_list_cat (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ldns_rr_list_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_list_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_verify_test_sig_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

ldns_status
ldns_verify_rrsig_keylist_notime(const ldns_rr_list *rrset,
					 const ldns_rr *rrsig,
					 const ldns_rr_list *keys, 
					 ldns_rr_list *good_keys)
{
	ldns_buffer *rawsig_buf;
	ldns_buffer *verify_buf;
	uint16_t i;
	ldns_status result, status;
	ldns_rr_list *rrset_clone;
	ldns_rr_list *validkeys;

	if (!rrset) {
		return LDNS_STATUS_ERR;
	}

	validkeys = ldns_rr_list_new();
	if (!validkeys) {
		return LDNS_STATUS_MEM_ERR;
	}
	
	/* clone the rrset so that we can fiddle with it */
	rrset_clone = ldns_rr_list_clone(rrset);

	/* create the buffers which will certainly hold the raw data */
	rawsig_buf = ldns_buffer_new(LDNS_MAX_PACKETLEN);
	verify_buf  = ldns_buffer_new(LDNS_MAX_PACKETLEN);

	result = ldns_prepare_for_verify(rawsig_buf, verify_buf, 
		rrset_clone, rrsig);
	if(result != LDNS_STATUS_OK) {
		ldns_buffer_free(verify_buf);
		ldns_buffer_free(rawsig_buf);
		ldns_rr_list_deep_free(rrset_clone);
		ldns_rr_list_free(validkeys);
		return result;
	}

	result = LDNS_STATUS_CRYPTO_NO_MATCHING_KEYTAG_DNSKEY;
	for(i = 0; i < ldns_rr_list_rr_count(keys); i++) {
		status = ldns_verify_test_sig_key(rawsig_buf, verify_buf, 
			rrsig, ldns_rr_list_rr(keys, i));
		if (status == LDNS_STATUS_OK) {
			/* one of the keys has matched, don't break
			 * here, instead put the 'winning' key in
			 * the validkey list and return the list 
			 * later */
			if (!ldns_rr_list_push_rr(validkeys, 
				ldns_rr_list_rr(keys,i))) {
				/* couldn't push the key?? */
				ldns_buffer_free(rawsig_buf);
				ldns_buffer_free(verify_buf);
				ldns_rr_list_deep_free(rrset_clone);
				ldns_rr_list_free(validkeys);
				return LDNS_STATUS_MEM_ERR;
			}

			result = status;
		}

		if (result == LDNS_STATUS_CRYPTO_NO_MATCHING_KEYTAG_DNSKEY) {
			result = status;
		}
	}

	/* no longer needed */
	ldns_rr_list_deep_free(rrset_clone);
	ldns_buffer_free(rawsig_buf);
	ldns_buffer_free(verify_buf);

	if (ldns_rr_list_rr_count(validkeys) == 0) {
		/* no keys were added, return last error */
		ldns_rr_list_free(validkeys); 
		return result;
	}

	/* do not check timestamps */

	ldns_rr_list_cat(good_keys, validkeys);
	ldns_rr_list_free(validkeys);
	return LDNS_STATUS_OK;
}