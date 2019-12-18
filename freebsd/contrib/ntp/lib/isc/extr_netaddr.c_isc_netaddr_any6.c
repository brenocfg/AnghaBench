#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  in6; } ;
struct TYPE_6__ {TYPE_1__ type; int /*<<< orphan*/  family; } ;
typedef  TYPE_2__ isc_netaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  in6addr_any ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void
isc_netaddr_any6(isc_netaddr_t *netaddr) {
	memset(netaddr, 0, sizeof(*netaddr));
	netaddr->family = AF_INET6;
	netaddr->type.in6 = in6addr_any;
}