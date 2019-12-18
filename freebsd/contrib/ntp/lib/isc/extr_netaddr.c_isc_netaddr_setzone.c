#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_uint32_t ;
struct TYPE_3__ {scalar_t__ family; int /*<<< orphan*/  zone; } ;
typedef  TYPE_1__ isc_netaddr_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  REQUIRE (int) ; 

void
isc_netaddr_setzone(isc_netaddr_t *netaddr, isc_uint32_t zone) {
	/* we currently only support AF_INET6. */
	REQUIRE(netaddr->family == AF_INET6);

	netaddr->zone = zone;
}