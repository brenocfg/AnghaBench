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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; } ;
struct TYPE_4__ {TYPE_1__* rfw_default; } ;
struct TYPE_3__ {int /*<<< orphan*/  opt_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_RFW_DEFAULT_OPT_1_UDMA_MASK ; 
 int EC_RFW_DEFAULT_OPT_1_UDMA_SHIFT ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int al_eth_fwd_default_udma_config(struct al_hal_eth_adapter *adapter, uint32_t idx,
				   uint8_t udma_mask)
{
	al_reg_write32_masked(&adapter->ec_regs_base->rfw_default[idx].opt_1,
			       EC_RFW_DEFAULT_OPT_1_UDMA_MASK,
			       udma_mask << EC_RFW_DEFAULT_OPT_1_UDMA_SHIFT);
	return 0;
}