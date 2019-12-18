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
typedef  scalar_t__ uint32_t ;
struct sctp_tcb {int /*<<< orphan*/  sctp_ep; } ;
struct sctp_ifa {int /*<<< orphan*/  ifn_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_MOBILITY_BASE ; 
 int /*<<< orphan*/  SCTP_MOBILITY_FASTHANDOFF ; 
 int /*<<< orphan*/  sctp_asconf_nets_cleanup (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_del_local_addr_restricted (struct sctp_tcb*,struct sctp_ifa*) ; 
 scalar_t__ sctp_is_mobility_feature_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_path_check_and_react (struct sctp_tcb*,struct sctp_ifa*) ; 

__attribute__((used)) static void
sctp_asconf_addr_mgmt_ack(struct sctp_tcb *stcb, struct sctp_ifa *addr, uint32_t flag)
{
	/*
	 * do the necessary asoc list work- if we get a failure indication,
	 * leave the address on the assoc's restricted list.  If we get a
	 * success indication, remove the address from the restricted list.
	 */
	/*
	 * Note: this will only occur for ADD_IP_ADDRESS, since
	 * DEL_IP_ADDRESS is never actually added to the list...
	 */
	if (flag) {
		/* success case, so remove from the restricted list */
		sctp_del_local_addr_restricted(stcb, addr);

		if (sctp_is_mobility_feature_on(stcb->sctp_ep,
		    SCTP_MOBILITY_BASE) ||
		    sctp_is_mobility_feature_on(stcb->sctp_ep,
		    SCTP_MOBILITY_FASTHANDOFF)) {
			sctp_path_check_and_react(stcb, addr);
			return;
		}
		/* clear any cached/topologically incorrect source addresses */
		sctp_asconf_nets_cleanup(stcb, addr->ifn_p);
	}
	/* else, leave it on the list */
}