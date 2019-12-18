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
struct al_pcie_regs {TYPE_2__* core_space; } ;
struct al_pcie_pf {size_t pf_num; TYPE_1__* pcie_port; } ;
typedef  int /*<<< orphan*/  al_bool ;
struct TYPE_4__ {int /*<<< orphan*/  msix_cap_base; } ;
struct TYPE_3__ {struct al_pcie_regs* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int AL_PCI_MSIX_MSGCTRL_MASK ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int al_reg_read32 (int /*<<< orphan*/ ) ; 

al_bool
al_pcie_msix_masked(struct al_pcie_pf *pcie_pf)
{
	struct al_pcie_regs *regs = pcie_pf->pcie_port->regs;
	uint32_t msix_reg0 = al_reg_read32(regs->core_space[pcie_pf->pf_num].msix_cap_base);

	if (msix_reg0 & AL_PCI_MSIX_MSGCTRL_MASK)
		return AL_TRUE;
	return AL_FALSE;
}