#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dtsec_cfg {int /*<<< orphan*/  wake_on_lan; int /*<<< orphan*/  tbi_phy_addr; int /*<<< orphan*/  maximum_frame; int /*<<< orphan*/  back_to_back_ipg; int /*<<< orphan*/  min_ifg_enforcement; int /*<<< orphan*/  non_back_to_back_ipg2; int /*<<< orphan*/  non_back_to_back_ipg1; int /*<<< orphan*/  rx_promisc; int /*<<< orphan*/  tx_pause_time_extd; int /*<<< orphan*/  rx_group_hash_exd; int /*<<< orphan*/  tx_flow; int /*<<< orphan*/  rx_flow; int /*<<< orphan*/  tx_time_stamp_en; int /*<<< orphan*/  rx_time_stamp_en; int /*<<< orphan*/  loopback; int /*<<< orphan*/  tx_preamble; int /*<<< orphan*/  rx_preamble; int /*<<< orphan*/  preamble_len; int /*<<< orphan*/  ptp_exception_en; int /*<<< orphan*/  ptp_tsu_en; int /*<<< orphan*/  rx_prepend; int /*<<< orphan*/  tbipa; int /*<<< orphan*/  tx_pause_time; int /*<<< orphan*/  rx_ctrl_acc; int /*<<< orphan*/  tx_crc; int /*<<< orphan*/  tx_pad_crc; int /*<<< orphan*/  rx_len_check; int /*<<< orphan*/  rx_short_frm; int /*<<< orphan*/  rx_drop_bcast; int /*<<< orphan*/  halfdup_alt_backoff_en; int /*<<< orphan*/  halfdup_alt_backoff_val; int /*<<< orphan*/  halfdup_bp_no_backoff; int /*<<< orphan*/  halfdup_no_backoff; int /*<<< orphan*/  halfdup_excess_defer; int /*<<< orphan*/  halfdup_coll_window; int /*<<< orphan*/  halfdup_retransmit; int /*<<< orphan*/  halfdup_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BACK_TO_BACK_IPG ; 
 int /*<<< orphan*/  DEFAULT_HALFDUP_ALT_BACKOFF_EN ; 
 int /*<<< orphan*/  DEFAULT_HALFDUP_ALT_BACKOFF_VAL ; 
 int /*<<< orphan*/  DEFAULT_HALFDUP_BP_NO_BACKOFF ; 
 int /*<<< orphan*/  DEFAULT_HALFDUP_COLL_WINDOW ; 
 int /*<<< orphan*/  DEFAULT_HALFDUP_EXCESS_DEFER ; 
 int /*<<< orphan*/  DEFAULT_HALFDUP_NO_BACKOFF ; 
 int /*<<< orphan*/  DEFAULT_HALFDUP_ON ; 
 int /*<<< orphan*/  DEFAULT_HALFDUP_RETRANSMIT ; 
 int /*<<< orphan*/  DEFAULT_LOOPBACK ; 
 int /*<<< orphan*/  DEFAULT_MAXIMUM_FRAME ; 
 int /*<<< orphan*/  DEFAULT_MIN_IFG_ENFORCEMENT ; 
 int /*<<< orphan*/  DEFAULT_NON_BACK_TO_BACK_IPG1 ; 
 int /*<<< orphan*/  DEFAULT_NON_BACK_TO_BACK_IPG2 ; 
 int /*<<< orphan*/  DEFAULT_PREAMBLE_LEN ; 
 int /*<<< orphan*/  DEFAULT_PTP_EXCEPTION_EN ; 
 int /*<<< orphan*/  DEFAULT_PTP_TSU_EN ; 
 int /*<<< orphan*/  DEFAULT_RX_CTRL_ACC ; 
 int /*<<< orphan*/  DEFAULT_RX_DROP_BCAST ; 
 int /*<<< orphan*/  DEFAULT_RX_FLOW ; 
 int /*<<< orphan*/  DEFAULT_RX_GROUP_HASH_EXD ; 
 int /*<<< orphan*/  DEFAULT_RX_LEN_CHECK ; 
 int /*<<< orphan*/  DEFAULT_RX_PREAMBLE ; 
 int /*<<< orphan*/  DEFAULT_RX_PREPEND ; 
 int /*<<< orphan*/  DEFAULT_RX_PROMISC ; 
 int /*<<< orphan*/  DEFAULT_RX_SHORT_FRM ; 
 int /*<<< orphan*/  DEFAULT_RX_TIME_STAMP_EN ; 
 int /*<<< orphan*/  DEFAULT_TBIPA ; 
 int /*<<< orphan*/  DEFAULT_TBI_PHY_ADDR ; 
 int /*<<< orphan*/  DEFAULT_TX_CRC ; 
 int /*<<< orphan*/  DEFAULT_TX_FLOW ; 
 int /*<<< orphan*/  DEFAULT_TX_PAD_CRC ; 
 int /*<<< orphan*/  DEFAULT_TX_PAUSE_TIME ; 
 int /*<<< orphan*/  DEFAULT_TX_PAUSE_TIME_EXTD ; 
 int /*<<< orphan*/  DEFAULT_TX_PREAMBLE ; 
 int /*<<< orphan*/  DEFAULT_TX_TIME_STAMP_EN ; 
 int /*<<< orphan*/  DEFAULT_WAKE_ON_LAN ; 

void fman_dtsec_defconfig(struct dtsec_cfg *cfg)
{
	cfg->halfdup_on = DEFAULT_HALFDUP_ON;
	cfg->halfdup_retransmit = DEFAULT_HALFDUP_RETRANSMIT;
	cfg->halfdup_coll_window = DEFAULT_HALFDUP_COLL_WINDOW;
	cfg->halfdup_excess_defer = DEFAULT_HALFDUP_EXCESS_DEFER;
	cfg->halfdup_no_backoff = DEFAULT_HALFDUP_NO_BACKOFF;
	cfg->halfdup_bp_no_backoff = DEFAULT_HALFDUP_BP_NO_BACKOFF;
	cfg->halfdup_alt_backoff_val = DEFAULT_HALFDUP_ALT_BACKOFF_VAL;
	cfg->halfdup_alt_backoff_en = DEFAULT_HALFDUP_ALT_BACKOFF_EN;
	cfg->rx_drop_bcast = DEFAULT_RX_DROP_BCAST;
	cfg->rx_short_frm = DEFAULT_RX_SHORT_FRM;
	cfg->rx_len_check = DEFAULT_RX_LEN_CHECK;
	cfg->tx_pad_crc = DEFAULT_TX_PAD_CRC;
	cfg->tx_crc = DEFAULT_TX_CRC;
	cfg->rx_ctrl_acc = DEFAULT_RX_CTRL_ACC;
	cfg->tx_pause_time = DEFAULT_TX_PAUSE_TIME;
	cfg->tbipa = DEFAULT_TBIPA; /* PHY address 0 is reserved (DPAA RM)*/
	cfg->rx_prepend = DEFAULT_RX_PREPEND;
	cfg->ptp_tsu_en = DEFAULT_PTP_TSU_EN;
	cfg->ptp_exception_en = DEFAULT_PTP_EXCEPTION_EN;
	cfg->preamble_len = DEFAULT_PREAMBLE_LEN;
	cfg->rx_preamble = DEFAULT_RX_PREAMBLE;
	cfg->tx_preamble = DEFAULT_TX_PREAMBLE;
	cfg->loopback = DEFAULT_LOOPBACK;
	cfg->rx_time_stamp_en = DEFAULT_RX_TIME_STAMP_EN;
	cfg->tx_time_stamp_en = DEFAULT_TX_TIME_STAMP_EN;
	cfg->rx_flow = DEFAULT_RX_FLOW;
	cfg->tx_flow = DEFAULT_TX_FLOW;
	cfg->rx_group_hash_exd = DEFAULT_RX_GROUP_HASH_EXD;
	cfg->tx_pause_time_extd = DEFAULT_TX_PAUSE_TIME_EXTD;
	cfg->rx_promisc = DEFAULT_RX_PROMISC;
	cfg->non_back_to_back_ipg1 = DEFAULT_NON_BACK_TO_BACK_IPG1;
	cfg->non_back_to_back_ipg2 = DEFAULT_NON_BACK_TO_BACK_IPG2;
	cfg->min_ifg_enforcement = DEFAULT_MIN_IFG_ENFORCEMENT;
	cfg->back_to_back_ipg = DEFAULT_BACK_TO_BACK_IPG;
	cfg->maximum_frame = DEFAULT_MAXIMUM_FRAME;
	cfg->tbi_phy_addr = DEFAULT_TBI_PHY_ADDR;
	cfg->wake_on_lan = DEFAULT_WAKE_ON_LAN;
}