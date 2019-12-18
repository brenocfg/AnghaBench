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
struct ifnet {int if_link_state; scalar_t__ if_type; int /*<<< orphan*/  if_xname; scalar_t__ if_lagg; int /*<<< orphan*/  (* if_bridge_linkstate ) (struct ifnet*) ;scalar_t__ if_bridge; scalar_t__ if_carp; int /*<<< orphan*/ * if_l2com; int /*<<< orphan*/ * if_vlantrunk; int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,struct ifnet*,int) ; 
 scalar_t__ IFT_ETHER ; 
 scalar_t__ IFT_L2VLAN ; 
 scalar_t__ IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int LINK_STATE_UP ; 
 int /*<<< orphan*/  carp_linkstate_p (struct ifnet*) ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  devctl_notify (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,...) ; 
 int /*<<< orphan*/  ifnet_link_event ; 
 int /*<<< orphan*/  lagg_linkstate_p (struct ifnet*,int) ; 
 scalar_t__ log_link_state_change ; 
 int /*<<< orphan*/  ng_ether_link_state_p (struct ifnet*,int) ; 
 int /*<<< orphan*/  rt_ifmsg (struct ifnet*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 
 int /*<<< orphan*/  stub2 (struct ifnet*,int) ; 
 int /*<<< orphan*/  stub3 (struct ifnet*) ; 
 int /*<<< orphan*/  stub4 (struct ifnet*) ; 
 int /*<<< orphan*/  stub5 (struct ifnet*,int) ; 
 int /*<<< orphan*/  vlan_link_state_p (struct ifnet*) ; 

__attribute__((used)) static void
do_link_state_change(void *arg, int pending)
{
	struct ifnet *ifp;
	int link_state;

	ifp = arg;
	link_state = ifp->if_link_state;

	CURVNET_SET(ifp->if_vnet);
	rt_ifmsg(ifp);
	if (ifp->if_vlantrunk != NULL)
		(*vlan_link_state_p)(ifp);

	if ((ifp->if_type == IFT_ETHER || ifp->if_type == IFT_L2VLAN) &&
	    ifp->if_l2com != NULL)
		(*ng_ether_link_state_p)(ifp, link_state);
	if (ifp->if_carp)
		(*carp_linkstate_p)(ifp);
	if (ifp->if_bridge)
		ifp->if_bridge_linkstate(ifp);
	if (ifp->if_lagg)
		(*lagg_linkstate_p)(ifp, link_state);

	if (IS_DEFAULT_VNET(curvnet))
		devctl_notify("IFNET", ifp->if_xname,
		    (link_state == LINK_STATE_UP) ? "LINK_UP" : "LINK_DOWN",
		    NULL);
	if (pending > 1)
		if_printf(ifp, "%d link states coalesced\n", pending);
	if (log_link_state_change)
		if_printf(ifp, "link state changed to %s\n",
		    (link_state == LINK_STATE_UP) ? "UP" : "DOWN" );
	EVENTHANDLER_INVOKE(ifnet_link_event, ifp, link_state);
	CURVNET_RESTORE();
}