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

/* Variables and functions */
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (struct in6_addr const*) ; 
 scalar_t__ IN6_IS_ADDR_LOOPBACK (struct in6_addr const*) ; 
 scalar_t__ IN6_IS_ADDR_MULTICAST (struct in6_addr const*) ; 
 scalar_t__ IN6_IS_ADDR_SITELOCAL (struct in6_addr const*) ; 
 int IPV6_ADDR_MC_SCOPE (struct in6_addr const*) ; 
 int IPV6_ADDR_SCOPE_GLOBAL ; 
 int IPV6_ADDR_SCOPE_LINKLOCAL ; 
 int IPV6_ADDR_SCOPE_SITELOCAL ; 

int
in6_addrscope(const struct in6_addr *addr)
{

	if (IN6_IS_ADDR_MULTICAST(addr)) {
		/*
		 * Addresses with reserved value F must be treated as
		 * global multicast addresses.
		 */
		if (IPV6_ADDR_MC_SCOPE(addr) == 0x0f)
			return (IPV6_ADDR_SCOPE_GLOBAL);
		return (IPV6_ADDR_MC_SCOPE(addr));
	}
	if (IN6_IS_ADDR_LINKLOCAL(addr) ||
	    IN6_IS_ADDR_LOOPBACK(addr))
		return (IPV6_ADDR_SCOPE_LINKLOCAL);
	if (IN6_IS_ADDR_SITELOCAL(addr))
		return (IPV6_ADDR_SCOPE_SITELOCAL);
	return (IPV6_ADDR_SCOPE_GLOBAL);
}