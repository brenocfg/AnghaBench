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
struct al_pcie_regs {TYPE_1__* port_regs; } ;
struct al_pcie_port {int /*<<< orphan*/  port_id; struct al_pcie_regs* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_link_ctrl; int /*<<< orphan*/  pipe_loopback_ctrl; } ;

/* Variables and functions */
 int PCIE_PORT_LINK_CTRL_LB_EN_SHIFT ; 
 int PCIE_PORT_PIPE_LOOPBACK_CTRL_PIPE_LB_EN_SHIFT ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
al_pcie_local_pipe_loopback_exit(struct al_pcie_port *pcie_port)
{
	struct al_pcie_regs *regs = pcie_port->regs;

	al_dbg("PCIe %d: Exit LOCAL PIPE Loopback mode", pcie_port->port_id);

	al_reg_write32_masked(&regs->port_regs->pipe_loopback_ctrl,
			      1 << PCIE_PORT_PIPE_LOOPBACK_CTRL_PIPE_LB_EN_SHIFT,
			      0);

	al_reg_write32_masked(&regs->port_regs->port_link_ctrl,
			      1 << PCIE_PORT_LINK_CTRL_LB_EN_SHIFT,
			      0);
	return 0;
}