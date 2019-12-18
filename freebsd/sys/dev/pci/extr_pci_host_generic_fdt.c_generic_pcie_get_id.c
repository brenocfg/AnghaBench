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
typedef  uintptr_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  enum pci_id_type { ____Placeholder_pci_id_type } pci_id_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_ID_MSI ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_bus_msimap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,uintptr_t*) ; 
 int /*<<< orphan*/  pci_get_rid (int /*<<< orphan*/ ) ; 
 int pcib_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 

int
generic_pcie_get_id(device_t pci, device_t child, enum pci_id_type type,
    uintptr_t *id)
{
	phandle_t node;
	int err;
	uint32_t rid;
	uint16_t pci_rid;

	if (type != PCI_ID_MSI)
		return (pcib_get_id(pci, child, type, id));

	node = ofw_bus_get_node(pci);
	pci_rid = pci_get_rid(child);

	err = ofw_bus_msimap(node, pci_rid, NULL, &rid);
	if (err != 0)
		return (err);
	*id = rid;

	return (0);
}