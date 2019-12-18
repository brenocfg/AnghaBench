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
typedef  enum pci_id_type { ____Placeholder_pci_id_type } pci_id_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int PCI_ID_MSI ; 
 int PCI_RID_DOMAIN_SHIFT ; 
 int generic_pcie_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int pci_get_domain (int /*<<< orphan*/ ) ; 
 int pci_get_rid (int /*<<< orphan*/ ) ; 
 int pcib_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 

__attribute__((used)) static int
thunder_pcie_fdt_get_id(device_t pci, device_t child, enum pci_id_type type,
    uintptr_t *id)
{
	phandle_t node;
	int bsf;

	if (type != PCI_ID_MSI)
		return (pcib_get_id(pci, child, type, id));

	node = ofw_bus_get_node(pci);
	if (OF_hasprop(node, "msi-map"))
		return (generic_pcie_get_id(pci, child, type, id));

	bsf = pci_get_rid(child);
	*id = (pci_get_domain(child) << PCI_RID_DOMAIN_SHIFT) | bsf;

	return (0);
}