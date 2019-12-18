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
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_RESET_DEACTIVATE ; 
 int /*<<< orphan*/  EEH_RESET_HOT ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_root_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_eeh_bridge_reset (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnv_eeh_root_reset (struct pci_controller*,int /*<<< orphan*/ ) ; 

void pnv_pci_reset_secondary_bus(struct pci_dev *dev)
{
	struct pci_controller *hose;

	if (pci_is_root_bus(dev->bus)) {
		hose = pci_bus_to_host(dev->bus);
		pnv_eeh_root_reset(hose, EEH_RESET_HOT);
		pnv_eeh_root_reset(hose, EEH_RESET_DEACTIVATE);
	} else {
		pnv_eeh_bridge_reset(dev, EEH_RESET_HOT);
		pnv_eeh_bridge_reset(dev, EEH_RESET_DEACTIVATE);
	}
}