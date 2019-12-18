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
struct nd_ifinfo {int initialized; int /*<<< orphan*/  flags; int /*<<< orphan*/  retrans; int /*<<< orphan*/  basereachable; int /*<<< orphan*/  reachable; int /*<<< orphan*/  chlim; } ;
struct ifnet {scalar_t__ if_type; int if_flags; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 scalar_t__ IFT_BRIDGE ; 
 int /*<<< orphan*/  IPV6_DEFHLIM ; 
 int /*<<< orphan*/  M_IP6NDP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  ND6_IFF_ACCEPT_RTADV ; 
 int /*<<< orphan*/  ND6_IFF_AUTO_LINKLOCAL ; 
 int /*<<< orphan*/  ND6_IFF_NO_RADR ; 
 int /*<<< orphan*/  ND6_IFF_PERFORMNUD ; 
 int /*<<< orphan*/  ND_COMPUTE_RTIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REACHABLE_TIME ; 
 int /*<<< orphan*/  RETRANS_TIMER ; 
 scalar_t__ V_ip6_accept_rtadv ; 
 scalar_t__ V_ip6_auto_linklocal ; 
 scalar_t__ V_ip6_no_radr ; 
 struct nd_ifinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nd6_setmtu0 (struct ifnet*,struct nd_ifinfo*) ; 

struct nd_ifinfo *
nd6_ifattach(struct ifnet *ifp)
{
	struct nd_ifinfo *nd;

	nd = malloc(sizeof(*nd), M_IP6NDP, M_WAITOK | M_ZERO);
	nd->initialized = 1;

	nd->chlim = IPV6_DEFHLIM;
	nd->basereachable = REACHABLE_TIME;
	nd->reachable = ND_COMPUTE_RTIME(nd->basereachable);
	nd->retrans = RETRANS_TIMER;

	nd->flags = ND6_IFF_PERFORMNUD;

	/* A loopback interface always has ND6_IFF_AUTO_LINKLOCAL.
	 * XXXHRS: Clear ND6_IFF_AUTO_LINKLOCAL on an IFT_BRIDGE interface by
	 * default regardless of the V_ip6_auto_linklocal configuration to
	 * give a reasonable default behavior.
	 */
	if ((V_ip6_auto_linklocal && ifp->if_type != IFT_BRIDGE) ||
	    (ifp->if_flags & IFF_LOOPBACK))
		nd->flags |= ND6_IFF_AUTO_LINKLOCAL;
	/*
	 * A loopback interface does not need to accept RTADV.
	 * XXXHRS: Clear ND6_IFF_ACCEPT_RTADV on an IFT_BRIDGE interface by
	 * default regardless of the V_ip6_accept_rtadv configuration to
	 * prevent the interface from accepting RA messages arrived
	 * on one of the member interfaces with ND6_IFF_ACCEPT_RTADV.
	 */
	if (V_ip6_accept_rtadv &&
	    !(ifp->if_flags & IFF_LOOPBACK) &&
	    (ifp->if_type != IFT_BRIDGE))
			nd->flags |= ND6_IFF_ACCEPT_RTADV;
	if (V_ip6_no_radr && !(ifp->if_flags & IFF_LOOPBACK))
		nd->flags |= ND6_IFF_NO_RADR;

	/* XXX: we cannot call nd6_setmtu since ifp is not fully initialized */
	nd6_setmtu0(ifp, nd);

	return nd;
}