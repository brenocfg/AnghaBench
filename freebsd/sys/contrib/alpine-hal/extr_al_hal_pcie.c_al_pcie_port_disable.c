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
struct al_pcie_port {unsigned int port_id; scalar_t__ pbs_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcie_conf_1; } ;
struct al_pbs_regs {TYPE_1__ unit; } ;

/* Variables and functions */
 unsigned int PBS_UNIT_PCIE_CONF_1_PCIE_EXIST_SHIFT ; 
 int /*<<< orphan*/  al_pcie_port_is_enabled (struct al_pcie_port*) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_warn (char*,unsigned int) ; 

void
al_pcie_port_disable(struct al_pcie_port *pcie_port)
{
	struct al_pbs_regs *pbs_reg_base =
				(struct al_pbs_regs *)pcie_port->pbs_regs;
	unsigned int port_id = pcie_port->port_id;

	if (!al_pcie_port_is_enabled(pcie_port)) {
		al_warn("PCIe %d: trying to disable a non-enabled port\n",
			pcie_port->port_id);
	}

	/* Assert core reset */
	al_reg_write32_masked(
		&pbs_reg_base->unit.pcie_conf_1,
		1 << (port_id + PBS_UNIT_PCIE_CONF_1_PCIE_EXIST_SHIFT),
		0);
}