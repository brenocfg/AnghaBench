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
struct tgec_cfg {int /*<<< orphan*/  skip_fman11_workaround; int /*<<< orphan*/  pause_quant; int /*<<< orphan*/  max_frame_length; int /*<<< orphan*/  tx_ipg_length; int /*<<< orphan*/  time_stamp_enable; int /*<<< orphan*/  lgth_check_nostdr; int /*<<< orphan*/  no_length_check_enable; int /*<<< orphan*/  send_idle_enable; int /*<<< orphan*/  rx_error_discard; int /*<<< orphan*/  cmd_frame_enable; int /*<<< orphan*/  loopback_enable; int /*<<< orphan*/  tx_addr_ins_enable; int /*<<< orphan*/  pause_ignore; int /*<<< orphan*/  pause_forward_enable; int /*<<< orphan*/  promiscuous_mode_enable; int /*<<< orphan*/  wan_mode_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CMD_FRAME_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_LGTH_CHECK_NOSTDR ; 
 int /*<<< orphan*/  DEFAULT_LOOPBACK_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_MAX_FRAME_LENGTH ; 
 int /*<<< orphan*/  DEFAULT_NO_LENGTH_CHECK_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_PAUSE_FORWARD_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_PAUSE_IGNORE ; 
 int /*<<< orphan*/  DEFAULT_PAUSE_QUANT ; 
 int /*<<< orphan*/  DEFAULT_PROMISCUOUS_MODE_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_RX_ERROR_DISCARD ; 
 int /*<<< orphan*/  DEFAULT_SEND_IDLE_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_TIME_STAMP_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_TX_ADDR_INS_ENABLE ; 
 int /*<<< orphan*/  DEFAULT_TX_IPG_LENGTH ; 
 int /*<<< orphan*/  DEFAULT_WAN_MODE_ENABLE ; 
 int /*<<< orphan*/  FALSE ; 

void fman_tgec_defconfig(struct tgec_cfg *cfg)
{
	cfg->wan_mode_enable = DEFAULT_WAN_MODE_ENABLE;
	cfg->promiscuous_mode_enable = DEFAULT_PROMISCUOUS_MODE_ENABLE;
	cfg->pause_forward_enable = DEFAULT_PAUSE_FORWARD_ENABLE;
	cfg->pause_ignore = DEFAULT_PAUSE_IGNORE;
	cfg->tx_addr_ins_enable = DEFAULT_TX_ADDR_INS_ENABLE;
	cfg->loopback_enable = DEFAULT_LOOPBACK_ENABLE;
	cfg->cmd_frame_enable = DEFAULT_CMD_FRAME_ENABLE;
	cfg->rx_error_discard = DEFAULT_RX_ERROR_DISCARD;
	cfg->send_idle_enable = DEFAULT_SEND_IDLE_ENABLE;
	cfg->no_length_check_enable = DEFAULT_NO_LENGTH_CHECK_ENABLE;
	cfg->lgth_check_nostdr = DEFAULT_LGTH_CHECK_NOSTDR;
	cfg->time_stamp_enable = DEFAULT_TIME_STAMP_ENABLE;
	cfg->tx_ipg_length = DEFAULT_TX_IPG_LENGTH;
	cfg->max_frame_length = DEFAULT_MAX_FRAME_LENGTH;
	cfg->pause_quant = DEFAULT_PAUSE_QUANT;
#ifdef FM_TX_ECC_FRMS_ERRATA_10GMAC_A004
	cfg->skip_fman11_workaround = FALSE;
#endif /* FM_TX_ECC_FRMS_ERRATA_10GMAC_A004 */
}