#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct ifaddrs {int ifa_flags; int /*<<< orphan*/  ifa_name; TYPE_2__* ifa_addr; struct ifaddrs* ifa_next; } ;
struct addrinfo {int ai_family; } ;
struct TYPE_4__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNSPEC 128 
 int IFF_UP ; 
 int IFT_LOOP ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LOOPBACK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ifdisabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
addrconfig(struct addrinfo *pai)
{
	struct ifaddrs *ifaddrs, *ifa;
	struct sockaddr_in *sin;
#ifdef INET6
	struct sockaddr_in6 *sin6;
#endif
	int seen_inet = 0, seen_inet6 = 0;

	if (getifaddrs(&ifaddrs) != 0)
		return (0);

	for (ifa = ifaddrs; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL || (ifa->ifa_flags & IFF_UP) == 0)
			continue;
		switch (ifa->ifa_addr->sa_family) {
		case AF_INET:
			if (seen_inet)
				continue;
			sin = (struct sockaddr_in *)(ifa->ifa_addr);
			if (htonl(sin->sin_addr.s_addr) == INADDR_LOOPBACK)
				continue;
			seen_inet = 1;
			break;
#ifdef INET6
		case AF_INET6:
			if (seen_inet6)
				continue;
			sin6 = (struct sockaddr_in6 *)(ifa->ifa_addr);
			if (IN6_IS_ADDR_LOOPBACK(&sin6->sin6_addr))
				continue;
			if ((ifa->ifa_flags & IFT_LOOP) != 0 &&
			    IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr))
				continue;
			if (is_ifdisabled(ifa->ifa_name))
				continue;
			seen_inet6 = 1;
			break;
#endif
		}
	}
	freeifaddrs(ifaddrs);

	switch(pai->ai_family) {
	case AF_INET6:
		return (seen_inet6);
	case AF_INET:
		return (seen_inet);
	case AF_UNSPEC:
		if (seen_inet == seen_inet6)
			return (seen_inet);
		pai->ai_family = seen_inet ? AF_INET : AF_INET6;
		return (1);
	}
	return (1);
}