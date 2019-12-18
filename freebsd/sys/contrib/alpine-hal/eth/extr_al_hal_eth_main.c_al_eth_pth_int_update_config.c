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
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; } ;
struct al_eth_pth_int_update_params {scalar_t__ enable; scalar_t__ trigger; int /*<<< orphan*/  method; } ;
struct TYPE_3__ {int /*<<< orphan*/  int_update_ctrl; } ;
struct TYPE_4__ {TYPE_1__ pth; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_PTH_INT_TRIG_REG_WRITE ; 
 scalar_t__ AL_FALSE ; 
 int /*<<< orphan*/  AL_REG_FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_PTH_INT_UPDATE_CTRL_INT_TRIG_EN ; 
 int /*<<< orphan*/  EC_PTH_INT_UPDATE_CTRL_UPDATE_METHOD_MASK ; 
 int /*<<< orphan*/  EC_PTH_INT_UPDATE_CTRL_UPDATE_METHOD_SHIFT ; 
 int /*<<< orphan*/  EC_PTH_INT_UPDATE_CTRL_UPDATE_TRIG ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int al_eth_pth_int_update_config(struct al_hal_eth_adapter *adapter,
				 struct al_eth_pth_int_update_params *params)
{
	uint32_t reg;

	reg = al_reg_read32(&adapter->ec_regs_base->pth.int_update_ctrl);
	if (params->enable == AL_FALSE) {
		reg &= ~EC_PTH_INT_UPDATE_CTRL_INT_TRIG_EN;
	} else {
		reg |= EC_PTH_INT_UPDATE_CTRL_INT_TRIG_EN;
		AL_REG_FIELD_SET(reg, EC_PTH_INT_UPDATE_CTRL_UPDATE_METHOD_MASK,
				 EC_PTH_INT_UPDATE_CTRL_UPDATE_METHOD_SHIFT,
				 params->method);
		if (params->trigger == AL_ETH_PTH_INT_TRIG_REG_WRITE)
			reg |= EC_PTH_INT_UPDATE_CTRL_UPDATE_TRIG;
		else
			reg &= ~EC_PTH_INT_UPDATE_CTRL_UPDATE_TRIG;
	}
	al_reg_write32(&adapter->ec_regs_base->pth.int_update_ctrl, reg);
	return 0;
}