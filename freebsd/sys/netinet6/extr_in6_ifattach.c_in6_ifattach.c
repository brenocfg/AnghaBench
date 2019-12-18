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
struct in6_ifaddr {int /*<<< orphan*/  ia_ifa; } ;
struct ifnet {int if_type; int if_flags; scalar_t__ if_mtu; int /*<<< orphan*/ ** if_afdata; } ;
struct epoch_tracker {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 size_t AF_INET6 ; 
 int IFF_LOOPBACK ; 
 int IFF_MULTICAST ; 
#define  IFT_STF 128 
 int /*<<< orphan*/  LOG_INFO ; 
 int ND6_IFF_AUTO_LINKLOCAL ; 
 int ND6_IFF_IFDISABLED ; 
 int ND6_IFF_NO_DAD ; 
 TYPE_1__* ND_IFINFO (struct ifnet*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 scalar_t__ V_in6_maxmtu ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifa_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6_ifattach_linklocal (struct ifnet*,struct ifnet*) ; 
 int /*<<< orphan*/  in6_ifattach_loopback (struct ifnet*) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 struct in6_ifaddr* in6ifa_ifpforlinklocal (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct in6_ifaddr* in6ifa_ifwithaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 

void
in6_ifattach(struct ifnet *ifp, struct ifnet *altifp)
{
	struct in6_ifaddr *ia;

	if (ifp->if_afdata[AF_INET6] == NULL)
		return;
	/*
	 * quirks based on interface type
	 */
	switch (ifp->if_type) {
	case IFT_STF:
		/*
		 * 6to4 interface is a very special kind of beast.
		 * no multicast, no linklocal.  RFC2529 specifies how to make
		 * linklocals for 6to4 interface, but there's no use and
		 * it is rather harmful to have one.
		 */
		ND_IFINFO(ifp)->flags &= ~ND6_IFF_AUTO_LINKLOCAL;
		ND_IFINFO(ifp)->flags |= ND6_IFF_NO_DAD;
		break;
	default:
		break;
	}

	/*
	 * usually, we require multicast capability to the interface
	 */
	if ((ifp->if_flags & IFF_MULTICAST) == 0) {
		nd6log((LOG_INFO, "in6_ifattach: "
		    "%s is not multicast capable, IPv6 not enabled\n",
		    if_name(ifp)));
		return;
	}

	/*
	 * assign loopback address for loopback interface.
	 */
	if ((ifp->if_flags & IFF_LOOPBACK) != 0) {
		/*
		 * check that loopback address doesn't exist yet.
		 */
		ia = in6ifa_ifwithaddr(&in6addr_loopback, 0);
		if (ia == NULL)
			in6_ifattach_loopback(ifp);
		else
			ifa_free(&ia->ia_ifa);
	}

	/*
	 * assign a link-local address, if there's none.
	 */
	if (!(ND_IFINFO(ifp)->flags & ND6_IFF_IFDISABLED) &&
	    ND_IFINFO(ifp)->flags & ND6_IFF_AUTO_LINKLOCAL) {
		struct epoch_tracker et;

		NET_EPOCH_ENTER(et);
		ia = in6ifa_ifpforlinklocal(ifp, 0);
		NET_EPOCH_EXIT(et);
		if (ia == NULL)
			in6_ifattach_linklocal(ifp, altifp);
		else
			ifa_free(&ia->ia_ifa);
	}

	/* update dynamically. */
	if (V_in6_maxmtu < ifp->if_mtu)
		V_in6_maxmtu = ifp->if_mtu;
}