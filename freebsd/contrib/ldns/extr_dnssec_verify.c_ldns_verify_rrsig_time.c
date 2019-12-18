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
typedef  int /*<<< orphan*/  time_t ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_PACKETLEN ; 
 scalar_t__ LDNS_STATUS_NO_DATA ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_prepare_for_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rrsig_check_timestamps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_verify_test_sig_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ldns_status
ldns_verify_rrsig_time(
		ldns_rr_list *rrset, 
		ldns_rr *rrsig, 
		ldns_rr *key, 
		time_t check_time)
{
	ldns_buffer *rawsig_buf;
	ldns_buffer *verify_buf;
	ldns_status result;
	ldns_rr_list *rrset_clone;

	if (!rrset) {
		return LDNS_STATUS_NO_DATA;
	}
	/* clone the rrset so that we can fiddle with it */
	rrset_clone = ldns_rr_list_clone(rrset);
	/* create the buffers which will certainly hold the raw data */
	rawsig_buf = ldns_buffer_new(LDNS_MAX_PACKETLEN);
	verify_buf  = ldns_buffer_new(LDNS_MAX_PACKETLEN);

	result = ldns_prepare_for_verify(rawsig_buf, verify_buf, 
		rrset_clone, rrsig);
	if(result != LDNS_STATUS_OK) {
		ldns_rr_list_deep_free(rrset_clone);
		ldns_buffer_free(rawsig_buf);
		ldns_buffer_free(verify_buf);
		return result;
	}
	result = ldns_verify_test_sig_key(rawsig_buf, verify_buf, 
		rrsig, key);
	/* no longer needed */
	ldns_rr_list_deep_free(rrset_clone);
	ldns_buffer_free(rawsig_buf);
	ldns_buffer_free(verify_buf);

	/* check timestamp last, apart from time its OK */
	if(result == LDNS_STATUS_OK)
		result = ldns_rrsig_check_timestamps(rrsig, check_time);

	return result;
}