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
struct pci_bus {int /*<<< orphan*/  self; } ;

/* Variables and functions */
 int iommu_table_iobmap_inited ; 
 int /*<<< orphan*/  iommu_table_iobmap_setup () ; 
 int /*<<< orphan*/  pr_debug (char*,struct pci_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_dma_bus_setup_pasemi(struct pci_bus *bus)
{
	pr_debug("pci_dma_bus_setup, bus %p, bus->self %p\n", bus, bus->self);

	if (!iommu_table_iobmap_inited) {
		iommu_table_iobmap_inited = 1;
		iommu_table_iobmap_setup();
	}
}