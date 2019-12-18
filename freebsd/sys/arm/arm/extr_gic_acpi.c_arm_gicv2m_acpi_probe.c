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
 int BUS_PROBE_DEFAULT ; 
 int EINVAL ; 
 scalar_t__ GIC_BUS_ACPI ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gic_get_bus (int /*<<< orphan*/ ) ; 
 int gic_get_hw_rev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_gicv2m_acpi_probe(device_t dev)
{

	if (gic_get_bus(dev) != GIC_BUS_ACPI)
		return (EINVAL);

	if (gic_get_hw_rev(dev) > 2)
		return (EINVAL);

	device_set_desc(dev, "ARM Generic Interrupt Controller MSI/MSIX");
	return (BUS_PROBE_DEFAULT);
}