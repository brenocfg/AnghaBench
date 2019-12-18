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
typedef  int u8 ;
typedef  int u32 ;
struct bcma_drv_pci {int dummy; } ;

/* Variables and functions */
 int BCMA_CORE_PCI_PLP_POLARITYINV_STAT ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_PLP_STATUSREG ; 
 int BCMA_CORE_PCI_SERDES_RX_CTRL_FORCE ; 
 int BCMA_CORE_PCI_SERDES_RX_CTRL_POLARITY ; 
 int bcma_pcie_read (struct bcma_drv_pci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 bcma_pcicore_polarity_workaround(struct bcma_drv_pci *pc)
{
	u32 tmp;

	tmp = bcma_pcie_read(pc, BCMA_CORE_PCI_PLP_STATUSREG);
	if (tmp & BCMA_CORE_PCI_PLP_POLARITYINV_STAT)
		return BCMA_CORE_PCI_SERDES_RX_CTRL_FORCE |
		       BCMA_CORE_PCI_SERDES_RX_CTRL_POLARITY;
	else
		return BCMA_CORE_PCI_SERDES_RX_CTRL_FORCE;
}