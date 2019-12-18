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
struct TYPE_2__ {int /*<<< orphan*/  lip_state; } ;
struct lacp_port {int /*<<< orphan*/  lp_state; TYPE_1__ lp_partner; } ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_SHORT_TIMEOUT_TIME ; 
 int /*<<< orphan*/  LACP_STATE_EXPIRED ; 
 int /*<<< orphan*/  LACP_STATE_SYNC ; 
 int /*<<< orphan*/  LACP_STATE_TIMEOUT ; 
 int /*<<< orphan*/  LACP_TIMER_ARM (struct lacp_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LACP_TIMER_CURRENT_WHILE ; 

__attribute__((used)) static void
lacp_sm_rx_set_expired(struct lacp_port *lp)
{
	lp->lp_partner.lip_state &= ~LACP_STATE_SYNC;
	lp->lp_partner.lip_state |= LACP_STATE_TIMEOUT;
	LACP_TIMER_ARM(lp, LACP_TIMER_CURRENT_WHILE, LACP_SHORT_TIMEOUT_TIME);
	lp->lp_state |= LACP_STATE_EXPIRED;
}