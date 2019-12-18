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
struct sockaddr {int dummy; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; int /*<<< orphan*/ * ifa_addr; struct ifaddrs* ifa_next; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ cmp_address (int /*<<< orphan*/ *,struct sockaddr const*) ; 
 int errno ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 int getifaddrs (struct ifaddrs**) ; 
 int if_nametoindex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_ifindex(const struct sockaddr *s)
{
	struct ifaddrs *ifaddr, *ifa;
	int name2index = -ENODEV;

	if (-1 == getifaddrs(&ifaddr))
		return errno;

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;

		if (cmp_address(ifa->ifa_addr, s)) {
			name2index = if_nametoindex(ifa->ifa_name);
			break;
		}
	}

	freeifaddrs(ifaddr);

	return name2index;
}