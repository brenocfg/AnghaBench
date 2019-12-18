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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  conf; } ;
struct TYPE_4__ {TYPE_1__ pcie_global; } ;
struct al_pcie_regs {TYPE_2__ axi; } ;
struct al_pcie_port {scalar_t__ rev_id; int /*<<< orphan*/  port_id; struct al_pcie_regs* regs; } ;
typedef  scalar_t__ al_bool ;

/* Variables and functions */
 scalar_t__ AL_PCIE_REV_ID_3 ; 
 scalar_t__ AL_TRUE ; 
 int EINVAL ; 
 int /*<<< orphan*/  PCIE_REV1_2_AXI_MISC_PCIE_GLOBAL_CONF_MEM_SHUTDOWN ; 
 int /*<<< orphan*/  PCIE_REV3_AXI_MISC_PCIE_GLOBAL_CONF_MEM_SHUTDOWN ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_pcie_port_is_enabled (struct al_pcie_port*) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
al_pcie_port_memory_shutdown_set(
	struct al_pcie_port	*pcie_port,
	al_bool			enable)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	uint32_t mask = (pcie_port->rev_id == AL_PCIE_REV_ID_3) ?
		PCIE_REV3_AXI_MISC_PCIE_GLOBAL_CONF_MEM_SHUTDOWN :
		PCIE_REV1_2_AXI_MISC_PCIE_GLOBAL_CONF_MEM_SHUTDOWN;

	if (!al_pcie_port_is_enabled(pcie_port)) {
		al_err("PCIe %d: not enabled, cannot shutdown memory\n",
			pcie_port->port_id);
		return -EINVAL;
	}

	al_reg_write32_masked(regs->axi.pcie_global.conf,
		mask, enable == AL_TRUE ? mask : 0);

	return 0;
}