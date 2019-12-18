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
typedef  enum al_pcie_link_speed { ____Placeholder_al_pcie_link_speed } al_pcie_link_speed ;
struct TYPE_2__ {int /*<<< orphan*/  gen2_ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCIE_PORT_GEN2_CTRL_DIRECT_SPEED_CHANGE ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_pcie_is_link_started (struct al_pcie_port*) ; 
 int /*<<< orphan*/  al_pcie_port_link_speed_ctrl_set (struct al_pcie_port*,int) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
al_pcie_link_change_speed(struct al_pcie_port *pcie_port,
			      enum al_pcie_link_speed new_speed)
{
	struct al_pcie_regs *regs = pcie_port->regs;

	if (!al_pcie_is_link_started(pcie_port)) {
		al_err("PCIe %d: link not started, cannot change speed\n", pcie_port->port_id);
		return -EINVAL;
	}

	al_dbg("PCIe %d: changing speed to %d\n", pcie_port->port_id, new_speed);

	al_pcie_port_link_speed_ctrl_set(pcie_port, new_speed);

	al_reg_write32_masked(&regs->port_regs->gen2_ctrl,
		PCIE_PORT_GEN2_CTRL_DIRECT_SPEED_CHANGE,
		PCIE_PORT_GEN2_CTRL_DIRECT_SPEED_CHANGE);

	return 0;
}