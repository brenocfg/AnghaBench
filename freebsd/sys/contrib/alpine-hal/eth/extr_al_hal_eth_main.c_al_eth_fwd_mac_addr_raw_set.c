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
typedef  size_t uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; } ;
struct TYPE_4__ {TYPE_1__* fwd_mac; } ;
struct TYPE_3__ {int /*<<< orphan*/  mask_h; int /*<<< orphan*/  mask_l; int /*<<< orphan*/  data_h; int /*<<< orphan*/  data_l; } ;

/* Variables and functions */
 size_t AL_ETH_FWD_MAC_NUM ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,size_t) ; 

int al_eth_fwd_mac_addr_raw_set(struct al_hal_eth_adapter *adapter, uint32_t idx, uint32_t addr_lo, uint32_t addr_hi, uint32_t mask_lo, uint32_t mask_hi)
{
	al_assert(idx < AL_ETH_FWD_MAC_NUM); /*valid FWD MAC index */

	al_reg_write32(&adapter->ec_regs_base->fwd_mac[idx].data_l, addr_lo);
	al_reg_write32(&adapter->ec_regs_base->fwd_mac[idx].data_h, addr_hi);
	al_reg_write32(&adapter->ec_regs_base->fwd_mac[idx].mask_l, mask_lo);
	al_reg_write32(&adapter->ec_regs_base->fwd_mac[idx].mask_h, mask_hi);

	return 0;
}