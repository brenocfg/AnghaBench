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
struct in6_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (struct in6_addr*) ; 
 int /*<<< orphan*/  rt6_deleteroute ; 
 int /*<<< orphan*/  rt_foreach_fib_walk_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void
rt6_flush(struct in6_addr *gateway, struct ifnet *ifp)
{

	/* We'll care only link-local addresses */
	if (!IN6_IS_ADDR_LINKLOCAL(gateway))
		return;

	/* XXX Do we really need to walk any but the default FIB? */
	rt_foreach_fib_walk_del(AF_INET6, rt6_deleteroute, (void *)gateway);
}