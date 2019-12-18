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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_hal_eth_adapter {TYPE_3__* ec_regs_base; int /*<<< orphan*/  rev_id; int /*<<< orphan*/  name; } ;
struct al_eth_filter_params {int filters; scalar_t__ enable; scalar_t__* filter_proto; } ;
struct TYPE_4__ {int /*<<< orphan*/  filter; int /*<<< orphan*/  out_cfg; } ;
struct TYPE_6__ {TYPE_2__* epe_a; TYPE_1__ rfw; } ;
struct TYPE_5__ {int /*<<< orphan*/  prot_act; } ;

/* Variables and functions */
 int AL_ETH_PROTOCOLS_NUM ; 
 int AL_ETH_RFW_FILTER_PROT_INDEX ; 
 int AL_ETH_RFW_FILTER_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_REG_MASK_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_REG_MASK_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AL_TRUE ; 
 int /*<<< orphan*/  EC_EPE_A_PROT_ACT_DROP ; 
 int /*<<< orphan*/  EC_RFW_OUT_CFG_DROP_EN ; 
 int EINVAL ; 
 int /*<<< orphan*/  al_assert (struct al_eth_filter_params*) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int,int) ; 

int al_eth_filter_config(struct al_hal_eth_adapter *adapter, struct al_eth_filter_params *params)
{
	uint32_t reg;

	al_assert(params); /* valid params pointer */

	if (params->filters & ~(AL_ETH_RFW_FILTER_SUPPORTED(adapter->rev_id))) {
		al_err("[%s]: unsupported filter options (0x%08x)\n", adapter->name, params->filters);
		return -EINVAL;
	}

	reg = al_reg_read32(&adapter->ec_regs_base->rfw.out_cfg);
	if (params->enable == AL_TRUE)
		AL_REG_MASK_SET(reg, EC_RFW_OUT_CFG_DROP_EN);
	else
		AL_REG_MASK_CLEAR(reg, EC_RFW_OUT_CFG_DROP_EN);
	al_reg_write32(&adapter->ec_regs_base->rfw.out_cfg, reg);

	al_reg_write32_masked(
		&adapter->ec_regs_base->rfw.filter,
		AL_ETH_RFW_FILTER_SUPPORTED(adapter->rev_id),
		params->filters);
	if (params->filters & AL_ETH_RFW_FILTER_PROT_INDEX) {
		int i;
		for (i = 0; i < AL_ETH_PROTOCOLS_NUM; i++) {
			reg = al_reg_read32(&adapter->ec_regs_base->epe_a[i].prot_act);
			if (params->filter_proto[i] == AL_TRUE)
				AL_REG_MASK_SET(reg, EC_EPE_A_PROT_ACT_DROP);
			else
				AL_REG_MASK_CLEAR(reg, EC_EPE_A_PROT_ACT_DROP);
			al_reg_write32(&adapter->ec_regs_base->epe_a[i].prot_act, reg);
		}
	}
	return 0;
}