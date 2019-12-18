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
typedef  int /*<<< orphan*/  ldns_resolver ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_verify_trusted_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ldns_status
ldns_verify_trusted(
		ldns_resolver *res,
		ldns_rr_list *rrset, 
		ldns_rr_list * rrsigs, 
		ldns_rr_list * validating_keys)
{
	return ldns_verify_trusted_time(
			res, rrset, rrsigs, ldns_time(NULL), validating_keys);
}