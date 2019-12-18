#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * set_phy_power; void* identify; int /*<<< orphan*/ * get_firmware_version; int /*<<< orphan*/  init; } ;
struct ixgbe_phy_info {TYPE_3__ ops; } ;
struct TYPE_6__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;int /*<<< orphan*/ * setup_fc; int /*<<< orphan*/  get_supported_physical_layer; int /*<<< orphan*/  reset_hw; int /*<<< orphan*/  get_link_capabilities; int /*<<< orphan*/  setup_sfp; int /*<<< orphan*/  get_bus_info; int /*<<< orphan*/ * prot_autoc_write; int /*<<< orphan*/ * prot_autoc_read; int /*<<< orphan*/ * enable_sec_rx_path; int /*<<< orphan*/ * disable_sec_rx_path; int /*<<< orphan*/ * get_fcoe_boot_status; int /*<<< orphan*/ * get_wwn_prefix; int /*<<< orphan*/ * set_san_mac_addr; int /*<<< orphan*/ * get_san_mac_addr; int /*<<< orphan*/ * bypass_rd_eep; int /*<<< orphan*/ * bypass_set; int /*<<< orphan*/ * bypass_valid_rd; int /*<<< orphan*/ * bypass_rw; } ;
struct ixgbe_mac_info {TYPE_2__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  calc_checksum; int /*<<< orphan*/  validate_checksum; int /*<<< orphan*/  update_checksum; int /*<<< orphan*/  write_buffer; int /*<<< orphan*/  write; int /*<<< orphan*/  read_buffer; int /*<<< orphan*/  read; int /*<<< orphan*/  init_params; } ;
struct ixgbe_eeprom_info {TYPE_4__ ops; } ;
struct ixgbe_hw {int device_id; TYPE_1__ bus; struct ixgbe_phy_info phy; struct ixgbe_eeprom_info eeprom; struct ixgbe_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
#define  IXGBE_DEV_ID_X550EM_A_1G_T 130 
#define  IXGBE_DEV_ID_X550EM_A_1G_T_L 129 
#define  IXGBE_DEV_ID_X550EM_X_1G_T 128 
 int /*<<< orphan*/  ixgbe_bus_type_internal ; 
 int /*<<< orphan*/  ixgbe_calc_eeprom_checksum_X550 ; 
 int /*<<< orphan*/  ixgbe_get_bus_info_X550em ; 
 int /*<<< orphan*/  ixgbe_get_link_capabilities_X550em ; 
 scalar_t__ ixgbe_get_media_type_X550em (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_get_supported_physical_layer_X550em ; 
 void* ixgbe_identify_phy_fw ; 
 void* ixgbe_identify_phy_x550em ; 
 int /*<<< orphan*/  ixgbe_init_eeprom_params_X540 ; 
 int /*<<< orphan*/  ixgbe_init_ops_X550 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_phy_ops_X550em ; 
 scalar_t__ ixgbe_media_type_copper ; 
 int /*<<< orphan*/  ixgbe_read_ee_hostif_X550 ; 
 int /*<<< orphan*/  ixgbe_read_ee_hostif_buffer_X550 ; 
 int /*<<< orphan*/  ixgbe_reset_hw_X550em ; 
 int /*<<< orphan*/ * ixgbe_setup_fc_X550em ; 
 int /*<<< orphan*/ * ixgbe_setup_fc_generic ; 
 int /*<<< orphan*/  ixgbe_setup_sfp_modules_X550em ; 
 int /*<<< orphan*/  ixgbe_update_eeprom_checksum_X550 ; 
 int /*<<< orphan*/  ixgbe_validate_eeprom_checksum_X550 ; 
 int /*<<< orphan*/  ixgbe_write_ee_hostif_X550 ; 
 int /*<<< orphan*/  ixgbe_write_ee_hostif_buffer_X550 ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*) ; 

s32 ixgbe_init_ops_X550EM(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	struct ixgbe_eeprom_info *eeprom = &hw->eeprom;
	struct ixgbe_phy_info *phy = &hw->phy;
	s32 ret_val;

	DEBUGFUNC("ixgbe_init_ops_X550EM");

	/* Similar to X550 so start there. */
	ret_val = ixgbe_init_ops_X550(hw);

	/* Since this function eventually calls
	 * ixgbe_init_ops_540 by design, we are setting
	 * the pointers to NULL explicitly here to overwrite
	 * the values being set in the x540 function.
	 */

	/* Bypass not supported in x550EM */
	mac->ops.bypass_rw = NULL;
	mac->ops.bypass_valid_rd = NULL;
	mac->ops.bypass_set = NULL;
	mac->ops.bypass_rd_eep = NULL;

	/* FCOE not supported in x550EM */
	mac->ops.get_san_mac_addr = NULL;
	mac->ops.set_san_mac_addr = NULL;
	mac->ops.get_wwn_prefix = NULL;
	mac->ops.get_fcoe_boot_status = NULL;

	/* IPsec not supported in x550EM */
	mac->ops.disable_sec_rx_path = NULL;
	mac->ops.enable_sec_rx_path = NULL;

	/* AUTOC register is not present in x550EM. */
	mac->ops.prot_autoc_read = NULL;
	mac->ops.prot_autoc_write = NULL;

	/* X550EM bus type is internal*/
	hw->bus.type = ixgbe_bus_type_internal;
	mac->ops.get_bus_info = ixgbe_get_bus_info_X550em;


	mac->ops.get_media_type = ixgbe_get_media_type_X550em;
	mac->ops.setup_sfp = ixgbe_setup_sfp_modules_X550em;
	mac->ops.get_link_capabilities = ixgbe_get_link_capabilities_X550em;
	mac->ops.reset_hw = ixgbe_reset_hw_X550em;
	mac->ops.get_supported_physical_layer =
				    ixgbe_get_supported_physical_layer_X550em;

	if (mac->ops.get_media_type(hw) == ixgbe_media_type_copper)
		mac->ops.setup_fc = ixgbe_setup_fc_generic;
	else
		mac->ops.setup_fc = ixgbe_setup_fc_X550em;

	/* PHY */
	phy->ops.init = ixgbe_init_phy_ops_X550em;
	switch (hw->device_id) {
	case IXGBE_DEV_ID_X550EM_A_1G_T:
	case IXGBE_DEV_ID_X550EM_A_1G_T_L:
		mac->ops.setup_fc = NULL;
		phy->ops.identify = ixgbe_identify_phy_fw;
		phy->ops.set_phy_power = NULL;
		phy->ops.get_firmware_version = NULL;
		break;
	case IXGBE_DEV_ID_X550EM_X_1G_T:
		mac->ops.setup_fc = NULL;
		phy->ops.identify = ixgbe_identify_phy_x550em;
		phy->ops.set_phy_power = NULL;
		break;
	default:
		phy->ops.identify = ixgbe_identify_phy_x550em;
	}

	if (mac->ops.get_media_type(hw) != ixgbe_media_type_copper)
		phy->ops.set_phy_power = NULL;


	/* EEPROM */
	eeprom->ops.init_params = ixgbe_init_eeprom_params_X540;
	eeprom->ops.read = ixgbe_read_ee_hostif_X550;
	eeprom->ops.read_buffer = ixgbe_read_ee_hostif_buffer_X550;
	eeprom->ops.write = ixgbe_write_ee_hostif_X550;
	eeprom->ops.write_buffer = ixgbe_write_ee_hostif_buffer_X550;
	eeprom->ops.update_checksum = ixgbe_update_eeprom_checksum_X550;
	eeprom->ops.validate_checksum = ixgbe_validate_eeprom_checksum_X550;
	eeprom->ops.calc_checksum = ixgbe_calc_eeprom_checksum_X550;

	return ret_val;
}