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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_pkt_section ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int ldns_pkt_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
ldns_pkt_safe_push_rr(ldns_pkt *pkt, ldns_pkt_section sec, ldns_rr *rr)
{

	/* check to see if its there */
	if (ldns_pkt_rr(pkt, sec, rr)) {
		/* already there */
		return false;
	}
	return ldns_pkt_push_rr(pkt, sec, rr);
}