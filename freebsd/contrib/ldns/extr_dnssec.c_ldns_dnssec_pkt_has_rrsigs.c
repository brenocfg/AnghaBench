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
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 size_t ldns_pkt_ancount (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_answer (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_authority (int /*<<< orphan*/  const*) ; 
 size_t ldns_pkt_nscount (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ ,size_t) ; 

bool
ldns_dnssec_pkt_has_rrsigs(const ldns_pkt *pkt)
{
	size_t i;
	for (i = 0; i < ldns_pkt_ancount(pkt); i++) {
		if (ldns_rr_get_type(ldns_rr_list_rr(ldns_pkt_answer(pkt), i)) ==
		    LDNS_RR_TYPE_RRSIG) {
			return true;
		}
	}
	for (i = 0; i < ldns_pkt_nscount(pkt); i++) {
		if (ldns_rr_get_type(ldns_rr_list_rr(ldns_pkt_authority(pkt), i)) ==
		    LDNS_RR_TYPE_RRSIG) {
			return true;
		}
	}
	return false;
}