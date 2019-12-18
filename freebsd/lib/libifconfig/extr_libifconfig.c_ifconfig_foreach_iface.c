#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ifaddrs {char* ifa_name; struct ifaddrs* ifa_next; } ;
struct TYPE_6__ {struct ifaddrs* ifap; } ;
typedef  TYPE_1__ ifconfig_handle_t ;
typedef  int /*<<< orphan*/  (* ifconfig_foreach_func_t ) (TYPE_1__*,struct ifaddrs*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 int ifconfig_getifaddrs (TYPE_1__*) ; 

int
ifconfig_foreach_iface(ifconfig_handle_t *h,
    ifconfig_foreach_func_t cb, void *udata)
{
	int ret;

	ret = ifconfig_getifaddrs(h);
	if (ret == 0) {
		struct ifaddrs *ifa;
		char *ifname = NULL;

		for (ifa = h->ifap; ifa; ifa = ifa->ifa_next) {
			if (ifname != ifa->ifa_name) {
				ifname = ifa->ifa_name;
				cb(h, ifa, udata);
			}
		}
	}
	/* Free ifaddrs so we don't accidentally cache stale data */
	freeifaddrs(h->ifap);
	h->ifap = NULL;

	return (ret);
}