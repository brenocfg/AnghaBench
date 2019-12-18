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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/ * dmac_config_tcs; int /*<<< orphan*/ * dmac_update_tcs; int /*<<< orphan*/ * dmac_config; int /*<<< orphan*/ * check_link; int /*<<< orphan*/ * setup_link; int /*<<< orphan*/ * get_link_capabilities; int /*<<< orphan*/  fc_autoneg; int /*<<< orphan*/  setup_fc; int /*<<< orphan*/  fc_enable; int /*<<< orphan*/  disable_rx; int /*<<< orphan*/  enable_rx; int /*<<< orphan*/ * init_uta_tables; int /*<<< orphan*/ * set_vlvf; int /*<<< orphan*/ * set_vfta; int /*<<< orphan*/ * clear_vfta; int /*<<< orphan*/  disable_mc; int /*<<< orphan*/  enable_mc; int /*<<< orphan*/  update_mc_addr_list; int /*<<< orphan*/  update_uc_addr_list; int /*<<< orphan*/  init_rx_addrs; int /*<<< orphan*/ * clear_vmdq; int /*<<< orphan*/ * set_vmdq; int /*<<< orphan*/ * insert_mac_addr; int /*<<< orphan*/  clear_rar; int /*<<< orphan*/  set_rar; int /*<<< orphan*/  init_led_link_act; int /*<<< orphan*/  blink_led_stop; int /*<<< orphan*/  blink_led_start; int /*<<< orphan*/  led_off; int /*<<< orphan*/  led_on; int /*<<< orphan*/  prot_autoc_write; int /*<<< orphan*/  prot_autoc_read; int /*<<< orphan*/  release_swfw_sync; int /*<<< orphan*/  acquire_swfw_sync; int /*<<< orphan*/  set_lan_id; int /*<<< orphan*/  get_bus_info; int /*<<< orphan*/  stop_adapter; int /*<<< orphan*/  get_mac_addr; int /*<<< orphan*/  enable_rx_dma; int /*<<< orphan*/ * get_supported_physical_layer; int /*<<< orphan*/ * get_media_type; int /*<<< orphan*/  clear_hw_cntrs; int /*<<< orphan*/  start_hw; int /*<<< orphan*/ * reset_hw; int /*<<< orphan*/  init_hw; } ;
struct ixgbe_mac_info {TYPE_2__ ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  calc_checksum; int /*<<< orphan*/  update_checksum; int /*<<< orphan*/  validate_checksum; int /*<<< orphan*/  write_buffer; int /*<<< orphan*/  write; int /*<<< orphan*/  read_buffer; int /*<<< orphan*/  read; int /*<<< orphan*/  init_params; } ;
struct ixgbe_eeprom_info {TYPE_1__ ops; } ;
struct ixgbe_hw {struct ixgbe_mac_info mac; struct ixgbe_eeprom_info eeprom; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_EEC_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_EEC_PRES ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_acquire_swfw_sync ; 
 int /*<<< orphan*/  ixgbe_blink_led_start_generic ; 
 int /*<<< orphan*/  ixgbe_blink_led_stop_generic ; 
 int /*<<< orphan*/  ixgbe_calc_eeprom_checksum_generic ; 
 int /*<<< orphan*/  ixgbe_clear_hw_cntrs_generic ; 
 int /*<<< orphan*/  ixgbe_clear_rar_generic ; 
 int /*<<< orphan*/  ixgbe_disable_mc_generic ; 
 int /*<<< orphan*/  ixgbe_disable_rx_generic ; 
 int /*<<< orphan*/  ixgbe_enable_mc_generic ; 
 int /*<<< orphan*/  ixgbe_enable_rx_dma_generic ; 
 int /*<<< orphan*/  ixgbe_enable_rx_generic ; 
 int /*<<< orphan*/  ixgbe_fc_autoneg ; 
 int /*<<< orphan*/  ixgbe_fc_enable_generic ; 
 int /*<<< orphan*/  ixgbe_get_bus_info_generic ; 
 int /*<<< orphan*/  ixgbe_get_mac_addr_generic ; 
 int /*<<< orphan*/  ixgbe_init_eeprom_params_generic ; 
 int /*<<< orphan*/  ixgbe_init_hw_generic ; 
 int /*<<< orphan*/  ixgbe_init_led_link_act_generic ; 
 int /*<<< orphan*/  ixgbe_init_rx_addrs_generic ; 
 int /*<<< orphan*/  ixgbe_led_off_generic ; 
 int /*<<< orphan*/  ixgbe_led_on_generic ; 
 int /*<<< orphan*/  ixgbe_read_eeprom_bit_bang_generic ; 
 int /*<<< orphan*/  ixgbe_read_eeprom_buffer_bit_bang_generic ; 
 int /*<<< orphan*/  ixgbe_read_eerd_buffer_generic ; 
 int /*<<< orphan*/  ixgbe_read_eerd_generic ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync ; 
 int /*<<< orphan*/  ixgbe_set_lan_id_multi_port_pcie ; 
 int /*<<< orphan*/  ixgbe_set_rar_generic ; 
 int /*<<< orphan*/  ixgbe_setup_fc_generic ; 
 int /*<<< orphan*/  ixgbe_start_hw_generic ; 
 int /*<<< orphan*/  ixgbe_stop_adapter_generic ; 
 int /*<<< orphan*/  ixgbe_update_eeprom_checksum_generic ; 
 int /*<<< orphan*/  ixgbe_update_mc_addr_list_generic ; 
 int /*<<< orphan*/  ixgbe_update_uc_addr_list_generic ; 
 int /*<<< orphan*/  ixgbe_validate_eeprom_checksum_generic ; 
 int /*<<< orphan*/  ixgbe_write_eeprom_buffer_bit_bang_generic ; 
 int /*<<< orphan*/  ixgbe_write_eeprom_generic ; 
 int /*<<< orphan*/  prot_autoc_read_generic ; 
 int /*<<< orphan*/  prot_autoc_write_generic ; 

s32 ixgbe_init_ops_generic(struct ixgbe_hw *hw)
{
	struct ixgbe_eeprom_info *eeprom = &hw->eeprom;
	struct ixgbe_mac_info *mac = &hw->mac;
	u32 eec = IXGBE_READ_REG(hw, IXGBE_EEC_BY_MAC(hw));

	DEBUGFUNC("ixgbe_init_ops_generic");

	/* EEPROM */
	eeprom->ops.init_params = ixgbe_init_eeprom_params_generic;
	/* If EEPROM is valid (bit 8 = 1), use EERD otherwise use bit bang */
	if (eec & IXGBE_EEC_PRES) {
		eeprom->ops.read = ixgbe_read_eerd_generic;
		eeprom->ops.read_buffer = ixgbe_read_eerd_buffer_generic;
	} else {
		eeprom->ops.read = ixgbe_read_eeprom_bit_bang_generic;
		eeprom->ops.read_buffer =
				 ixgbe_read_eeprom_buffer_bit_bang_generic;
	}
	eeprom->ops.write = ixgbe_write_eeprom_generic;
	eeprom->ops.write_buffer = ixgbe_write_eeprom_buffer_bit_bang_generic;
	eeprom->ops.validate_checksum =
				      ixgbe_validate_eeprom_checksum_generic;
	eeprom->ops.update_checksum = ixgbe_update_eeprom_checksum_generic;
	eeprom->ops.calc_checksum = ixgbe_calc_eeprom_checksum_generic;

	/* MAC */
	mac->ops.init_hw = ixgbe_init_hw_generic;
	mac->ops.reset_hw = NULL;
	mac->ops.start_hw = ixgbe_start_hw_generic;
	mac->ops.clear_hw_cntrs = ixgbe_clear_hw_cntrs_generic;
	mac->ops.get_media_type = NULL;
	mac->ops.get_supported_physical_layer = NULL;
	mac->ops.enable_rx_dma = ixgbe_enable_rx_dma_generic;
	mac->ops.get_mac_addr = ixgbe_get_mac_addr_generic;
	mac->ops.stop_adapter = ixgbe_stop_adapter_generic;
	mac->ops.get_bus_info = ixgbe_get_bus_info_generic;
	mac->ops.set_lan_id = ixgbe_set_lan_id_multi_port_pcie;
	mac->ops.acquire_swfw_sync = ixgbe_acquire_swfw_sync;
	mac->ops.release_swfw_sync = ixgbe_release_swfw_sync;
	mac->ops.prot_autoc_read = prot_autoc_read_generic;
	mac->ops.prot_autoc_write = prot_autoc_write_generic;

	/* LEDs */
	mac->ops.led_on = ixgbe_led_on_generic;
	mac->ops.led_off = ixgbe_led_off_generic;
	mac->ops.blink_led_start = ixgbe_blink_led_start_generic;
	mac->ops.blink_led_stop = ixgbe_blink_led_stop_generic;
	mac->ops.init_led_link_act = ixgbe_init_led_link_act_generic;

	/* RAR, Multicast, VLAN */
	mac->ops.set_rar = ixgbe_set_rar_generic;
	mac->ops.clear_rar = ixgbe_clear_rar_generic;
	mac->ops.insert_mac_addr = NULL;
	mac->ops.set_vmdq = NULL;
	mac->ops.clear_vmdq = NULL;
	mac->ops.init_rx_addrs = ixgbe_init_rx_addrs_generic;
	mac->ops.update_uc_addr_list = ixgbe_update_uc_addr_list_generic;
	mac->ops.update_mc_addr_list = ixgbe_update_mc_addr_list_generic;
	mac->ops.enable_mc = ixgbe_enable_mc_generic;
	mac->ops.disable_mc = ixgbe_disable_mc_generic;
	mac->ops.clear_vfta = NULL;
	mac->ops.set_vfta = NULL;
	mac->ops.set_vlvf = NULL;
	mac->ops.init_uta_tables = NULL;
	mac->ops.enable_rx = ixgbe_enable_rx_generic;
	mac->ops.disable_rx = ixgbe_disable_rx_generic;

	/* Flow Control */
	mac->ops.fc_enable = ixgbe_fc_enable_generic;
	mac->ops.setup_fc = ixgbe_setup_fc_generic;
	mac->ops.fc_autoneg = ixgbe_fc_autoneg;

	/* Link */
	mac->ops.get_link_capabilities = NULL;
	mac->ops.setup_link = NULL;
	mac->ops.check_link = NULL;
	mac->ops.dmac_config = NULL;
	mac->ops.dmac_update_tcs = NULL;
	mac->ops.dmac_config_tcs = NULL;

	return IXGBE_SUCCESS;
}