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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int lip_state; } ;
struct lacp_port {TYPE_1__ lp_partner; } ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_DPRINTF (struct lacp_port*) ; 
 scalar_t__ LACP_STATE_EQ (int /*<<< orphan*/ ,int,int) ; 
 int LACP_STATE_TIMEOUT ; 
 int /*<<< orphan*/  LACP_TIMER_DISARM (struct lacp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LACP_TIMER_PERIODIC ; 
 int /*<<< orphan*/  lacp_sm_assert_ntt (struct lacp_port*) ; 

__attribute__((used)) static void
lacp_sm_ptx_update_timeout(struct lacp_port *lp, uint8_t oldpstate)
{
	if (LACP_STATE_EQ(oldpstate, lp->lp_partner.lip_state,
	    LACP_STATE_TIMEOUT)) {
		return;
	}

	LACP_DPRINTF((lp, "partner timeout changed\n"));

	/*
	 * FAST_PERIODIC -> SLOW_PERIODIC
	 * or
	 * SLOW_PERIODIC (-> PERIODIC_TX) -> FAST_PERIODIC
	 *
	 * let lacp_sm_ptx_tx_schedule to update timeout.
	 */

	LACP_TIMER_DISARM(lp, LACP_TIMER_PERIODIC);

	/*
	 * if timeout has been shortened, assert NTT.
	 */

	if ((lp->lp_partner.lip_state & LACP_STATE_TIMEOUT)) {
		lacp_sm_assert_ntt(lp);
	}
}