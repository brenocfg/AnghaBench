#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int lip_state; } ;
struct lacp_port {int lp_state; TYPE_1__ lp_partner; } ;

/* Variables and functions */
 int LACP_FAST_PERIODIC_TIME ; 
 int LACP_SLOW_PERIODIC_TIME ; 
 int LACP_STATE_ACTIVITY ; 
 int LACP_STATE_TIMEOUT ; 
 int /*<<< orphan*/  LACP_TIMER_ARM (struct lacp_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LACP_TIMER_DISARM (struct lacp_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ LACP_TIMER_ISARMED (struct lacp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LACP_TIMER_PERIODIC ; 

__attribute__((used)) static void
lacp_sm_ptx_tx_schedule(struct lacp_port *lp)
{
	int timeout;

	if (!(lp->lp_state & LACP_STATE_ACTIVITY) &&
	    !(lp->lp_partner.lip_state & LACP_STATE_ACTIVITY)) {

		/*
		 * NO_PERIODIC
		 */

		LACP_TIMER_DISARM(lp, LACP_TIMER_PERIODIC);
		return;
	}

	if (LACP_TIMER_ISARMED(lp, LACP_TIMER_PERIODIC)) {
		return;
	}

	timeout = (lp->lp_partner.lip_state & LACP_STATE_TIMEOUT) ?
	    LACP_FAST_PERIODIC_TIME : LACP_SLOW_PERIODIC_TIME;

	LACP_TIMER_ARM(lp, LACP_TIMER_PERIODIC, timeout);
}