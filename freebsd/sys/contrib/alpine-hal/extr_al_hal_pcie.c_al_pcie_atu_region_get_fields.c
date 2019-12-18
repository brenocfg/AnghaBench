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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct al_pcie_regs {TYPE_2__* port_regs; } ;
struct al_pcie_port {struct al_pcie_regs* regs; } ;
typedef  enum al_pcie_atu_dir { ____Placeholder_al_pcie_atu_dir } al_pcie_atu_dir ;
typedef  int /*<<< orphan*/  al_bool ;
struct TYPE_3__ {int /*<<< orphan*/  cr1; int /*<<< orphan*/  upper_target_addr; int /*<<< orphan*/  lower_target_addr; int /*<<< orphan*/  upper_base_addr; int /*<<< orphan*/  lower_base_addr; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {TYPE_1__ iatu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 scalar_t__ AL_REG_BIT_GET (void*,int) ; 
 int /*<<< orphan*/  AL_REG_BIT_VAL_SET (void*,int,int) ; 
 int /*<<< orphan*/  AL_REG_FIELD_SET (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_TRUE ; 
 void* al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,void*) ; 

void
al_pcie_atu_region_get_fields(
	struct al_pcie_port *pcie_port,
	enum al_pcie_atu_dir direction, uint8_t index,
	al_bool *enable, uint64_t *base_addr, uint64_t *target_addr)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	uint64_t high_addr;
	uint32_t reg = 0;

	AL_REG_FIELD_SET(reg, 0xF, 0, index);
	AL_REG_BIT_VAL_SET(reg, 31, direction);
	al_reg_write32(&regs->port_regs->iatu.index, reg);

	*base_addr = al_reg_read32(&regs->port_regs->iatu.lower_base_addr);
	high_addr = al_reg_read32(&regs->port_regs->iatu.upper_base_addr);
	high_addr <<= 32;
	*base_addr |= high_addr;

	*target_addr = al_reg_read32(&regs->port_regs->iatu.lower_target_addr);
	high_addr = al_reg_read32(&regs->port_regs->iatu.upper_target_addr);
	high_addr <<= 32;
	*target_addr |= high_addr;

	reg = al_reg_read32(&regs->port_regs->iatu.cr1);
	*enable = AL_REG_BIT_GET(reg, 31) ? AL_TRUE : AL_FALSE;
}