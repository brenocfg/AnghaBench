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
struct TYPE_4__ {int /*<<< orphan*/ * led_off; int /*<<< orphan*/ * led_on; int /*<<< orphan*/  set_fw_drv_ver; int /*<<< orphan*/  disable_rx; int /*<<< orphan*/  restore_mdd_vf; int /*<<< orphan*/  mdd_event; int /*<<< orphan*/  enable_mdd; int /*<<< orphan*/  disable_mdd; int /*<<< orphan*/  get_rtrup2tc; int /*<<< orphan*/  set_ethertype_anti_spoofing; int /*<<< orphan*/  set_source_address_pruning; int /*<<< orphan*/ * setup_eee; int /*<<< orphan*/  dmac_update_tcs; int /*<<< orphan*/  dmac_config_tcs; int /*<<< orphan*/  dmac_config; } ;
struct ixgbe_mac_info {TYPE_2__ ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  validate_checksum; int /*<<< orphan*/  update_checksum; int /*<<< orphan*/  write_buffer; int /*<<< orphan*/  write; int /*<<< orphan*/  read_buffer; int /*<<< orphan*/  read; int /*<<< orphan*/  calc_checksum; int /*<<< orphan*/  init_params; } ;
struct ixgbe_eeprom_info {TYPE_1__ ops; } ;
struct ixgbe_hw {int device_id; struct ixgbe_mac_info mac; struct ixgbe_eeprom_info eeprom; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
#define  IXGBE_DEV_ID_X550EM_A_10G_T 130 
#define  IXGBE_DEV_ID_X550EM_X_10G_T 129 
#define  IXGBE_DEV_ID_X550EM_X_1G_T 128 
 int /*<<< orphan*/  ixgbe_calc_eeprom_checksum_X550 ; 
 int /*<<< orphan*/  ixgbe_dcb_get_rtrup2tc_generic ; 
 int /*<<< orphan*/  ixgbe_disable_mdd_X550 ; 
 int /*<<< orphan*/  ixgbe_disable_rx_x550 ; 
 int /*<<< orphan*/  ixgbe_dmac_config_X550 ; 
 int /*<<< orphan*/  ixgbe_dmac_config_tcs_X550 ; 
 int /*<<< orphan*/  ixgbe_dmac_update_tcs_X550 ; 
 int /*<<< orphan*/  ixgbe_enable_mdd_X550 ; 
 int /*<<< orphan*/  ixgbe_init_eeprom_params_X550 ; 
 int /*<<< orphan*/  ixgbe_init_ops_X540 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/ * ixgbe_led_off_t_X550em ; 
 int /*<<< orphan*/ * ixgbe_led_on_t_X550em ; 
 int /*<<< orphan*/  ixgbe_mdd_event_X550 ; 
 int /*<<< orphan*/  ixgbe_read_ee_hostif_X550 ; 
 int /*<<< orphan*/  ixgbe_read_ee_hostif_buffer_X550 ; 
 int /*<<< orphan*/  ixgbe_restore_mdd_vf_X550 ; 
 int /*<<< orphan*/  ixgbe_set_ethertype_anti_spoofing_X550 ; 
 int /*<<< orphan*/  ixgbe_set_fw_drv_ver_x550 ; 
 int /*<<< orphan*/  ixgbe_set_source_address_pruning_X550 ; 
 int /*<<< orphan*/  ixgbe_update_eeprom_checksum_X550 ; 
 int /*<<< orphan*/  ixgbe_validate_eeprom_checksum_X550 ; 
 int /*<<< orphan*/  ixgbe_write_ee_hostif_X550 ; 
 int /*<<< orphan*/  ixgbe_write_ee_hostif_buffer_X550 ; 

s32 ixgbe_init_ops_X550(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	struct ixgbe_eeprom_info *eeprom = &hw->eeprom;
	s32 ret_val;

	DEBUGFUNC("ixgbe_init_ops_X550");

	ret_val = ixgbe_init_ops_X540(hw);
	mac->ops.dmac_config = ixgbe_dmac_config_X550;
	mac->ops.dmac_config_tcs = ixgbe_dmac_config_tcs_X550;
	mac->ops.dmac_update_tcs = ixgbe_dmac_update_tcs_X550;
	mac->ops.setup_eee = NULL;
	mac->ops.set_source_address_pruning =
			ixgbe_set_source_address_pruning_X550;
	mac->ops.set_ethertype_anti_spoofing =
			ixgbe_set_ethertype_anti_spoofing_X550;

	mac->ops.get_rtrup2tc = ixgbe_dcb_get_rtrup2tc_generic;
	eeprom->ops.init_params = ixgbe_init_eeprom_params_X550;
	eeprom->ops.calc_checksum = ixgbe_calc_eeprom_checksum_X550;
	eeprom->ops.read = ixgbe_read_ee_hostif_X550;
	eeprom->ops.read_buffer = ixgbe_read_ee_hostif_buffer_X550;
	eeprom->ops.write = ixgbe_write_ee_hostif_X550;
	eeprom->ops.write_buffer = ixgbe_write_ee_hostif_buffer_X550;
	eeprom->ops.update_checksum = ixgbe_update_eeprom_checksum_X550;
	eeprom->ops.validate_checksum = ixgbe_validate_eeprom_checksum_X550;

	mac->ops.disable_mdd = ixgbe_disable_mdd_X550;
	mac->ops.enable_mdd = ixgbe_enable_mdd_X550;
	mac->ops.mdd_event = ixgbe_mdd_event_X550;
	mac->ops.restore_mdd_vf = ixgbe_restore_mdd_vf_X550;
	mac->ops.disable_rx = ixgbe_disable_rx_x550;
	/* Manageability interface */
	mac->ops.set_fw_drv_ver = ixgbe_set_fw_drv_ver_x550;
	switch (hw->device_id) {
	case IXGBE_DEV_ID_X550EM_X_1G_T:
		hw->mac.ops.led_on = NULL;
		hw->mac.ops.led_off = NULL;
		break;
	case IXGBE_DEV_ID_X550EM_X_10G_T:
	case IXGBE_DEV_ID_X550EM_A_10G_T:
		hw->mac.ops.led_on = ixgbe_led_on_t_X550em;
		hw->mac.ops.led_off = ixgbe_led_off_t_X550em;
		break;
	default:
		break;
	}
	return ret_val;
}