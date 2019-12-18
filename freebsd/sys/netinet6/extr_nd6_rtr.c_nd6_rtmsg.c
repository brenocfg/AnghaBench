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
struct rtentry {int /*<<< orphan*/  rt_fibnum; int /*<<< orphan*/  rt_flags; TYPE_1__* rt_ifa; struct ifnet* rt_ifp; int /*<<< orphan*/  rt_gateway; } ;
struct rt_addrinfo {int /*<<< orphan*/ * rti_info; } ;
struct ifnet {int /*<<< orphan*/  if_addrhead; } ;
struct ifaddr {int /*<<< orphan*/  ifa_addr; } ;
struct epoch_tracker {int dummy; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  ifa_addr; } ;

/* Variables and functions */
 struct ifaddr* CK_STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 size_t RTAX_IFA ; 
 size_t RTAX_IFP ; 
 size_t RTAX_NETMASK ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifa_free (struct ifaddr*) ; 
 int /*<<< orphan*/  ifa_ref (struct ifaddr*) ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_mask (struct rtentry*) ; 
 int /*<<< orphan*/  rt_missmsg_fib (int,struct rt_addrinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nd6_rtmsg(int cmd, struct rtentry *rt)
{
	struct rt_addrinfo info;
	struct ifnet *ifp;
	struct ifaddr *ifa;

	bzero((caddr_t)&info, sizeof(info));
	info.rti_info[RTAX_DST] = rt_key(rt);
	info.rti_info[RTAX_GATEWAY] = rt->rt_gateway;
	info.rti_info[RTAX_NETMASK] = rt_mask(rt);
	ifp = rt->rt_ifp;
	if (ifp != NULL) {
		struct epoch_tracker et;

		NET_EPOCH_ENTER(et);
		ifa = CK_STAILQ_FIRST(&ifp->if_addrhead);
		info.rti_info[RTAX_IFP] = ifa->ifa_addr;
		ifa_ref(ifa);
		NET_EPOCH_EXIT(et);
		info.rti_info[RTAX_IFA] = rt->rt_ifa->ifa_addr;
	} else
		ifa = NULL;

	rt_missmsg_fib(cmd, &info, rt->rt_flags, 0, rt->rt_fibnum);
	if (ifa != NULL)
		ifa_free(ifa);
}