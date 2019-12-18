#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  init; int /*<<< orphan*/  identify; } ;
struct ixgbe_phy_info {TYPE_1__ ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  get_rtrup2tc; int /*<<< orphan*/  bypass_rd_eep; int /*<<< orphan*/  bypass_set; int /*<<< orphan*/  bypass_valid_rd; int /*<<< orphan*/  bypass_rw; int /*<<< orphan*/  set_fw_drv_ver; int /*<<< orphan*/  setup_rxpba; int /*<<< orphan*/  check_link; int /*<<< orphan*/  get_link_capabilities; int /*<<< orphan*/  set_vlan_anti_spoofing; int /*<<< orphan*/  set_mac_anti_spoofing; int /*<<< orphan*/  setup_sfp; int /*<<< orphan*/  init_uta_tables; int /*<<< orphan*/  clear_vfta; int /*<<< orphan*/  set_vlvf; int /*<<< orphan*/  set_vfta; int /*<<< orphan*/  insert_mac_addr; int /*<<< orphan*/  clear_vmdq; int /*<<< orphan*/  set_vmdq_san_mac; int /*<<< orphan*/  set_vmdq; int /*<<< orphan*/  prot_autoc_write; int /*<<< orphan*/  prot_autoc_read; int /*<<< orphan*/  get_fcoe_boot_status; int /*<<< orphan*/  get_wwn_prefix; int /*<<< orphan*/  get_device_caps; int /*<<< orphan*/  set_san_mac_addr; int /*<<< orphan*/  get_san_mac_addr; int /*<<< orphan*/  start_hw; int /*<<< orphan*/  write_analog_reg8; int /*<<< orphan*/  read_analog_reg8; int /*<<< orphan*/  enable_rx_dma; int /*<<< orphan*/  enable_sec_rx_path; int /*<<< orphan*/  disable_sec_rx_path; int /*<<< orphan*/  get_supported_physical_layer; int /*<<< orphan*/  get_media_type; int /*<<< orphan*/  enable_relaxed_ordering; int /*<<< orphan*/  reset_hw; } ;
struct ixgbe_mac_info {int rar_highwater; int arc_subsystem_valid; TYPE_5__ ops; int /*<<< orphan*/  max_msix_vectors; int /*<<< orphan*/  max_tx_queues; int /*<<< orphan*/  max_rx_queues; int /*<<< orphan*/  rx_pb_size; int /*<<< orphan*/  num_rar_entries; int /*<<< orphan*/  vft_size; int /*<<< orphan*/  mcft_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  init_params; } ;
struct TYPE_8__ {TYPE_2__ ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  read_buffer; int /*<<< orphan*/  read; } ;
struct ixgbe_eeprom_info {TYPE_4__ ops; } ;
struct ixgbe_hw {TYPE_3__ mbx; struct ixgbe_eeprom_info eeprom; struct ixgbe_phy_info phy; struct ixgbe_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_82599_MAX_RX_QUEUES ; 
 int /*<<< orphan*/  IXGBE_82599_MAX_TX_QUEUES ; 
 int /*<<< orphan*/  IXGBE_82599_MC_TBL_SIZE ; 
 int /*<<< orphan*/  IXGBE_82599_RAR_ENTRIES ; 
 int /*<<< orphan*/  IXGBE_82599_RX_PB_SIZE ; 
 int /*<<< orphan*/  IXGBE_82599_VFT_TBL_SIZE ; 
 int /*<<< orphan*/  IXGBE_FWSM_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_FWSM_MODE_MASK ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_bypass_rd_eep_generic ; 
 int /*<<< orphan*/  ixgbe_bypass_rw_generic ; 
 int /*<<< orphan*/  ixgbe_bypass_set_generic ; 
 int /*<<< orphan*/  ixgbe_bypass_valid_rd_generic ; 
 int /*<<< orphan*/  ixgbe_check_mac_link_generic ; 
 int /*<<< orphan*/  ixgbe_clear_vfta_generic ; 
 int /*<<< orphan*/  ixgbe_clear_vmdq_generic ; 
 int /*<<< orphan*/  ixgbe_dcb_get_rtrup2tc_generic ; 
 int /*<<< orphan*/  ixgbe_disable_sec_rx_path_generic ; 
 int /*<<< orphan*/  ixgbe_enable_relaxed_ordering_gen2 ; 
 int /*<<< orphan*/  ixgbe_enable_rx_dma_82599 ; 
 int /*<<< orphan*/  ixgbe_enable_sec_rx_path_generic ; 
 int /*<<< orphan*/  ixgbe_get_device_caps_generic ; 
 int /*<<< orphan*/  ixgbe_get_fcoe_boot_status_generic ; 
 int /*<<< orphan*/  ixgbe_get_link_capabilities_82599 ; 
 int /*<<< orphan*/  ixgbe_get_media_type_82599 ; 
 int /*<<< orphan*/  ixgbe_get_pcie_msix_count_generic (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_get_san_mac_addr_generic ; 
 int /*<<< orphan*/  ixgbe_get_supported_physical_layer_82599 ; 
 int /*<<< orphan*/  ixgbe_get_wwn_prefix_generic ; 
 int /*<<< orphan*/  ixgbe_identify_phy_82599 ; 
 int /*<<< orphan*/  ixgbe_init_mac_link_ops_82599 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_mbx_params_pf ; 
 int /*<<< orphan*/  ixgbe_init_ops_generic (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_phy_ops_82599 ; 
 int /*<<< orphan*/  ixgbe_init_phy_ops_generic (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_uta_tables_generic ; 
 int /*<<< orphan*/  ixgbe_insert_mac_addr_generic ; 
 int /*<<< orphan*/  ixgbe_read_analog_reg8_82599 ; 
 int /*<<< orphan*/  ixgbe_read_eeprom_82599 ; 
 int /*<<< orphan*/  ixgbe_read_eeprom_buffer_82599 ; 
 int /*<<< orphan*/  ixgbe_reset_hw_82599 ; 
 int /*<<< orphan*/  ixgbe_set_fw_drv_ver_generic ; 
 int /*<<< orphan*/  ixgbe_set_mac_anti_spoofing ; 
 int /*<<< orphan*/  ixgbe_set_rxpba_generic ; 
 int /*<<< orphan*/  ixgbe_set_san_mac_addr_generic ; 
 int /*<<< orphan*/  ixgbe_set_vfta_generic ; 
 int /*<<< orphan*/  ixgbe_set_vlan_anti_spoofing ; 
 int /*<<< orphan*/  ixgbe_set_vlvf_generic ; 
 int /*<<< orphan*/  ixgbe_set_vmdq_generic ; 
 int /*<<< orphan*/  ixgbe_set_vmdq_san_mac_generic ; 
 int /*<<< orphan*/  ixgbe_setup_sfp_modules_82599 ; 
 int /*<<< orphan*/  ixgbe_start_hw_82599 ; 
 int /*<<< orphan*/  ixgbe_write_analog_reg8_82599 ; 
 int /*<<< orphan*/  prot_autoc_read_82599 ; 
 int /*<<< orphan*/  prot_autoc_write_82599 ; 

s32 ixgbe_init_ops_82599(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	struct ixgbe_phy_info *phy = &hw->phy;
	struct ixgbe_eeprom_info *eeprom = &hw->eeprom;
	s32 ret_val;

	DEBUGFUNC("ixgbe_init_ops_82599");

	ixgbe_init_phy_ops_generic(hw);
	ret_val = ixgbe_init_ops_generic(hw);

	/* PHY */
	phy->ops.identify = ixgbe_identify_phy_82599;
	phy->ops.init = ixgbe_init_phy_ops_82599;

	/* MAC */
	mac->ops.reset_hw = ixgbe_reset_hw_82599;
	mac->ops.enable_relaxed_ordering = ixgbe_enable_relaxed_ordering_gen2;
	mac->ops.get_media_type = ixgbe_get_media_type_82599;
	mac->ops.get_supported_physical_layer =
				    ixgbe_get_supported_physical_layer_82599;
	mac->ops.disable_sec_rx_path = ixgbe_disable_sec_rx_path_generic;
	mac->ops.enable_sec_rx_path = ixgbe_enable_sec_rx_path_generic;
	mac->ops.enable_rx_dma = ixgbe_enable_rx_dma_82599;
	mac->ops.read_analog_reg8 = ixgbe_read_analog_reg8_82599;
	mac->ops.write_analog_reg8 = ixgbe_write_analog_reg8_82599;
	mac->ops.start_hw = ixgbe_start_hw_82599;
	mac->ops.get_san_mac_addr = ixgbe_get_san_mac_addr_generic;
	mac->ops.set_san_mac_addr = ixgbe_set_san_mac_addr_generic;
	mac->ops.get_device_caps = ixgbe_get_device_caps_generic;
	mac->ops.get_wwn_prefix = ixgbe_get_wwn_prefix_generic;
	mac->ops.get_fcoe_boot_status = ixgbe_get_fcoe_boot_status_generic;
	mac->ops.prot_autoc_read = prot_autoc_read_82599;
	mac->ops.prot_autoc_write = prot_autoc_write_82599;

	/* RAR, Multicast, VLAN */
	mac->ops.set_vmdq = ixgbe_set_vmdq_generic;
	mac->ops.set_vmdq_san_mac = ixgbe_set_vmdq_san_mac_generic;
	mac->ops.clear_vmdq = ixgbe_clear_vmdq_generic;
	mac->ops.insert_mac_addr = ixgbe_insert_mac_addr_generic;
	mac->rar_highwater = 1;
	mac->ops.set_vfta = ixgbe_set_vfta_generic;
	mac->ops.set_vlvf = ixgbe_set_vlvf_generic;
	mac->ops.clear_vfta = ixgbe_clear_vfta_generic;
	mac->ops.init_uta_tables = ixgbe_init_uta_tables_generic;
	mac->ops.setup_sfp = ixgbe_setup_sfp_modules_82599;
	mac->ops.set_mac_anti_spoofing = ixgbe_set_mac_anti_spoofing;
	mac->ops.set_vlan_anti_spoofing = ixgbe_set_vlan_anti_spoofing;

	/* Link */
	mac->ops.get_link_capabilities = ixgbe_get_link_capabilities_82599;
	mac->ops.check_link = ixgbe_check_mac_link_generic;
	mac->ops.setup_rxpba = ixgbe_set_rxpba_generic;
	ixgbe_init_mac_link_ops_82599(hw);

	mac->mcft_size		= IXGBE_82599_MC_TBL_SIZE;
	mac->vft_size		= IXGBE_82599_VFT_TBL_SIZE;
	mac->num_rar_entries	= IXGBE_82599_RAR_ENTRIES;
	mac->rx_pb_size		= IXGBE_82599_RX_PB_SIZE;
	mac->max_rx_queues	= IXGBE_82599_MAX_RX_QUEUES;
	mac->max_tx_queues	= IXGBE_82599_MAX_TX_QUEUES;
	mac->max_msix_vectors	= ixgbe_get_pcie_msix_count_generic(hw);

	mac->arc_subsystem_valid = !!(IXGBE_READ_REG(hw, IXGBE_FWSM_BY_MAC(hw))
				      & IXGBE_FWSM_MODE_MASK);

	hw->mbx.ops.init_params = ixgbe_init_mbx_params_pf;

	/* EEPROM */
	eeprom->ops.read = ixgbe_read_eeprom_82599;
	eeprom->ops.read_buffer = ixgbe_read_eeprom_buffer_82599;

	/* Manageability interface */
	mac->ops.set_fw_drv_ver = ixgbe_set_fw_drv_ver_generic;

	mac->ops.bypass_rw = ixgbe_bypass_rw_generic;
	mac->ops.bypass_valid_rd = ixgbe_bypass_valid_rd_generic;
	mac->ops.bypass_set = ixgbe_bypass_set_generic;
	mac->ops.bypass_rd_eep = ixgbe_bypass_rd_eep_generic;

	mac->ops.get_rtrup2tc = ixgbe_dcb_get_rtrup2tc_generic;

	return ret_val;
}