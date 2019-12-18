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
typedef  int uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; int /*<<< orphan*/  name; } ;
struct al_eth_eee_params {void* stop_cnt; void* min_interval; void* tx_eee_timer; int /*<<< orphan*/  enable; } ;
struct TYPE_3__ {int /*<<< orphan*/  stop_cnt; int /*<<< orphan*/  post_cnt; int /*<<< orphan*/  pre_cnt; int /*<<< orphan*/  cfg_e; } ;
struct TYPE_4__ {TYPE_1__ eee; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int EC_EEE_CFG_E_ENABLE ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 void* al_reg_read32 (int /*<<< orphan*/ *) ; 

int al_eth_eee_get(struct al_hal_eth_adapter *adapter, struct al_eth_eee_params *params)
{
	uint32_t reg;

	al_dbg("[%s]: getting eee.\n", adapter->name);

	reg = al_reg_read32(&adapter->ec_regs_base->eee.cfg_e);
	params->enable = (reg & EC_EEE_CFG_E_ENABLE) ? AL_TRUE : AL_FALSE;

	params->tx_eee_timer = al_reg_read32(&adapter->ec_regs_base->eee.pre_cnt);
	params->min_interval = al_reg_read32(&adapter->ec_regs_base->eee.post_cnt);
	params->stop_cnt = al_reg_read32(&adapter->ec_regs_base->eee.stop_cnt);

	return 0;
}