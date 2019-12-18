#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lip_systemid; } ;
struct lacpdu {TYPE_1__ ldu_actor; } ;
struct TYPE_4__ {int /*<<< orphan*/  lip_systemid; } ;
struct lacp_port {int lp_state; TYPE_2__ lp_actor; } ;

/* Variables and functions */
 int LACP_LONG_TIMEOUT_TIME ; 
 int LACP_SHORT_TIMEOUT_TIME ; 
 int LACP_STATE_AGGREGATION ; 
 int LACP_STATE_EXPIRED ; 
 int LACP_STATE_TIMEOUT ; 
 int /*<<< orphan*/  LACP_TIMER_ARM (struct lacp_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LACP_TIMER_CURRENT_WHILE ; 
 int /*<<< orphan*/  lacp_compare_systemid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lacp_sm_rx_record_pdu (struct lacp_port*,struct lacpdu const*) ; 
 int /*<<< orphan*/  lacp_sm_rx_update_ntt (struct lacp_port*,struct lacpdu const*) ; 
 int /*<<< orphan*/  lacp_sm_rx_update_selected (struct lacp_port*,struct lacpdu const*) ; 
 int /*<<< orphan*/  lacp_sm_tx (struct lacp_port*) ; 

__attribute__((used)) static void
lacp_sm_rx(struct lacp_port *lp, const struct lacpdu *du)
{
	int timeout;

	/*
	 * check LACP_DISABLED first
	 */

	if (!(lp->lp_state & LACP_STATE_AGGREGATION)) {
		return;
	}

	/*
	 * check loopback condition.
	 */

	if (!lacp_compare_systemid(&du->ldu_actor.lip_systemid,
	    &lp->lp_actor.lip_systemid)) {
		return;
	}

	/*
	 * EXPIRED, DEFAULTED, CURRENT -> CURRENT
	 */

	lacp_sm_rx_update_selected(lp, du);
	lacp_sm_rx_update_ntt(lp, du);
	lacp_sm_rx_record_pdu(lp, du);

	timeout = (lp->lp_state & LACP_STATE_TIMEOUT) ?
	    LACP_SHORT_TIMEOUT_TIME : LACP_LONG_TIMEOUT_TIME;
	LACP_TIMER_ARM(lp, LACP_TIMER_CURRENT_WHILE, timeout);

	lp->lp_state &= ~LACP_STATE_EXPIRED;

	/*
	 * kick transmit machine without waiting the next tick.
	 */

	lacp_sm_tx(lp);
}