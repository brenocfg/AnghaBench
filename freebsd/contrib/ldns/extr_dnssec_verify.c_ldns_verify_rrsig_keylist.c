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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_keylist_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ldns_status
ldns_verify_rrsig_keylist(ldns_rr_list *rrset,
					 ldns_rr *rrsig,
					 const ldns_rr_list *keys, 
					 ldns_rr_list *good_keys)
{
	return ldns_verify_rrsig_keylist_time(
			rrset, rrsig, keys, ldns_time(NULL), good_keys);
}