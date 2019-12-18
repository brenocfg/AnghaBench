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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct rtentry {int rt_flags; struct ifnet* rt_ifp; scalar_t__ rt_gateway; } ;
struct rt_addrinfo {int dummy; } ;
struct nd_defrouter {int /*<<< orphan*/  installed; } ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RTF_GATEWAY ; 
#define  RTM_ADD 129 
#define  RTM_DELETE 128 
 TYPE_1__* SIN6 (int /*<<< orphan*/ ) ; 
 struct nd_defrouter* defrouter_lookup (int /*<<< orphan*/ *,struct ifnet*) ; 
 int /*<<< orphan*/  defrouter_rele (struct nd_defrouter*) ; 
 int /*<<< orphan*/  in6addr_any ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 

void
nd6_rtrequest(int req, struct rtentry *rt, struct rt_addrinfo *info)
{
	struct sockaddr_in6 *gateway;
	struct nd_defrouter *dr;
	struct ifnet *ifp;

	gateway = (struct sockaddr_in6 *)rt->rt_gateway;
	ifp = rt->rt_ifp;

	switch (req) {
	case RTM_ADD:
		break;

	case RTM_DELETE:
		if (!ifp)
			return;
		/*
		 * Only indirect routes are interesting.
		 */
		if ((rt->rt_flags & RTF_GATEWAY) == 0)
			return;
		/*
		 * check for default route
		 */
		if (IN6_ARE_ADDR_EQUAL(&in6addr_any,
		    &SIN6(rt_key(rt))->sin6_addr)) {
			dr = defrouter_lookup(&gateway->sin6_addr, ifp);
			if (dr != NULL) {
				dr->installed = 0;
				defrouter_rele(dr);
			}
		}
		break;
	}
}