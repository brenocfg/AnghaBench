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
typedef  scalar_t__ u8 ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct ar2315_pci_ctrl {int irq_ext; } ;

/* Variables and functions */
 struct ar2315_pci_ctrl* ar2315_pci_bus_to_apc (int /*<<< orphan*/ ) ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	struct ar2315_pci_ctrl *apc = ar2315_pci_bus_to_apc(dev->bus);

	return slot ? 0 : apc->irq_ext;
}