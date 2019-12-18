#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_dnssec_zone ;
struct TYPE_4__ {TYPE_2__* rrs; } ;
typedef  TYPE_1__ ldns_dnssec_rrsets ;
struct TYPE_5__ {int /*<<< orphan*/  rr; struct TYPE_5__* next; } ;
typedef  TYPE_2__ ldns_dnssec_rrs ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  ldns_dnssec_zone_add_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ldns_dnssec_zone_find_rrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ldns_rr_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int verbosity ; 

__attribute__((used)) static void add_rr_list_to_referrals(
    ldns_dnssec_zone *referrals, ldns_rr_list *rr_list)
{
	size_t i;
	ldns_rr *rr;
	ldns_dnssec_rrsets *rrset;
	ldns_dnssec_rrs *rrs;

	for (i = 0; i < ldns_rr_list_rr_count(rr_list); i++) {
		rr = ldns_rr_list_rr(rr_list, i);
		/* Check if a RR equal to "rr" is present in "referrals" */
		rrset = ldns_dnssec_zone_find_rrset(
		    referrals, ldns_rr_owner(rr), ldns_rr_get_type(rr));
		if (rrset) {
			for (rrs = rrset->rrs; rrs; rrs = rrs->next)
				if (ldns_rr_compare(rr, rrs->rr) == 0)
					break;
			if (rrs) continue; /* "rr" is present, next! */
		}
		if (ldns_rr_get_type(rr) == LDNS_RR_TYPE_NS && verbosity != -1)
			ldns_rr_print(stdout, rr);
		(void) ldns_dnssec_zone_add_rr(referrals, rr);
	}
}