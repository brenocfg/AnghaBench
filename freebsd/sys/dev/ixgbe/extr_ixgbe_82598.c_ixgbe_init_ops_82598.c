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
struct TYPE_3__ {int /*<<< orphan*/  read_i2c_sff8472; int /*<<< orphan*/  read_i2c_eeprom; int /*<<< orphan*/  init; } ;
struct ixgbe_phy_info {TYPE_1__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/ * get_rtrup2tc; int /*<<< orphan*/ * set_fw_drv_ver; int /*<<< orphan*/  setup_rxpba; int /*<<< orphan*/  get_link_capabilities; int /*<<< orphan*/ * flap_tx_laser; int /*<<< orphan*/  setup_link; int /*<<< orphan*/  check_link; int /*<<< orphan*/  fc_enable; int /*<<< orphan*/  clear_vfta; int /*<<< orphan*/ * set_vlvf; int /*<<< orphan*/  set_vfta; int /*<<< orphan*/  clear_vmdq; int /*<<< orphan*/  set_vmdq; int /*<<< orphan*/  enable_rx_dma; int /*<<< orphan*/  set_lan_id; int /*<<< orphan*/  write_analog_reg8; int /*<<< orphan*/  read_analog_reg8; int /*<<< orphan*/  get_supported_physical_layer; int /*<<< orphan*/  get_media_type; int /*<<< orphan*/  reset_hw; int /*<<< orphan*/  enable_relaxed_ordering; int /*<<< orphan*/  start_hw; } ;
struct ixgbe_mac_info {TYPE_2__ ops; int /*<<< orphan*/  max_msix_vectors; int /*<<< orphan*/  max_tx_queues; int /*<<< orphan*/  max_rx_queues; int /*<<< orphan*/  rx_pb_size; int /*<<< orphan*/  num_rar_entries; int /*<<< orphan*/  vft_size; int /*<<< orphan*/  mcft_size; } ;
struct ixgbe_hw {struct ixgbe_phy_info phy; struct ixgbe_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_82598_MAX_RX_QUEUES ; 
 int /*<<< orphan*/  IXGBE_82598_MAX_TX_QUEUES ; 
 int /*<<< orphan*/  IXGBE_82598_MC_TBL_SIZE ; 
 int /*<<< orphan*/  IXGBE_82598_RAR_ENTRIES ; 
 int /*<<< orphan*/  IXGBE_82598_RX_PB_SIZE ; 
 int /*<<< orphan*/  IXGBE_82598_VFT_TBL_SIZE ; 
 int /*<<< orphan*/  ixgbe_check_mac_link_82598 ; 
 int /*<<< orphan*/  ixgbe_clear_vfta_82598 ; 
 int /*<<< orphan*/  ixgbe_clear_vmdq_82598 ; 
 int /*<<< orphan*/  ixgbe_enable_relaxed_ordering_82598 ; 
 int /*<<< orphan*/  ixgbe_enable_rx_dma_82598 ; 
 int /*<<< orphan*/  ixgbe_fc_enable_82598 ; 
 int /*<<< orphan*/  ixgbe_get_link_capabilities_82598 ; 
 int /*<<< orphan*/  ixgbe_get_media_type_82598 ; 
 int /*<<< orphan*/  ixgbe_get_pcie_msix_count_generic (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_get_supported_physical_layer_82598 ; 
 int /*<<< orphan*/  ixgbe_init_ops_generic (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_phy_ops_82598 ; 
 int /*<<< orphan*/  ixgbe_init_phy_ops_generic (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_read_analog_reg8_82598 ; 
 int /*<<< orphan*/  ixgbe_read_i2c_eeprom_82598 ; 
 int /*<<< orphan*/  ixgbe_read_i2c_sff8472_82598 ; 
 int /*<<< orphan*/  ixgbe_reset_hw_82598 ; 
 int /*<<< orphan*/  ixgbe_set_lan_id_multi_port_pcie_82598 ; 
 int /*<<< orphan*/  ixgbe_set_rxpba_82598 ; 
 int /*<<< orphan*/  ixgbe_set_vfta_82598 ; 
 int /*<<< orphan*/  ixgbe_set_vmdq_82598 ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_82598 ; 
 int /*<<< orphan*/  ixgbe_start_hw_82598 ; 
 int /*<<< orphan*/  ixgbe_write_analog_reg8_82598 ; 

s32 ixgbe_init_ops_82598(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	struct ixgbe_phy_info *phy = &hw->phy;
	s32 ret_val;

	DEBUGFUNC("ixgbe_init_ops_82598");

	ret_val = ixgbe_init_phy_ops_generic(hw);
	ret_val = ixgbe_init_ops_generic(hw);

	/* PHY */
	phy->ops.init = ixgbe_init_phy_ops_82598;

	/* MAC */
	mac->ops.start_hw = ixgbe_start_hw_82598;
	mac->ops.enable_relaxed_ordering = ixgbe_enable_relaxed_ordering_82598;
	mac->ops.reset_hw = ixgbe_reset_hw_82598;
	mac->ops.get_media_type = ixgbe_get_media_type_82598;
	mac->ops.get_supported_physical_layer =
				ixgbe_get_supported_physical_layer_82598;
	mac->ops.read_analog_reg8 = ixgbe_read_analog_reg8_82598;
	mac->ops.write_analog_reg8 = ixgbe_write_analog_reg8_82598;
	mac->ops.set_lan_id = ixgbe_set_lan_id_multi_port_pcie_82598;
	mac->ops.enable_rx_dma = ixgbe_enable_rx_dma_82598;

	/* RAR, Multicast, VLAN */
	mac->ops.set_vmdq = ixgbe_set_vmdq_82598;
	mac->ops.clear_vmdq = ixgbe_clear_vmdq_82598;
	mac->ops.set_vfta = ixgbe_set_vfta_82598;
	mac->ops.set_vlvf = NULL;
	mac->ops.clear_vfta = ixgbe_clear_vfta_82598;

	/* Flow Control */
	mac->ops.fc_enable = ixgbe_fc_enable_82598;

	mac->mcft_size		= IXGBE_82598_MC_TBL_SIZE;
	mac->vft_size		= IXGBE_82598_VFT_TBL_SIZE;
	mac->num_rar_entries	= IXGBE_82598_RAR_ENTRIES;
	mac->rx_pb_size		= IXGBE_82598_RX_PB_SIZE;
	mac->max_rx_queues	= IXGBE_82598_MAX_RX_QUEUES;
	mac->max_tx_queues	= IXGBE_82598_MAX_TX_QUEUES;
	mac->max_msix_vectors	= ixgbe_get_pcie_msix_count_generic(hw);

	/* SFP+ Module */
	phy->ops.read_i2c_eeprom = ixgbe_read_i2c_eeprom_82598;
	phy->ops.read_i2c_sff8472 = ixgbe_read_i2c_sff8472_82598;

	/* Link */
	mac->ops.check_link = ixgbe_check_mac_link_82598;
	mac->ops.setup_link = ixgbe_setup_mac_link_82598;
	mac->ops.flap_tx_laser = NULL;
	mac->ops.get_link_capabilities = ixgbe_get_link_capabilities_82598;
	mac->ops.setup_rxpba = ixgbe_set_rxpba_82598;

	/* Manageability interface */
	mac->ops.set_fw_drv_ver = NULL;

	mac->ops.get_rtrup2tc = NULL;

	return ret_val;
}