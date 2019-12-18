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
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_pkt_edns_udp_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_set_edns_udp_size (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ldns_pkt_tc (int /*<<< orphan*/ *) ; 
 size_t* ldns_resolver_backup_rtt (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_fallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_restore_rtt (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  ldns_resolver_set_usevc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_resolver_usevc (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_send (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ldns_status
ldns_resolver_send_pkt(ldns_pkt **answer, ldns_resolver *r,
				   ldns_pkt *query_pkt)
{
	ldns_pkt *answer_pkt = NULL;
	ldns_status stat = LDNS_STATUS_OK;
	size_t *rtt;

	stat = ldns_send(&answer_pkt, (ldns_resolver *)r, query_pkt);
	if (stat != LDNS_STATUS_OK) {
		if(answer_pkt) {
			ldns_pkt_free(answer_pkt);
			answer_pkt = NULL;
		}
	} else {
		/* if tc=1 fall back to EDNS and/or TCP */
		/* check for tcp first (otherwise we don't care about tc=1) */
		if (!ldns_resolver_usevc(r) && ldns_resolver_fallback(r)) {
			if (ldns_pkt_tc(answer_pkt)) {
				/* was EDNS0 set? */
				if (ldns_pkt_edns_udp_size(query_pkt) == 0) {
					ldns_pkt_set_edns_udp_size(query_pkt
							, 4096);
					ldns_pkt_free(answer_pkt);
					answer_pkt = NULL;
					/* Nameservers should not become 
					 * unreachable because fragments are
					 * dropped (network error). We might
					 * still have success with TCP.
					 * Therefore maintain reachability
					 * statuses of the nameservers by
					 * backup and restore the rtt list.
					 */
					rtt = ldns_resolver_backup_rtt(r);
					stat = ldns_send(&answer_pkt, r
							, query_pkt);
					ldns_resolver_restore_rtt(r, rtt);
				}
				/* either way, if it is still truncated, use TCP */
				if (stat != LDNS_STATUS_OK ||
				    ldns_pkt_tc(answer_pkt)) {
					ldns_resolver_set_usevc(r, true);
					ldns_pkt_free(answer_pkt);
					stat = ldns_send(&answer_pkt, r, query_pkt);
					ldns_resolver_set_usevc(r, false);
				}
			}
		}
	}

	if (answer) {
		*answer = answer_pkt;
	}

	return stat;
}