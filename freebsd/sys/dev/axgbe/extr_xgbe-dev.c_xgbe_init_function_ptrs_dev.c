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
struct xgbe_hw_if {int /*<<< orphan*/  disable_rss; int /*<<< orphan*/  read_mmc_stats; int /*<<< orphan*/  rx_mmc_int; int /*<<< orphan*/  tx_mmc_int; int /*<<< orphan*/  config_pblx8; int /*<<< orphan*/  get_tx_pbl_val; int /*<<< orphan*/  config_tx_pbl_val; int /*<<< orphan*/  get_rx_pbl_val; int /*<<< orphan*/  config_rx_pbl_val; int /*<<< orphan*/  config_osp_mode; int /*<<< orphan*/  config_tsf_mode; int /*<<< orphan*/  config_rsf_mode; int /*<<< orphan*/  config_tx_threshold; int /*<<< orphan*/  config_rx_threshold; int /*<<< orphan*/  riwt_to_usec; int /*<<< orphan*/  usec_to_riwt; int /*<<< orphan*/  config_tx_coalesce; int /*<<< orphan*/  config_rx_coalesce; int /*<<< orphan*/  config_rx_flow_control; int /*<<< orphan*/  config_tx_flow_control; int /*<<< orphan*/  tx_start_xmit; int /*<<< orphan*/  is_context_desc; int /*<<< orphan*/  is_last_desc; int /*<<< orphan*/  rx_desc_reset; int /*<<< orphan*/  tx_desc_reset; int /*<<< orphan*/  rx_desc_init; int /*<<< orphan*/  tx_desc_init; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; int /*<<< orphan*/  disable_int; int /*<<< orphan*/  enable_int; int /*<<< orphan*/  dev_read; int /*<<< orphan*/  dev_xmit; int /*<<< orphan*/  powerdown_rx; int /*<<< orphan*/  powerup_rx; int /*<<< orphan*/  powerdown_tx; int /*<<< orphan*/  powerup_tx; int /*<<< orphan*/  disable_rx; int /*<<< orphan*/  enable_rx; int /*<<< orphan*/  disable_tx; int /*<<< orphan*/  enable_tx; int /*<<< orphan*/  set_xgmii_speed; int /*<<< orphan*/  set_gmii_2500_speed; int /*<<< orphan*/  set_gmii_speed; int /*<<< orphan*/  write_mmd_regs; int /*<<< orphan*/  read_mmd_regs; int /*<<< orphan*/  update_vlan_hash_table; int /*<<< orphan*/  disable_rx_vlan_filtering; int /*<<< orphan*/  enable_rx_vlan_filtering; int /*<<< orphan*/  disable_rx_vlan_stripping; int /*<<< orphan*/  enable_rx_vlan_stripping; int /*<<< orphan*/  disable_rx_csum; int /*<<< orphan*/  enable_rx_csum; int /*<<< orphan*/  config_rx_mode; int /*<<< orphan*/  set_mac_address; int /*<<< orphan*/  tx_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  xgbe_config_osp_mode ; 
 int /*<<< orphan*/  xgbe_config_pblx8 ; 
 int /*<<< orphan*/  xgbe_config_rsf_mode ; 
 int /*<<< orphan*/  xgbe_config_rx_coalesce ; 
 int /*<<< orphan*/  xgbe_config_rx_flow_control ; 
 int /*<<< orphan*/  xgbe_config_rx_mode ; 
 int /*<<< orphan*/  xgbe_config_rx_pbl_val ; 
 int /*<<< orphan*/  xgbe_config_rx_threshold ; 
 int /*<<< orphan*/  xgbe_config_tsf_mode ; 
 int /*<<< orphan*/  xgbe_config_tx_coalesce ; 
 int /*<<< orphan*/  xgbe_config_tx_flow_control ; 
 int /*<<< orphan*/  xgbe_config_tx_pbl_val ; 
 int /*<<< orphan*/  xgbe_config_tx_threshold ; 
 int /*<<< orphan*/  xgbe_dev_read ; 
 int /*<<< orphan*/  xgbe_dev_xmit ; 
 int /*<<< orphan*/  xgbe_disable_int ; 
 int /*<<< orphan*/  xgbe_disable_rss ; 
 int /*<<< orphan*/  xgbe_disable_rx ; 
 int /*<<< orphan*/  xgbe_disable_rx_csum ; 
 int /*<<< orphan*/  xgbe_disable_rx_vlan_filtering ; 
 int /*<<< orphan*/  xgbe_disable_rx_vlan_stripping ; 
 int /*<<< orphan*/  xgbe_disable_tx ; 
 int /*<<< orphan*/  xgbe_enable_int ; 
 int /*<<< orphan*/  xgbe_enable_rx ; 
 int /*<<< orphan*/  xgbe_enable_rx_csum ; 
 int /*<<< orphan*/  xgbe_enable_rx_vlan_filtering ; 
 int /*<<< orphan*/  xgbe_enable_rx_vlan_stripping ; 
 int /*<<< orphan*/  xgbe_enable_tx ; 
 int /*<<< orphan*/  xgbe_exit ; 
 int /*<<< orphan*/  xgbe_get_rx_pbl_val ; 
 int /*<<< orphan*/  xgbe_get_tx_pbl_val ; 
 int /*<<< orphan*/  xgbe_init ; 
 int /*<<< orphan*/  xgbe_is_context_desc ; 
 int /*<<< orphan*/  xgbe_is_last_desc ; 
 int /*<<< orphan*/  xgbe_powerdown_rx ; 
 int /*<<< orphan*/  xgbe_powerdown_tx ; 
 int /*<<< orphan*/  xgbe_powerup_rx ; 
 int /*<<< orphan*/  xgbe_powerup_tx ; 
 int /*<<< orphan*/  xgbe_read_mmc_stats ; 
 int /*<<< orphan*/  xgbe_read_mmd_regs ; 
 int /*<<< orphan*/  xgbe_riwt_to_usec ; 
 int /*<<< orphan*/  xgbe_rx_desc_init ; 
 int /*<<< orphan*/  xgbe_rx_desc_reset ; 
 int /*<<< orphan*/  xgbe_rx_mmc_int ; 
 int /*<<< orphan*/  xgbe_set_gmii_2500_speed ; 
 int /*<<< orphan*/  xgbe_set_gmii_speed ; 
 int /*<<< orphan*/  xgbe_set_mac_address ; 
 int /*<<< orphan*/  xgbe_set_xgmii_speed ; 
 int /*<<< orphan*/  xgbe_tx_complete ; 
 int /*<<< orphan*/  xgbe_tx_desc_init ; 
 int /*<<< orphan*/  xgbe_tx_desc_reset ; 
 int /*<<< orphan*/  xgbe_tx_mmc_int ; 
 int /*<<< orphan*/  xgbe_tx_start_xmit ; 
 int /*<<< orphan*/  xgbe_update_vlan_hash_table ; 
 int /*<<< orphan*/  xgbe_usec_to_riwt ; 
 int /*<<< orphan*/  xgbe_write_mmd_regs ; 

void xgbe_init_function_ptrs_dev(struct xgbe_hw_if *hw_if)
{
	DBGPR("-->xgbe_init_function_ptrs\n");

	hw_if->tx_complete = xgbe_tx_complete;

	hw_if->set_mac_address = xgbe_set_mac_address;
	hw_if->config_rx_mode = xgbe_config_rx_mode;

	hw_if->enable_rx_csum = xgbe_enable_rx_csum;
	hw_if->disable_rx_csum = xgbe_disable_rx_csum;

	hw_if->enable_rx_vlan_stripping = xgbe_enable_rx_vlan_stripping;
	hw_if->disable_rx_vlan_stripping = xgbe_disable_rx_vlan_stripping;
	hw_if->enable_rx_vlan_filtering = xgbe_enable_rx_vlan_filtering;
	hw_if->disable_rx_vlan_filtering = xgbe_disable_rx_vlan_filtering;
	hw_if->update_vlan_hash_table = xgbe_update_vlan_hash_table;

	hw_if->read_mmd_regs = xgbe_read_mmd_regs;
	hw_if->write_mmd_regs = xgbe_write_mmd_regs;

	hw_if->set_gmii_speed = xgbe_set_gmii_speed;
	hw_if->set_gmii_2500_speed = xgbe_set_gmii_2500_speed;
	hw_if->set_xgmii_speed = xgbe_set_xgmii_speed;

	hw_if->enable_tx = xgbe_enable_tx;
	hw_if->disable_tx = xgbe_disable_tx;
	hw_if->enable_rx = xgbe_enable_rx;
	hw_if->disable_rx = xgbe_disable_rx;

	hw_if->powerup_tx = xgbe_powerup_tx;
	hw_if->powerdown_tx = xgbe_powerdown_tx;
	hw_if->powerup_rx = xgbe_powerup_rx;
	hw_if->powerdown_rx = xgbe_powerdown_rx;

	hw_if->dev_xmit = xgbe_dev_xmit;
	hw_if->dev_read = xgbe_dev_read;
	hw_if->enable_int = xgbe_enable_int;
	hw_if->disable_int = xgbe_disable_int;
	hw_if->init = xgbe_init;
	hw_if->exit = xgbe_exit;

	/* Descriptor related Sequences have to be initialized here */
	hw_if->tx_desc_init = xgbe_tx_desc_init;
	hw_if->rx_desc_init = xgbe_rx_desc_init;
	hw_if->tx_desc_reset = xgbe_tx_desc_reset;
	hw_if->rx_desc_reset = xgbe_rx_desc_reset;
	hw_if->is_last_desc = xgbe_is_last_desc;
	hw_if->is_context_desc = xgbe_is_context_desc;
	hw_if->tx_start_xmit = xgbe_tx_start_xmit;

	/* For FLOW ctrl */
	hw_if->config_tx_flow_control = xgbe_config_tx_flow_control;
	hw_if->config_rx_flow_control = xgbe_config_rx_flow_control;

	/* For RX coalescing */
	hw_if->config_rx_coalesce = xgbe_config_rx_coalesce;
	hw_if->config_tx_coalesce = xgbe_config_tx_coalesce;
	hw_if->usec_to_riwt = xgbe_usec_to_riwt;
	hw_if->riwt_to_usec = xgbe_riwt_to_usec;

	/* For RX and TX threshold config */
	hw_if->config_rx_threshold = xgbe_config_rx_threshold;
	hw_if->config_tx_threshold = xgbe_config_tx_threshold;

	/* For RX and TX Store and Forward Mode config */
	hw_if->config_rsf_mode = xgbe_config_rsf_mode;
	hw_if->config_tsf_mode = xgbe_config_tsf_mode;

	/* For TX DMA Operating on Second Frame config */
	hw_if->config_osp_mode = xgbe_config_osp_mode;

	/* For RX and TX PBL config */
	hw_if->config_rx_pbl_val = xgbe_config_rx_pbl_val;
	hw_if->get_rx_pbl_val = xgbe_get_rx_pbl_val;
	hw_if->config_tx_pbl_val = xgbe_config_tx_pbl_val;
	hw_if->get_tx_pbl_val = xgbe_get_tx_pbl_val;
	hw_if->config_pblx8 = xgbe_config_pblx8;

	/* For MMC statistics support */
	hw_if->tx_mmc_int = xgbe_tx_mmc_int;
	hw_if->rx_mmc_int = xgbe_rx_mmc_int;
	hw_if->read_mmc_stats = xgbe_read_mmc_stats;

	/* For Receive Side Scaling */
	hw_if->disable_rss = xgbe_disable_rss;

	DBGPR("<--xgbe_init_function_ptrs\n");
}