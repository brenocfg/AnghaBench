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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {int sin6_len; struct in6_addr sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct route_in6 {TYPE_1__* ro_rt; scalar_t__ ro_mtu; int /*<<< orphan*/  ro_dst; } ;
struct nhop6_basic {scalar_t__ nh_mtu; } ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {scalar_t__ rt_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (struct in6_addr*,struct in6_addr const*) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 scalar_t__ fib6_lookup_nh_basic (int /*<<< orphan*/ ,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nhop6_basic*) ; 
 int /*<<< orphan*/  in6_splitscope (struct in6_addr const*,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int ip6_calcmtu (struct ifnet*,struct in6_addr const*,scalar_t__,scalar_t__*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip6_getpmtu(struct route_in6 *ro_pmtu, int do_lookup,
    struct ifnet *ifp, const struct in6_addr *dst, u_long *mtup,
    int *alwaysfragp, u_int fibnum, u_int proto)
{
	struct nhop6_basic nh6;
	struct in6_addr kdst;
	uint32_t scopeid;
	struct sockaddr_in6 *sa6_dst;
	u_long mtu;

	mtu = 0;
	if (do_lookup) {

		/*
		 * Here ro_pmtu has final destination address, while
		 * ro might represent immediate destination.
		 * Use ro_pmtu destination since mtu might differ.
		 */
		sa6_dst = (struct sockaddr_in6 *)&ro_pmtu->ro_dst;
		if (!IN6_ARE_ADDR_EQUAL(&sa6_dst->sin6_addr, dst))
			ro_pmtu->ro_mtu = 0;

		if (ro_pmtu->ro_mtu == 0) {
			bzero(sa6_dst, sizeof(*sa6_dst));
			sa6_dst->sin6_family = AF_INET6;
			sa6_dst->sin6_len = sizeof(struct sockaddr_in6);
			sa6_dst->sin6_addr = *dst;

			in6_splitscope(dst, &kdst, &scopeid);
			if (fib6_lookup_nh_basic(fibnum, &kdst, scopeid, 0, 0,
			    &nh6) == 0)
				ro_pmtu->ro_mtu = nh6.nh_mtu;
		}

		mtu = ro_pmtu->ro_mtu;
	}

	if (ro_pmtu->ro_rt)
		mtu = ro_pmtu->ro_rt->rt_mtu;

	return (ip6_calcmtu(ifp, dst, mtu, mtup, alwaysfragp, proto));
}