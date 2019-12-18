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
typedef  int /*<<< orphan*/  isc_portset_t ;
typedef  scalar_t__ in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  portset_remove (int /*<<< orphan*/ *,scalar_t__) ; 

void
isc_portset_removerange(isc_portset_t *portset, in_port_t port_lo,
			in_port_t port_hi)
{
	in_port_t p;

	REQUIRE(portset != NULL);
	REQUIRE(port_lo <= port_hi);

	p = port_lo;
	do {
		portset_remove(portset, p);
	} while (p++ < port_hi);
}