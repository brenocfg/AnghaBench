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
struct memac_cfg {void* wake_on_lan; void* debug_mode; void* tx_pbl_fwd; void* rx_pbl_fwd; void* rx_sfd_any; void* phy_tx_ena_on; void* pad_enable; int /*<<< orphan*/  pause_quanta; int /*<<< orphan*/  max_frame_length; int /*<<< orphan*/  tx_ipg_length; void* time_stamp_enable; void* lgth_check_nostdr; void* no_length_check_enable; void* send_idle_enable; void* rx_error_discard; void* cmd_frame_enable; void* loopback_enable; void* tx_addr_ins_enable; void* pause_ignore; void* pause_forward_enable; void* promiscuous_mode_enable; void* wan_mode_enable; void* reset_on_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FRAME_LENGTH ; 
 int /*<<< orphan*/  DEFAULT_PAUSE_QUANTA ; 
 int /*<<< orphan*/  DEFAULT_TX_IPG_LENGTH ; 
 void* FALSE ; 
 void* TRUE ; 

void fman_memac_defconfig(struct memac_cfg *cfg)
{
    cfg->reset_on_init		= FALSE;
    cfg->wan_mode_enable		= FALSE;
    cfg->promiscuous_mode_enable	= FALSE;
    cfg->pause_forward_enable	= FALSE;
    cfg->pause_ignore		= FALSE;
    cfg->tx_addr_ins_enable		= FALSE;
    cfg->loopback_enable		= FALSE;
    cfg->cmd_frame_enable		= FALSE;
    cfg->rx_error_discard		= FALSE;
    cfg->send_idle_enable		= FALSE;
    cfg->no_length_check_enable	= TRUE;
    cfg->lgth_check_nostdr		= FALSE;
    cfg->time_stamp_enable		= FALSE;
    cfg->tx_ipg_length		= DEFAULT_TX_IPG_LENGTH;
    cfg->max_frame_length		= DEFAULT_FRAME_LENGTH;
    cfg->pause_quanta		= DEFAULT_PAUSE_QUANTA;
    cfg->pad_enable			= TRUE;
    cfg->phy_tx_ena_on		= FALSE;
    cfg->rx_sfd_any			= FALSE;
    cfg->rx_pbl_fwd			= FALSE;
    cfg->tx_pbl_fwd			= FALSE;
    cfg->debug_mode			= FALSE;
    cfg->wake_on_lan        = FALSE;
}