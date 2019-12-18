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
struct pci_map {int pm_value; int /*<<< orphan*/  pm_reg; } ;
struct pci_devinfo {int /*<<< orphan*/  cfg; } ;
typedef  int pci_addr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCIR_IS_BIOS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_maprange (int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
pci_write_bar(device_t dev, struct pci_map *pm, pci_addr_t base)
{
	struct pci_devinfo *dinfo;
	int ln2range;

	/* The device ROM BAR is always a 32-bit memory BAR. */
	dinfo = device_get_ivars(dev);
	if (PCIR_IS_BIOS(&dinfo->cfg, pm->pm_reg))
		ln2range = 32;
	else
		ln2range = pci_maprange(pm->pm_value);
	pci_write_config(dev, pm->pm_reg, base, 4);
	if (ln2range == 64)
		pci_write_config(dev, pm->pm_reg + 4, base >> 32, 4);
	pm->pm_value = pci_read_config(dev, pm->pm_reg, 4);
	if (ln2range == 64)
		pm->pm_value |= (pci_addr_t)pci_read_config(dev,
		    pm->pm_reg + 4, 4) << 32;
}