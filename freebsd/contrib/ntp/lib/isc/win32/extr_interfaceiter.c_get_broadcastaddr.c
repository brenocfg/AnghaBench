#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int isc_uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  in; } ;
struct TYPE_7__ {TYPE_1__ type; } ;
typedef  TYPE_2__ isc_netaddr_t ;

/* Variables and functions */

__attribute__((used)) static void
get_broadcastaddr(isc_netaddr_t *bcastaddr, isc_netaddr_t *addr, isc_netaddr_t *netmask) {

	isc_uint32_t *	b;
	isc_uint32_t	a, n;

	b = (isc_uint32_t *)&bcastaddr->type.in;
	a = *(isc_uint32_t *)&addr->type.in;
	n = *(isc_uint32_t *)&netmask->type.in;

	*b = a | ~n;
}