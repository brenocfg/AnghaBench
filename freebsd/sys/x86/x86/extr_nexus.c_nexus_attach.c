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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nexus_init_resources () ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
nexus_attach(device_t dev)
{

	nexus_init_resources();
	bus_generic_probe(dev);

	/*
	 * Explicitly add the legacy0 device here.  Other platform
	 * types (such as ACPI), use their own nexus(4) subclass
	 * driver to override this routine and add their own root bus.
	 */
	if (BUS_ADD_CHILD(dev, 10, "legacy", 0) == NULL)
		panic("legacy: could not attach");
	bus_generic_attach(dev);
	return 0;
}