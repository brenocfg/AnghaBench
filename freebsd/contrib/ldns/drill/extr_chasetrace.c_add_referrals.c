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
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_pkt ;
typedef  int /*<<< orphan*/  ldns_dnssec_zone ;

/* Variables and functions */
 int /*<<< orphan*/  add_rr_list_to_referrals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_all_noquestion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_referrals(ldns_dnssec_zone *referrals, ldns_pkt *p)
{
	ldns_rr_list *l = ldns_pkt_all_noquestion(p);
	if (l) {
		add_rr_list_to_referrals(referrals, l);
		ldns_rr_list_free(l);
	}
}