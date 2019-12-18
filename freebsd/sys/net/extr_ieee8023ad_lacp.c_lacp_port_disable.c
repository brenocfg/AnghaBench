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
struct lacp_port {int /*<<< orphan*/  lp_state; TYPE_1__ lp_partner; int /*<<< orphan*/  lp_selected; } ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_MUX_DETACHED ; 
 int /*<<< orphan*/  LACP_STATE_AGGREGATION ; 
 int /*<<< orphan*/  LACP_STATE_EXPIRED ; 
 int /*<<< orphan*/  LACP_UNSELECTED ; 
 int /*<<< orphan*/  lacp_set_mux (struct lacp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lacp_sm_rx_record_default (struct lacp_port*) ; 

__attribute__((used)) static void
lacp_port_disable(struct lacp_port *lp)
{
	lacp_set_mux(lp, LACP_MUX_DETACHED);

	lp->lp_state &= ~LACP_STATE_AGGREGATION;
	lp->lp_selected = LACP_UNSELECTED;
	lacp_sm_rx_record_default(lp);
	lp->lp_partner.lip_state &= ~LACP_STATE_AGGREGATION;
	lp->lp_state &= ~LACP_STATE_EXPIRED;
}