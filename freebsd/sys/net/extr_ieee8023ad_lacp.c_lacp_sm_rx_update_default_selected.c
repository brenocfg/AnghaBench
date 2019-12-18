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
struct lacp_port {TYPE_1__* lp_lsc; } ;
struct TYPE_2__ {scalar_t__ lsc_strict_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_TRACE (struct lacp_port*) ; 
 int /*<<< orphan*/  lacp_partner_admin_optimistic ; 
 int /*<<< orphan*/  lacp_partner_admin_strict ; 
 int /*<<< orphan*/  lacp_sm_rx_update_selected_from_peerinfo (struct lacp_port*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lacp_sm_rx_update_default_selected(struct lacp_port *lp)
{

	LACP_TRACE(lp);

	if (lp->lp_lsc->lsc_strict_mode)
		lacp_sm_rx_update_selected_from_peerinfo(lp,
		    &lacp_partner_admin_strict);
	else
		lacp_sm_rx_update_selected_from_peerinfo(lp,
		    &lacp_partner_admin_optimistic);
}