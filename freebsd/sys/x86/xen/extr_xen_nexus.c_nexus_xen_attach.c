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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int acpi_cpu_disabled ; 
 int acpi_hpet_disabled ; 
 int /*<<< orphan*/  acpi_install_wakeup_handler (int /*<<< orphan*/ ) ; 
 int acpi_timer_disabled ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nexus_init_resources () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ xen_initial_domain () ; 

__attribute__((used)) static int
nexus_xen_attach(device_t dev)
{
	int error;
	device_t acpi_dev = NULL;

	nexus_init_resources();
	bus_generic_probe(dev);

	if (xen_initial_domain()) {
		/* Disable some ACPI devices that are not usable by Dom0 */
		acpi_cpu_disabled = true;
		acpi_hpet_disabled = true;
		acpi_timer_disabled = true;

		acpi_dev = BUS_ADD_CHILD(dev, 10, "acpi", 0);
		if (acpi_dev == NULL)
			panic("Unable to add ACPI bus to Xen Dom0");
	}

	error = bus_generic_attach(dev);
	if (xen_initial_domain() && (error == 0))
		acpi_install_wakeup_handler(device_get_softc(acpi_dev));

	return (error);
}