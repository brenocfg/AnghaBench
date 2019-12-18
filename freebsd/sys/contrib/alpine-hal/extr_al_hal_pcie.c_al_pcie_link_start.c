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
struct TYPE_3__ {int /*<<< orphan*/  port_init; } ;
struct TYPE_4__ {TYPE_1__ global_ctrl; } ;
struct al_pcie_regs {TYPE_2__ app; } ;
struct al_pcie_port {int /*<<< orphan*/  port_id; scalar_t__ regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCIE_W_GLOBAL_CTRL_PORT_INIT_APP_LTSSM_EN_MASK ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_pcie_port_is_enabled (struct al_pcie_port*) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
al_pcie_link_start(struct al_pcie_port *pcie_port)
{
	struct al_pcie_regs *regs = (struct al_pcie_regs *)pcie_port->regs;

	if (!al_pcie_port_is_enabled(pcie_port)) {
		al_err("PCIe %d: port not enabled, cannot start link\n",
			pcie_port->port_id);
		return -EINVAL;
	}

	al_dbg("PCIe_%d: start port link.\n", pcie_port->port_id);

	al_reg_write32_masked(
			regs->app.global_ctrl.port_init,
			PCIE_W_GLOBAL_CTRL_PORT_INIT_APP_LTSSM_EN_MASK,
			PCIE_W_GLOBAL_CTRL_PORT_INIT_APP_LTSSM_EN_MASK);

	return 0;
}