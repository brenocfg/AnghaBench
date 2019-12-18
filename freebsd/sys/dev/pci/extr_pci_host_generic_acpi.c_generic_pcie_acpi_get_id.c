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
typedef  enum pci_id_type { ____Placeholder_pci_id_type } pci_id_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_ID_MSI ; 
 int generic_pcie_map_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 int pcib_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 

__attribute__((used)) static int
generic_pcie_acpi_get_id(device_t pci, device_t child, enum pci_id_type type,
    uintptr_t *id)
{

	if (type == PCI_ID_MSI)
		return (generic_pcie_map_id(pci, child, id));
	else
		return (pcib_get_id(pci, child, type, id));
}