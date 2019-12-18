#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct al_pcie_regs {TYPE_1__* core_space; } ;
struct al_pcie_port {int /*<<< orphan*/  port_id; struct al_pcie_regs* regs; } ;
typedef  enum al_pcie_operating_mode { ____Placeholder_al_pcie_operating_mode } al_pcie_operating_mode ;
struct TYPE_2__ {scalar_t__ pcie_cap_base; } ;

/* Variables and functions */
 int AL_PCIE_OPERATING_MODE_RC ; 
 int AL_PCI_EXP_LNKCTL ; 
 int /*<<< orphan*/  AL_PCI_EXP_LNKCTL_LNK_RTRN ; 
 int EINVAL ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_pcie_is_link_started (struct al_pcie_port*) ; 
 int al_pcie_operating_mode_get (struct al_pcie_port*) ; 
 int /*<<< orphan*/  al_reg_write32_masked (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
al_pcie_link_retrain(struct al_pcie_port *pcie_port)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	enum al_pcie_operating_mode op_mode = al_pcie_operating_mode_get(pcie_port);

	if (op_mode != AL_PCIE_OPERATING_MODE_RC) {
		al_err("PCIe %d: link-retrain is applicable only for RC mode\n",
			pcie_port->port_id);
		return -EINVAL;
	}

	if (!al_pcie_is_link_started(pcie_port)) {
		al_err("PCIe %d: link not started, cannot link-retrain\n", pcie_port->port_id);
		return -EINVAL;
	}

	al_reg_write32_masked(regs->core_space[0].pcie_cap_base + (AL_PCI_EXP_LNKCTL >> 1),
	AL_PCI_EXP_LNKCTL_LNK_RTRN, AL_PCI_EXP_LNKCTL_LNK_RTRN);

	return 0;
}