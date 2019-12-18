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
 int PCI_POWERSTATE_D0 ; 
 int PCI_POWERSTATE_D3 ; 
 int pci_get_powerstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_powerstate (int /*<<< orphan*/ ,int) ; 

int
pci_power_reset(device_t dev)
{
	int ps;

	ps = pci_get_powerstate(dev);
	if (ps != PCI_POWERSTATE_D0 && ps != PCI_POWERSTATE_D3)
		pci_set_powerstate(dev, PCI_POWERSTATE_D0);
	pci_set_powerstate(dev, PCI_POWERSTATE_D3);
	pci_set_powerstate(dev, ps);
	return (0);
}