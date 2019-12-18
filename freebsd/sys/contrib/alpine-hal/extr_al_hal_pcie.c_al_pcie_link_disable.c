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
typedef  int uint32_t ;
struct al_pcie_regs {TYPE_1__* core_space; } ;
struct al_pcie_port {int /*<<< orphan*/  port_id; struct al_pcie_regs* regs; } ;
typedef  enum al_pcie_operating_mode { ____Placeholder_al_pcie_operating_mode } al_pcie_operating_mode ;
typedef  int al_bool ;
struct TYPE_2__ {scalar_t__ pcie_cap_base; } ;

/* Variables and functions */
 int AL_PCIE_OPERATING_MODE_RC ; 
 int AL_PCI_EXP_LNKCTL ; 
 int AL_PCI_EXP_LNKCTL_LNK_DIS ; 
 int EINVAL ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_pcie_is_link_started (struct al_pcie_port*) ; 
 int al_pcie_operating_mode_get (struct al_pcie_port*) ; 
 int al_reg_read32 (scalar_t__) ; 
 int /*<<< orphan*/  al_reg_write32_masked (scalar_t__,int,int) ; 

int
al_pcie_link_disable(struct al_pcie_port *pcie_port, al_bool disable)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	uint32_t pcie_lnkctl;
	al_bool link_disable_state;
	enum al_pcie_operating_mode op_mode = al_pcie_operating_mode_get(pcie_port);

	if (op_mode != AL_PCIE_OPERATING_MODE_RC) {
		al_err("PCIe %d: hot-reset is applicable only for RC mode\n", pcie_port->port_id);
		return -EINVAL;
	}

	if (!al_pcie_is_link_started(pcie_port)) {
		al_err("PCIe %d: link not started, cannot disable link\n", pcie_port->port_id);
		return -EINVAL;
	}

	pcie_lnkctl = al_reg_read32(regs->core_space[0].pcie_cap_base + (AL_PCI_EXP_LNKCTL >> 1));
	link_disable_state = pcie_lnkctl & AL_PCI_EXP_LNKCTL_LNK_DIS;

	if (disable && link_disable_state) {
		al_err("PCIe %d: link is already in disable state\n", pcie_port->port_id);
		return -EINVAL;
	} else if ((!disable) && (!(link_disable_state))) {
		al_err("PCIe %d: link is already in enable state\n", pcie_port->port_id);
		return -EINVAL;
	}

	al_dbg("PCIe %d: %s port\n", pcie_port->port_id, (disable ? "disabling" : "enabling"));
	al_reg_write32_masked(regs->core_space[0].pcie_cap_base + (AL_PCI_EXP_LNKCTL >> 1),
		AL_PCI_EXP_LNKCTL_LNK_DIS,
		(disable ? AL_PCI_EXP_LNKCTL_LNK_DIS : ~AL_PCI_EXP_LNKCTL_LNK_DIS));
	return 0;
}