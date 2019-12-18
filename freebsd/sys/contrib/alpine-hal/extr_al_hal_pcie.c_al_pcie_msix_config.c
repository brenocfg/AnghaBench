#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct al_pcie_regs {TYPE_1__* core_space; } ;
struct al_pcie_pf {unsigned int pf_num; TYPE_2__* pcie_port; } ;
struct al_pcie_msix_params {int table_size; int table_offset; int table_bar; int pba_offset; int pba_bar; } ;
struct TYPE_4__ {struct al_pcie_regs* regs; } ;
struct TYPE_3__ {scalar_t__ msix_cap_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int AL_PCI_MSIX_MSGCTRL_TBL_SIZE ; 
 int AL_PCI_MSIX_MSGCTRL_TBL_SIZE_SHIFT ; 
 int AL_PCI_MSIX_PBA ; 
 int AL_PCI_MSIX_PBA_BAR ; 
 int AL_PCI_MSIX_PBA_OFFSET ; 
 int AL_PCI_MSIX_TABLE ; 
 int AL_PCI_MSIX_TABLE_BAR ; 
 int AL_PCI_MSIX_TABLE_OFFSET ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  al_pcie_port_wr_to_ro_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int al_reg_read32 (scalar_t__) ; 
 int /*<<< orphan*/  al_reg_write32 (scalar_t__,int) ; 

int
al_pcie_msix_config(
	struct al_pcie_pf *pcie_pf,
	struct al_pcie_msix_params *msix_params)
{
	struct al_pcie_regs *regs = pcie_pf->pcie_port->regs;
	unsigned int pf_num = pcie_pf->pf_num;
	uint32_t msix_reg0;

	al_pcie_port_wr_to_ro_set(pcie_pf->pcie_port, AL_TRUE);

	msix_reg0 = al_reg_read32(regs->core_space[pf_num].msix_cap_base);

	msix_reg0 &= ~(AL_PCI_MSIX_MSGCTRL_TBL_SIZE << AL_PCI_MSIX_MSGCTRL_TBL_SIZE_SHIFT);
	msix_reg0 |= ((msix_params->table_size - 1) & AL_PCI_MSIX_MSGCTRL_TBL_SIZE) <<
			AL_PCI_MSIX_MSGCTRL_TBL_SIZE_SHIFT;
	al_reg_write32(regs->core_space[pf_num].msix_cap_base, msix_reg0);

	/* Table offset & BAR */
	al_reg_write32(regs->core_space[pf_num].msix_cap_base + (AL_PCI_MSIX_TABLE >> 2),
		       (msix_params->table_offset & AL_PCI_MSIX_TABLE_OFFSET) |
			       (msix_params->table_bar & AL_PCI_MSIX_TABLE_BAR));
	/* PBA offset & BAR */
	al_reg_write32(regs->core_space[pf_num].msix_cap_base + (AL_PCI_MSIX_PBA >> 2),
		       (msix_params->pba_offset & AL_PCI_MSIX_PBA_OFFSET) |
			       (msix_params->pba_bar & AL_PCI_MSIX_PBA_BAR));

	al_pcie_port_wr_to_ro_set(pcie_pf->pcie_port, AL_FALSE);

	return 0;
}