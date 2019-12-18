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
 int /*<<< orphan*/  CPU_IMPL_CAVIUM ; 
 int CPU_IMPL_MASK ; 
 int /*<<< orphan*/  CPU_MATCH (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CPU_PART_MASK ; 
 int /*<<< orphan*/  CPU_PART_THUNDERX ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
thunder_pcie_fdt_probe(device_t dev)
{

	/* Check if we're running on Cavium ThunderX */
	if (!CPU_MATCH(CPU_IMPL_MASK | CPU_PART_MASK,
	    CPU_IMPL_CAVIUM, CPU_PART_THUNDERX, 0, 0))
		return (ENXIO);

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (ofw_bus_is_compatible(dev, "pci-host-ecam-generic") ||
	    ofw_bus_is_compatible(dev, "cavium,thunder-pcie") ||
	    ofw_bus_is_compatible(dev, "cavium,pci-host-thunder-ecam")) {
		device_set_desc(dev, "Cavium Integrated PCI/PCI-E Controller");
		return (BUS_PROBE_DEFAULT);
	}

	return (ENXIO);
}