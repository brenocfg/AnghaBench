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

/* Variables and functions */
 int PIC_PCIE_LINK0_IRQ ; 
 int PIC_PCIE_LINK1_IRQ ; 
 int PIC_PCIE_LINK2_IRQ ; 
 int PIC_PCIE_LINK3_IRQ ; 
 int PIC_PCIE_XLSB0_LINK2_IRQ ; 
 int PIC_PCIE_XLSB0_LINK3_IRQ ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  nlm_chip_is_xls_b () ; 

__attribute__((used)) static int nlm_pci_link_to_irq(int link)
{
	switch	(link) {
	case 0:
		return PIC_PCIE_LINK0_IRQ;
	case 1:
		return PIC_PCIE_LINK1_IRQ;
	case 2:
		if (nlm_chip_is_xls_b())
			return PIC_PCIE_XLSB0_LINK2_IRQ;
		else
			return PIC_PCIE_LINK2_IRQ;
	case 3:
		if (nlm_chip_is_xls_b())
			return PIC_PCIE_XLSB0_LINK3_IRQ;
		else
			return PIC_PCIE_LINK3_IRQ;
	}
	WARN(1, "Unexpected link %d\n", link);
	return 0;
}