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
struct ifaddrs {struct ifaddrs* ifa_next; int /*<<< orphan*/  ifa_name; int /*<<< orphan*/ * ifa_addr; } ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;
typedef  int /*<<< orphan*/  (* ifconfig_foreach_func_t ) (int /*<<< orphan*/ *,struct ifaddrs*,void*) ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ifconfig_foreach_ifaddr(ifconfig_handle_t *h, struct ifaddrs *ifa,
    ifconfig_foreach_func_t cb, void *udata)
{
	struct ifaddrs *ift;

	for (ift = ifa;
	    ift != NULL &&
	    ift->ifa_addr != NULL &&
	    strcmp(ift->ifa_name, ifa->ifa_name) == 0;
	    ift = ift->ifa_next) {
		cb(h, ift, udata);
	}
}