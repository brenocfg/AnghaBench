#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct al_hal_eth_adapter {scalar_t__ rev_id; TYPE_6__* mac_regs_base; int /*<<< orphan*/  mac_mode; TYPE_2__* ec_regs_base; } ;
struct TYPE_11__ {int /*<<< orphan*/  frm_len; } ;
struct TYPE_10__ {int /*<<< orphan*/  frm_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_afifo_cfg_2; int /*<<< orphan*/  rx_afifo_cfg_1; } ;
struct TYPE_12__ {TYPE_5__ mac_10g; TYPE_4__ mac_1g; TYPE_3__ gen_v3; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_pkt; int /*<<< orphan*/  min_pkt; } ;
struct TYPE_8__ {TYPE_1__ mac; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_IS_10G_MAC (int /*<<< orphan*/ ) ; 
 scalar_t__ AL_ETH_IS_1G_MAC (int /*<<< orphan*/ ) ; 
 scalar_t__ AL_ETH_IS_25G_MAC (int /*<<< orphan*/ ) ; 
 scalar_t__ AL_ETH_MAX_FRAME_LEN ; 
 scalar_t__ AL_ETH_REV_ID_2 ; 
 int /*<<< orphan*/  ETH_MAC_GEN_V3_MAC_40G_FRM_LENGTH_ADDR ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/  al_eth_40g_mac_reg_write (struct al_hal_eth_adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,scalar_t__) ; 

int al_eth_rx_pkt_limit_config(struct al_hal_eth_adapter *adapter, uint32_t min_rx_len, uint32_t max_rx_len)
{
	al_assert(max_rx_len <= AL_ETH_MAX_FRAME_LEN);

	/* EC minimum packet length [bytes] in RX */
	al_reg_write32(&adapter->ec_regs_base->mac.min_pkt, min_rx_len);
	/* EC maximum packet length [bytes] in RX */
	al_reg_write32(&adapter->ec_regs_base->mac.max_pkt, max_rx_len);

	if (adapter->rev_id > AL_ETH_REV_ID_2) {
		al_reg_write32(&adapter->mac_regs_base->gen_v3.rx_afifo_cfg_1, min_rx_len);
		al_reg_write32(&adapter->mac_regs_base->gen_v3.rx_afifo_cfg_2, max_rx_len);
	}

	/* configure the MAC's max rx length, add 16 bytes so the packet get
	 * trimmed by the EC/Async_fifo rather by the MAC
	*/
	if (AL_ETH_IS_1G_MAC(adapter->mac_mode))
		al_reg_write32(&adapter->mac_regs_base->mac_1g.frm_len, max_rx_len + 16);
	else if (AL_ETH_IS_10G_MAC(adapter->mac_mode) || AL_ETH_IS_25G_MAC(adapter->mac_mode))
		/* 10G MAC control register  */
		al_reg_write32(&adapter->mac_regs_base->mac_10g.frm_len, (max_rx_len + 16));
	else
		al_eth_40g_mac_reg_write(adapter, ETH_MAC_GEN_V3_MAC_40G_FRM_LENGTH_ADDR, (max_rx_len + 16));

	return 0;
}