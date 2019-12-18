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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int intr_alloc_msix (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_bus_msimap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_rid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
generic_pcie_fdt_alloc_msix(device_t pci, device_t child, int *irq)
{
#if defined(INTRNG)
	phandle_t msi_parent;
	int err;

	err = ofw_bus_msimap(ofw_bus_get_node(pci), pci_get_rid(child),
	    &msi_parent, NULL);
	if (err != 0)
		return (err);
	return (intr_alloc_msix(pci, child, msi_parent, irq));
#else
	return (ENXIO);
#endif
}