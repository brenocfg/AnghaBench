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
struct lacpdu {int /*<<< orphan*/  ldu_actor; } ;
struct lacp_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LACP_TRACE (struct lacp_port*) ; 
 int /*<<< orphan*/  lacp_sm_rx_update_selected_from_peerinfo (struct lacp_port*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lacp_sm_rx_update_selected(struct lacp_port *lp, const struct lacpdu *du)
{

	LACP_TRACE(lp);

	lacp_sm_rx_update_selected_from_peerinfo(lp, &du->ldu_actor);
}