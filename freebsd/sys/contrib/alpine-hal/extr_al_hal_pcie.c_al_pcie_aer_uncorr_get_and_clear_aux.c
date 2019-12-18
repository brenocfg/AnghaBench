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
typedef  unsigned int uint32_t ;
struct al_pcie_regs {TYPE_1__* core_space; } ;
struct al_pcie_port {struct al_pcie_regs* regs; } ;
struct al_pcie_core_aer_regs {int /*<<< orphan*/  uncorr_err_stat; } ;
struct TYPE_2__ {struct al_pcie_core_aer_regs* aer; } ;

/* Variables and functions */
 unsigned int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static unsigned int 
al_pcie_aer_uncorr_get_and_clear_aux(
		struct al_pcie_port		*pcie_port,
		unsigned int	pf_num)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	struct al_pcie_core_aer_regs *aer_regs = regs->core_space[pf_num].aer;
	uint32_t reg_val;

	reg_val = al_reg_read32(&aer_regs->uncorr_err_stat);
	al_reg_write32(&aer_regs->uncorr_err_stat, reg_val);

	return reg_val;
}