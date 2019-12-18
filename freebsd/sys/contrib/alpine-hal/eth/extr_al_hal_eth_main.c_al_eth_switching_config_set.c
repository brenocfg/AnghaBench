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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct al_hal_eth_adapter {TYPE_3__* ec_regs_base; } ;
typedef  enum al_eth_tx_switch_vid_sel_type { ____Placeholder_al_eth_tx_switch_vid_sel_type } al_eth_tx_switch_vid_sel_type ;
typedef  enum al_eth_tx_switch_dec_type { ____Placeholder_al_eth_tx_switch_dec_type } al_eth_tx_switch_dec_type ;
struct TYPE_4__ {int /*<<< orphan*/  tx_gen; } ;
struct TYPE_6__ {TYPE_2__* tfw_udma; TYPE_1__ tfw; } ;
struct TYPE_5__ {int /*<<< orphan*/  fwd_dec; } ;

/* Variables and functions */
 int EC_TFW_TX_GEN_FWD_ALL_TO_MAC ; 
 int al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_eth_switching_config_set(struct al_hal_eth_adapter *adapter, uint8_t udma_id, uint8_t forward_all_to_mac, uint8_t enable_int_switching,
					enum al_eth_tx_switch_vid_sel_type vid_sel_type,
					enum al_eth_tx_switch_dec_type uc_dec,
					enum al_eth_tx_switch_dec_type mc_dec,
					enum al_eth_tx_switch_dec_type bc_dec)
{
	uint32_t reg;

	if (udma_id == 0) {
		reg = al_reg_read32(&adapter->ec_regs_base->tfw.tx_gen);
		if (forward_all_to_mac)
			reg |= EC_TFW_TX_GEN_FWD_ALL_TO_MAC;
		else
			reg &= ~EC_TFW_TX_GEN_FWD_ALL_TO_MAC;
		al_reg_write32(&adapter->ec_regs_base->tfw.tx_gen, reg);
	}

	reg = enable_int_switching;
	reg |= (vid_sel_type & 7) << 1;
	reg |= (bc_dec & 3) << 4;
	reg |= (mc_dec & 3) << 6;
	reg |= (uc_dec & 3) << 8;
	al_reg_write32(&adapter->ec_regs_base->tfw_udma[udma_id].fwd_dec, reg);

	return 0;
}