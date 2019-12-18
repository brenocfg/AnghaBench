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
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nexus_init_resources () ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
nexus_acpi_attach(device_t dev)
{

	nexus_init_resources();
	bus_generic_probe(dev);
	if (BUS_ADD_CHILD(dev, 10, "acpi", 0) == NULL)
		panic("failed to add acpi0 device");

	return (bus_generic_attach(dev));
}