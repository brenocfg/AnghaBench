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
struct TYPE_2__ {int flags; } ;
struct in6_ndireq {TYPE_1__ ndi; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; } ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ifconfig_get_nd6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct in6_ndireq*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
print_nd6(ifconfig_handle_t *lifh, struct ifaddrs *ifa)
{
	struct in6_ndireq nd;

	if (ifconfig_get_nd6(lifh, ifa->ifa_name, &nd) == 0) {
		printf("\tnd6 options=%x\n", nd.ndi.flags);
	} else {
		err(1, "Failed to get nd6 options");
	}
}