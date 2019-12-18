#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sin6_addr; } ;
struct in6_ifaddr {int ia6_flags; TYPE_1__ ia_addr; } ;
struct ifaddr {TYPE_2__* ifa_ifp; } ;
struct epoch_tracker {int dummy; } ;
struct dadq {int /*<<< orphan*/  dad_refcnt; scalar_t__ dad_loopbackprobe; scalar_t__ dad_ns_lcount; scalar_t__ dad_ns_tcount; scalar_t__ dad_ns_ocount; scalar_t__ dad_na_icount; scalar_t__ dad_ns_icount; scalar_t__ dad_count; struct ifaddr* dad_ifa; int /*<<< orphan*/  dad_vnet; int /*<<< orphan*/  dad_timer_ch; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {int if_flags; int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int IN6_IFF_ANYCAST ; 
 int IN6_IFF_TENTATIVE ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  M_IP6NDP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int ND6_IFF_IFDISABLED ; 
 int ND6_IFF_NO_DAD ; 
 TYPE_3__* ND_IFINFO (TYPE_2__*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 scalar_t__ V_ip6_dad_count ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curvnet ; 
 char* if_name (TYPE_2__*) ; 
 int /*<<< orphan*/  ifa_ref (struct ifaddr*) ; 
 int /*<<< orphan*/  ip6_sprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 struct dadq* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nd6_dad_add (struct dadq*) ; 
 struct dadq* nd6_dad_find (struct ifaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nd6_dad_rele (struct dadq*) ; 
 int /*<<< orphan*/  nd6_dad_starttimer (struct dadq*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 

void
nd6_dad_start(struct ifaddr *ifa, int delay)
{
	struct in6_ifaddr *ia = (struct in6_ifaddr *)ifa;
	struct dadq *dp;
	char ip6buf[INET6_ADDRSTRLEN];
	struct epoch_tracker et;

	KASSERT((ia->ia6_flags & IN6_IFF_TENTATIVE) != 0,
	    ("starting DAD on non-tentative address %p", ifa));

	/*
	 * If we don't need DAD, don't do it.
	 * There are several cases:
	 * - DAD is disabled globally or on the interface
	 * - the interface address is anycast
	 */
	if ((ia->ia6_flags & IN6_IFF_ANYCAST) != 0 ||
	    V_ip6_dad_count == 0 ||
	    (ND_IFINFO(ifa->ifa_ifp)->flags & ND6_IFF_NO_DAD) != 0) {
		ia->ia6_flags &= ~IN6_IFF_TENTATIVE;
		return;
	}
	if ((ifa->ifa_ifp->if_flags & IFF_UP) == 0 ||
	    (ifa->ifa_ifp->if_drv_flags & IFF_DRV_RUNNING) == 0 ||
	    (ND_IFINFO(ifa->ifa_ifp)->flags & ND6_IFF_IFDISABLED) != 0)
		return;

	if ((dp = nd6_dad_find(ifa, NULL)) != NULL) {
		/*
		 * DAD is already in progress.  Let the existing entry
		 * finish it.
		 */
		nd6_dad_rele(dp);
		return;
	}

	dp = malloc(sizeof(*dp), M_IP6NDP, M_NOWAIT | M_ZERO);
	if (dp == NULL) {
		log(LOG_ERR, "nd6_dad_start: memory allocation failed for "
			"%s(%s)\n",
			ip6_sprintf(ip6buf, &ia->ia_addr.sin6_addr),
			ifa->ifa_ifp ? if_name(ifa->ifa_ifp) : "???");
		return;
	}
	callout_init(&dp->dad_timer_ch, 0);
#ifdef VIMAGE
	dp->dad_vnet = curvnet;
#endif
	nd6log((LOG_DEBUG, "%s: starting DAD for %s\n", if_name(ifa->ifa_ifp),
	    ip6_sprintf(ip6buf, &ia->ia_addr.sin6_addr)));

	/*
	 * Send NS packet for DAD, ip6_dad_count times.
	 * Note that we must delay the first transmission, if this is the
	 * first packet to be sent from the interface after interface
	 * (re)initialization.
	 */
	dp->dad_ifa = ifa;
	ifa_ref(dp->dad_ifa);
	dp->dad_count = V_ip6_dad_count;
	dp->dad_ns_icount = dp->dad_na_icount = 0;
	dp->dad_ns_ocount = dp->dad_ns_tcount = 0;
	dp->dad_ns_lcount = dp->dad_loopbackprobe = 0;

	/* Add this to the dadq and add a reference for the dadq. */
	refcount_init(&dp->dad_refcnt, 1);
	nd6_dad_add(dp);
	NET_EPOCH_ENTER(et);
	nd6_dad_starttimer(dp, delay, 0);
	NET_EPOCH_EXIT(et);
}