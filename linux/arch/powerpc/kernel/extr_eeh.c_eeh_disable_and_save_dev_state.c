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
struct pci_dev {int dummy; } ;
struct eeh_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_COMMAND_INTX_DISABLE ; 
 int /*<<< orphan*/  PCI_D0 ; 
 struct pci_dev* eeh_dev_to_pci_dev (struct eeh_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eeh_disable_and_save_dev_state(struct eeh_dev *edev,
					    void *userdata)
{
	struct pci_dev *pdev = eeh_dev_to_pci_dev(edev);
	struct pci_dev *dev = userdata;

	/*
	 * The caller should have disabled and saved the
	 * state for the specified device
	 */
	if (!pdev || pdev == dev)
		return;

	/* Ensure we have D0 power state */
	pci_set_power_state(pdev, PCI_D0);

	/* Save device state */
	pci_save_state(pdev);

	/*
	 * Disable device to avoid any DMA traffic and
	 * interrupt from the device
	 */
	pci_write_config_word(pdev, PCI_COMMAND, PCI_COMMAND_INTX_DISABLE);
}