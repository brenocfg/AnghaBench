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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_RES_BUS ; 
 int bus_generic_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int pci_host_generic_core_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 

__attribute__((used)) static int
generic_pcie_fdt_release_resource(device_t dev, device_t child, int type,
    int rid, struct resource *res)
{

#if defined(NEW_PCIB) && defined(PCI_RES_BUS)
	if (type == PCI_RES_BUS) {
		return (pci_host_generic_core_release_resource(dev, child, type,
		    rid, res));
	}
#endif

	/* For PCIe devices that do not have FDT nodes, use PCIB method */
	if ((int)ofw_bus_get_node(child) <= 0) {
		return (pci_host_generic_core_release_resource(dev, child, type,
		    rid, res));
	}

	/* For other devices use OFW method */
	return (bus_generic_release_resource(dev, child, type, rid, res));
}