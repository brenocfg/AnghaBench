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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * events_gen; } ;
struct TYPE_5__ {TYPE_1__ global_ctrl; } ;
struct al_pcie_regs {TYPE_2__ app; } ;
struct al_pcie_pf {unsigned int pf_num; TYPE_3__* pcie_port; } ;
struct TYPE_6__ {struct al_pcie_regs* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_REG_BIT_CLEAR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AL_REG_BIT_SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AL_REG_FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_W_GLOBAL_CTRL_EVENTS_GEN_MSI_VECTOR_MASK ; 
 int /*<<< orphan*/  PCIE_W_GLOBAL_CTRL_EVENTS_GEN_MSI_VECTOR_SHIFT ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
al_pcie_msi_int_gen(struct al_pcie_pf *pcie_pf, uint8_t vector)
{
	struct al_pcie_regs *regs = pcie_pf->pcie_port->regs;
	unsigned int pf_num = pcie_pf->pf_num;
	uint32_t reg;

	/* set msi vector and clear MSI request */
	reg = al_reg_read32(regs->app.global_ctrl.events_gen[pf_num]);
	AL_REG_BIT_CLEAR(reg, 4);
	AL_REG_FIELD_SET(reg,
			PCIE_W_GLOBAL_CTRL_EVENTS_GEN_MSI_VECTOR_MASK,
			PCIE_W_GLOBAL_CTRL_EVENTS_GEN_MSI_VECTOR_SHIFT,
			vector);
	al_reg_write32(regs->app.global_ctrl.events_gen[pf_num], reg);
	/* set MSI request */
	AL_REG_BIT_SET(reg, 4);
	al_reg_write32(regs->app.global_ctrl.events_gen[pf_num], reg);

	return 0;
}