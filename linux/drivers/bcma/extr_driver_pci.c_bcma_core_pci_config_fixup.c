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
struct bcma_drv_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCI_SPROM (int /*<<< orphan*/ ) ; 
 int BCMA_CORE_PCI_SPROM_L23READY_EXIT_NOPERST ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_SPROM_MISC_CONFIG ; 
 int pcicore_read16 (struct bcma_drv_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcicore_write16 (struct bcma_drv_pci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcma_core_pci_config_fixup(struct bcma_drv_pci *pc)
{
	u16 val16;
	uint regoff;

	regoff = BCMA_CORE_PCI_SPROM(BCMA_CORE_PCI_SPROM_MISC_CONFIG);

	val16 = pcicore_read16(pc, regoff);

	if (!(val16 & BCMA_CORE_PCI_SPROM_L23READY_EXIT_NOPERST)) {
		val16 |= BCMA_CORE_PCI_SPROM_L23READY_EXIT_NOPERST;
		pcicore_write16(pc, regoff, val16);
	}
}