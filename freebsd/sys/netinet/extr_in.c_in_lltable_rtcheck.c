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
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr_in {scalar_t__ sa_family; int sin_len; int sa_len; int rti_flags; int rti_addrs; int /*<<< orphan*/  sin_addr; struct ifnet* rti_ifp; int /*<<< orphan*/  sa_data; struct sockaddr_in** rti_info; } ;
struct sockaddr {scalar_t__ sa_family; int sin_len; int sa_len; int rti_flags; int rti_addrs; int /*<<< orphan*/  sin_addr; struct ifnet* rti_ifp; int /*<<< orphan*/  sa_data; struct sockaddr** rti_info; } ;
struct rt_addrinfo {scalar_t__ sa_family; int sin_len; int sa_len; int rti_flags; int rti_addrs; int /*<<< orphan*/  sin_addr; struct ifnet* rti_ifp; int /*<<< orphan*/  sa_data; struct rt_addrinfo** rti_info; } ;
struct ifnet {scalar_t__ if_type; int if_flags; int /*<<< orphan*/  if_fib; } ;
typedef  int /*<<< orphan*/  rt_mask ;
typedef  int /*<<< orphan*/  rt_key ;
typedef  int /*<<< orphan*/  rt_gateway ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EINVAL ; 
 int IFF_NOARP ; 
 int IFF_STATICARP ; 
 scalar_t__ IFT_ETHER ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  NHR_REF ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 size_t RTAX_NETMASK ; 
 int RTA_NETMASK ; 
 int RTF_GATEWAY ; 
 int RTF_HOST ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  inet_ntoa_r (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rib_free_info (struct sockaddr_in*) ; 
 scalar_t__ rib_lookup_info (int /*<<< orphan*/ ,struct sockaddr_in const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_in*) ; 

__attribute__((used)) static int
in_lltable_rtcheck(struct ifnet *ifp, u_int flags, const struct sockaddr *l3addr)
{
	struct rt_addrinfo info;
	struct sockaddr_in rt_key, rt_mask;
	struct sockaddr rt_gateway;
	int rt_flags;

	KASSERT(l3addr->sa_family == AF_INET,
	    ("sin_family %d", l3addr->sa_family));

	bzero(&rt_key, sizeof(rt_key));
	rt_key.sin_len = sizeof(rt_key);
	bzero(&rt_mask, sizeof(rt_mask));
	rt_mask.sin_len = sizeof(rt_mask);
	bzero(&rt_gateway, sizeof(rt_gateway));
	rt_gateway.sa_len = sizeof(rt_gateway);

	bzero(&info, sizeof(info));
	info.rti_info[RTAX_DST] = (struct sockaddr *)&rt_key;
	info.rti_info[RTAX_NETMASK] = (struct sockaddr *)&rt_mask;
	info.rti_info[RTAX_GATEWAY] = (struct sockaddr *)&rt_gateway;

	if (rib_lookup_info(ifp->if_fib, l3addr, NHR_REF, 0, &info) != 0)
		return (EINVAL);

	rt_flags = info.rti_flags;

	/*
	 * If the gateway for an existing host route matches the target L3
	 * address, which is a special route inserted by some implementation
	 * such as MANET, and the interface is of the correct type, then
	 * allow for ARP to proceed.
	 */
	if (rt_flags & RTF_GATEWAY) {
		if (!(rt_flags & RTF_HOST) || !info.rti_ifp ||
		    info.rti_ifp->if_type != IFT_ETHER ||
		    (info.rti_ifp->if_flags & (IFF_NOARP | IFF_STATICARP)) != 0 ||
		    memcmp(rt_gateway.sa_data, l3addr->sa_data,
		    sizeof(in_addr_t)) != 0) {
			rib_free_info(&info);
			return (EINVAL);
		}
	}
	rib_free_info(&info);

	/*
	 * Make sure that at least the destination address is covered
	 * by the route. This is for handling the case where 2 or more
	 * interfaces have the same prefix. An incoming packet arrives
	 * on one interface and the corresponding outgoing packet leaves
	 * another interface.
	 */
	if (!(rt_flags & RTF_HOST) && info.rti_ifp != ifp) {
		const char *sa, *mask, *addr, *lim;
		const struct sockaddr_in *l3sin;

		mask = (const char *)&rt_mask;
		/*
		 * Just being extra cautious to avoid some custom
		 * code getting into trouble.
		 */
		if ((info.rti_addrs & RTA_NETMASK) == 0)
			return (EINVAL);

		sa = (const char *)&rt_key;
		addr = (const char *)l3addr;
		l3sin = (const struct sockaddr_in *)l3addr;
		lim = addr + l3sin->sin_len;

		for ( ; addr < lim; sa++, mask++, addr++) {
			if ((*sa ^ *addr) & *mask) {
#ifdef DIAGNOSTIC
				char addrbuf[INET_ADDRSTRLEN];

				log(LOG_INFO, "IPv4 address: \"%s\" "
				    "is not on the network\n",
				    inet_ntoa_r(l3sin->sin_addr, addrbuf));
#endif
				return (EINVAL);
			}
		}
	}

	return (0);
}