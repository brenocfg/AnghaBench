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
typedef  int /*<<< orphan*/  u32 ;
struct bcma_drv_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_PCI_ASPMTIMER_EXTEND ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_DLLP_PMTHRESHREG ; 
 int /*<<< orphan*/  bcma_pcie_read (struct bcma_drv_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_pcie_write (struct bcma_drv_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcma_core_pci_extend_L1timer(struct bcma_drv_pci *pc, bool extend)
{
	u32 w;

	w = bcma_pcie_read(pc, BCMA_CORE_PCI_DLLP_PMTHRESHREG);
	if (extend)
		w |= BCMA_CORE_PCI_ASPMTIMER_EXTEND;
	else
		w &= ~BCMA_CORE_PCI_ASPMTIMER_EXTEND;
	bcma_pcie_write(pc, BCMA_CORE_PCI_DLLP_PMTHRESHREG, w);
	bcma_pcie_read(pc, BCMA_CORE_PCI_DLLP_PMTHRESHREG);
}