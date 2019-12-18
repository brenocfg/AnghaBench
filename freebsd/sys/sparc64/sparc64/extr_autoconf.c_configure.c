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

/* Variables and functions */
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * isa_bus_device ; 
 int /*<<< orphan*/  root_bus_configure () ; 

__attribute__((used)) static void
configure(void *dummy)
{

	root_bus_configure();
#ifdef DEV_ISA
	/*
	 * We bypass isa_probe_children(9) here in order to avoid
	 * invasive probes done by identify-routines of ISA drivers,
	 * which in turn can trigger master/target aborts, and the
	 * addition of ISA hints, which might erroneously exist.
	 */
	if (isa_bus_device != NULL)
		(void)bus_generic_attach(isa_bus_device);
#endif
}