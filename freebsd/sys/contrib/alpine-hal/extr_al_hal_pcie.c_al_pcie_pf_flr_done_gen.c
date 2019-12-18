#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * events_gen; } ;
struct TYPE_6__ {TYPE_2__ global_ctrl; } ;
struct al_pcie_regs {TYPE_3__ app; } ;
struct al_pcie_pf {unsigned int pf_num; TYPE_1__* pcie_port; } ;
struct TYPE_4__ {struct al_pcie_regs* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_PCIE_FLR_DONE_INTERVAL ; 
 int /*<<< orphan*/  PCIE_W_GLOBAL_CTRL_EVENTS_GEN_FLR_PF_DONE ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_udelay (int /*<<< orphan*/ ) ; 

int al_pcie_pf_flr_done_gen(struct al_pcie_pf		*pcie_pf)
{
	struct al_pcie_regs *regs = pcie_pf->pcie_port->regs;
	unsigned int pf_num = pcie_pf->pf_num;

	al_reg_write32_masked(regs->app.global_ctrl.events_gen[pf_num],
			PCIE_W_GLOBAL_CTRL_EVENTS_GEN_FLR_PF_DONE,
			PCIE_W_GLOBAL_CTRL_EVENTS_GEN_FLR_PF_DONE);
	al_udelay(AL_PCIE_FLR_DONE_INTERVAL);
	al_reg_write32_masked(regs->app.global_ctrl.events_gen[pf_num],
			PCIE_W_GLOBAL_CTRL_EVENTS_GEN_FLR_PF_DONE, 0);
	return 0;
}