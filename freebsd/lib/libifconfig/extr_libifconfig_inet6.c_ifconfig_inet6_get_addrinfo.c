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
struct TYPE_2__ {int /*<<< orphan*/  ifru_lifetime; int /*<<< orphan*/  ifru_flags6; } ;
struct in6_ifreq {TYPE_1__ ifr_ifru; struct sockaddr_in6 ifr_addr; int /*<<< orphan*/  ifr_name; } ;
struct ifconfig_inet6_addr {int /*<<< orphan*/  vhid; int /*<<< orphan*/  lifetime; struct sockaddr_in6* sin6; int /*<<< orphan*/  flags; int /*<<< orphan*/  prefixlen; struct sockaddr_in6* dstin6; } ;
struct ifaddrs {int ifa_flags; scalar_t__ ifa_data; scalar_t__ ifa_netmask; scalar_t__ ifa_dstaddr; scalar_t__ ifa_addr; } ;
struct if_data {int /*<<< orphan*/  ifi_vhid; } ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  SIOCGIFAFLAG_IN6 ; 
 int /*<<< orphan*/  SIOCGIFALIFETIME_IN6 ; 
 int /*<<< orphan*/  bzero (struct ifconfig_inet6_addr*,int) ; 
 scalar_t__ ifconfig_ioctlwrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in6_ifreq*) ; 
 int /*<<< orphan*/  inet6_prefixlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int
ifconfig_inet6_get_addrinfo(ifconfig_handle_t *h,
    const char *name, struct ifaddrs *ifa, struct ifconfig_inet6_addr *addr)
{
	struct sockaddr_in6 *netmask;
	struct in6_ifreq ifr6;

	bzero(addr, sizeof(*addr));

	/* Set the address */
	addr->sin6 = (struct sockaddr_in6 *)ifa->ifa_addr;

	/* Set the destination address */
	if (ifa->ifa_flags & IFF_POINTOPOINT) {
		addr->dstin6 = (struct sockaddr_in6 *)ifa->ifa_dstaddr;
	}

	/* Set the prefixlen */
	netmask = (struct sockaddr_in6 *)ifa->ifa_netmask;
	addr->prefixlen = inet6_prefixlen(&netmask->sin6_addr);

	/* Set the flags */
	strlcpy(ifr6.ifr_name, name, sizeof(ifr6.ifr_name));
	ifr6.ifr_addr = *addr->sin6;
	if (ifconfig_ioctlwrap(h, AF_INET6, SIOCGIFAFLAG_IN6, &ifr6) < 0) {
		return (-1);
	}
	addr->flags = ifr6.ifr_ifru.ifru_flags6;

	/* Set the lifetimes */
	memset(&addr->lifetime, 0, sizeof(addr->lifetime));
	ifr6.ifr_addr = *addr->sin6;
	if (ifconfig_ioctlwrap(h, AF_INET6, SIOCGIFALIFETIME_IN6, &ifr6) < 0) {
		return (-1);
	}
	addr->lifetime = ifr6.ifr_ifru.ifru_lifetime; /* struct copy */

	/* Set the vhid */
	if (ifa->ifa_data && ifa->ifa_data) {
		addr->vhid = ((struct if_data *)ifa->ifa_data)->ifi_vhid;
	}

	return (0);
}