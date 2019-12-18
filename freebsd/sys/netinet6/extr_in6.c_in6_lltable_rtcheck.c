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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct nhop6_basic {int nh_flags; struct ifnet* nh_ifp; } ;
struct in6_addr {int dummy; } ;
struct ifnet {int if_fib; } ;
struct ifaddr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 int NHF_GATEWAY ; 
 int RT_DEFAULT_FIB ; 
 scalar_t__ V_rt_add_addr_allfibs ; 
 int fib6_lookup_nh_basic (int,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nhop6_basic*) ; 
 struct ifaddr* ifaof_ifpforaddr (struct sockaddr const*,struct ifnet*) ; 
 int /*<<< orphan*/  in6_splitscope (int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_sprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
in6_lltable_rtcheck(struct ifnet *ifp,
		    u_int flags,
		    const struct sockaddr *l3addr)
{
	const struct sockaddr_in6 *sin6;
	struct nhop6_basic nh6;
	struct in6_addr dst;
	uint32_t scopeid;
	int error;
	char ip6buf[INET6_ADDRSTRLEN];
	int fibnum;

	NET_EPOCH_ASSERT();
	KASSERT(l3addr->sa_family == AF_INET6,
	    ("sin_family %d", l3addr->sa_family));

	sin6 = (const struct sockaddr_in6 *)l3addr;
	in6_splitscope(&sin6->sin6_addr, &dst, &scopeid);
	fibnum = V_rt_add_addr_allfibs ? RT_DEFAULT_FIB : ifp->if_fib;
	error = fib6_lookup_nh_basic(fibnum, &dst, scopeid, 0, 0, &nh6);
	if (error != 0 || (nh6.nh_flags & NHF_GATEWAY) || nh6.nh_ifp != ifp) {
		struct ifaddr *ifa;
		/*
		 * Create an ND6 cache for an IPv6 neighbor
		 * that is not covered by our own prefix.
		 */
		ifa = ifaof_ifpforaddr(l3addr, ifp);
		if (ifa != NULL) {
			return 0;
		}
		log(LOG_INFO, "IPv6 address: \"%s\" is not on the network\n",
		    ip6_sprintf(ip6buf, &sin6->sin6_addr));
		return EINVAL;
	}
	return 0;
}