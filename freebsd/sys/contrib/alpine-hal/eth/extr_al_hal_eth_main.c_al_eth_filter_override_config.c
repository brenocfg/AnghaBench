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
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; int /*<<< orphan*/  rev_id; int /*<<< orphan*/  name; } ;
struct al_eth_filter_override_params {int filters; int /*<<< orphan*/  qid; int /*<<< orphan*/  udma; } ;
struct TYPE_3__ {int /*<<< orphan*/  default_or; int /*<<< orphan*/  filter; } ;
struct TYPE_4__ {TYPE_1__ rfw; } ;

/* Variables and functions */
 int AL_ETH_RFW_FILTER_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_REG_FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_RFW_DEFAULT_OR_QUEUE_MASK ; 
 int /*<<< orphan*/  EC_RFW_DEFAULT_OR_QUEUE_SHIFT ; 
 int /*<<< orphan*/  EC_RFW_DEFAULT_OR_UDMA_MASK ; 
 int /*<<< orphan*/  EC_RFW_DEFAULT_OR_UDMA_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  al_assert (struct al_eth_filter_override_params*) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int,int) ; 

int al_eth_filter_override_config(struct al_hal_eth_adapter *adapter,
				  struct al_eth_filter_override_params *params)
{
	uint32_t reg;

	al_assert(params); /* valid params pointer */

	if (params->filters & ~(AL_ETH_RFW_FILTER_SUPPORTED(adapter->rev_id))) {
		al_err("[%s]: unsupported override filter options (0x%08x)\n", adapter->name, params->filters);
		return -EINVAL;
	}

	al_reg_write32_masked(
		&adapter->ec_regs_base->rfw.filter,
		AL_ETH_RFW_FILTER_SUPPORTED(adapter->rev_id) << 16,
		params->filters << 16);

	reg = al_reg_read32(&adapter->ec_regs_base->rfw.default_or);
	AL_REG_FIELD_SET(reg, EC_RFW_DEFAULT_OR_UDMA_MASK, EC_RFW_DEFAULT_OR_UDMA_SHIFT, params->udma);
	AL_REG_FIELD_SET(reg, EC_RFW_DEFAULT_OR_QUEUE_MASK, EC_RFW_DEFAULT_OR_QUEUE_SHIFT, params->qid);
	al_reg_write32(&adapter->ec_regs_base->rfw.default_or, reg);
	return 0;
}