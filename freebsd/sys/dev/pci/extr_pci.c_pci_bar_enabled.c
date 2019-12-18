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
typedef  int uint16_t ;
struct pci_map {int pm_value; int /*<<< orphan*/  pm_reg; } ;
struct pci_devinfo {int /*<<< orphan*/  cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_BIOS_ENABLE ; 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_PORTEN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 scalar_t__ PCIR_IS_BIOS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_BAR_MEM (int) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
pci_bar_enabled(device_t dev, struct pci_map *pm)
{
	struct pci_devinfo *dinfo;
	uint16_t cmd;

	dinfo = device_get_ivars(dev);
	if (PCIR_IS_BIOS(&dinfo->cfg, pm->pm_reg) &&
	    !(pm->pm_value & PCIM_BIOS_ENABLE))
		return (0);
	cmd = pci_read_config(dev, PCIR_COMMAND, 2);
	if (PCIR_IS_BIOS(&dinfo->cfg, pm->pm_reg) || PCI_BAR_MEM(pm->pm_value))
		return ((cmd & PCIM_CMD_MEMEN) != 0);
	else
		return ((cmd & PCIM_CMD_PORTEN) != 0);
}