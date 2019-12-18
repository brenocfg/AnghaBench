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

/* Variables and functions */
 scalar_t__ LDNS_STATUS_MEM_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_rr_list_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 scalar_t__ ldns_rrsig_check_timestamps (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_verify_rrsig_keylist_notime (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

ldns_status
ldns_verify_rrsig_keylist_time(
		const ldns_rr_list *rrset,
		const ldns_rr *rrsig,
		const ldns_rr_list *keys, 
		time_t check_time,
		ldns_rr_list *good_keys)
{
	ldns_status result;
	ldns_rr_list *valid = ldns_rr_list_new();
	if (!valid)
		return LDNS_STATUS_MEM_ERR;

	result = ldns_verify_rrsig_keylist_notime(rrset, rrsig, keys, valid);
	if(result != LDNS_STATUS_OK) {
		ldns_rr_list_free(valid); 
		return result;
	}

	/* check timestamps last; its OK except time */
	result = ldns_rrsig_check_timestamps(rrsig, check_time);
	if(result != LDNS_STATUS_OK) {
		ldns_rr_list_free(valid); 
		return result;
	}

	ldns_rr_list_cat(good_keys, valid);
	ldns_rr_list_free(valid);
	return LDNS_STATUS_OK;
}