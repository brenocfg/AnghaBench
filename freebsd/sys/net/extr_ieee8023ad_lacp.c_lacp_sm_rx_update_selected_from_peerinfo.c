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
struct lacp_port {int /*<<< orphan*/  lp_selected; TYPE_1__ lp_partner; } ;
struct lacp_peerinfo {int /*<<< orphan*/  lip_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_STATE_AGGREGATION ; 
 int /*<<< orphan*/  LACP_STATE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LACP_TRACE (struct lacp_port*) ; 
 int /*<<< orphan*/  LACP_UNSELECTED ; 
 scalar_t__ lacp_compare_peerinfo (TYPE_1__*,struct lacp_peerinfo const*) ; 

__attribute__((used)) static void
lacp_sm_rx_update_selected_from_peerinfo(struct lacp_port *lp,
    const struct lacp_peerinfo *info)
{

	LACP_TRACE(lp);

	if (lacp_compare_peerinfo(&lp->lp_partner, info) ||
	    !LACP_STATE_EQ(lp->lp_partner.lip_state, info->lip_state,
	    LACP_STATE_AGGREGATION)) {
		lp->lp_selected = LACP_UNSELECTED;
		/* mux machine will clean up lp->lp_aggregator */
	}
}