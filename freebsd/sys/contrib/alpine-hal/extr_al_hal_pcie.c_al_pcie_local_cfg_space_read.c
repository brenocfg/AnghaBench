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
struct al_pcie_regs {TYPE_2__* core_space; } ;
struct al_pcie_pf {size_t pf_num; TYPE_1__* pcie_port; } ;
struct TYPE_4__ {int /*<<< orphan*/ * config_header; } ;
struct TYPE_3__ {struct al_pcie_regs* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 

uint32_t
al_pcie_local_cfg_space_read(
	struct al_pcie_pf	*pcie_pf,
	unsigned int		reg_offset)
{
	struct al_pcie_regs *regs = pcie_pf->pcie_port->regs;
	uint32_t data;

	data = al_reg_read32(&regs->core_space[pcie_pf->pf_num].config_header[reg_offset]);

	return data;
}