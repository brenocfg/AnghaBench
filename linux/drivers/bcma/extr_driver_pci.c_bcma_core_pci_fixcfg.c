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
typedef  int /*<<< orphan*/  uint ;
typedef  int u16 ;
struct bcma_drv_pci {struct bcma_device* core; } ;
struct bcma_device {scalar_t__ core_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCI_SPROM (int /*<<< orphan*/ ) ; 
 int BCMA_CORE_PCI_SPROM_PI_MASK ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_SPROM_PI_OFFSET ; 
 int BCMA_CORE_PCI_SPROM_PI_SHIFT ; 
 int pcicore_read16 (struct bcma_drv_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcicore_write16 (struct bcma_drv_pci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcma_core_pci_fixcfg(struct bcma_drv_pci *pc)
{
	struct bcma_device *core = pc->core;
	u16 val16, core_index;
	uint regoff;

	regoff = BCMA_CORE_PCI_SPROM(BCMA_CORE_PCI_SPROM_PI_OFFSET);
	core_index = (u16)core->core_index;

	val16 = pcicore_read16(pc, regoff);
	if (((val16 & BCMA_CORE_PCI_SPROM_PI_MASK) >> BCMA_CORE_PCI_SPROM_PI_SHIFT)
	     != core_index) {
		val16 = (core_index << BCMA_CORE_PCI_SPROM_PI_SHIFT) |
			(val16 & ~BCMA_CORE_PCI_SPROM_PI_MASK);
		pcicore_write16(pc, regoff, val16);
	}
}