#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  check_overtemp; int /*<<< orphan*/  write_i2c_byte_unlocked; int /*<<< orphan*/  read_i2c_byte_unlocked; int /*<<< orphan*/  identify_sfp; int /*<<< orphan*/  i2c_bus_clear; int /*<<< orphan*/  write_i2c_eeprom; int /*<<< orphan*/  read_i2c_eeprom; int /*<<< orphan*/  read_i2c_sff8472; int /*<<< orphan*/  write_i2c_byte; int /*<<< orphan*/  read_i2c_byte; int /*<<< orphan*/  get_firmware_version; int /*<<< orphan*/ * check_link; int /*<<< orphan*/  setup_link_speed; int /*<<< orphan*/  setup_link; int /*<<< orphan*/  write_reg_mdi; int /*<<< orphan*/  read_reg_mdi; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; int /*<<< orphan*/  reset; int /*<<< orphan*/  identify; } ;
struct ixgbe_phy_info {TYPE_1__ ops; int /*<<< orphan*/  sfp_type; } ;
struct ixgbe_hw {struct ixgbe_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_get_phy_firmware_version_generic ; 
 int /*<<< orphan*/  ixgbe_i2c_bus_clear ; 
 int /*<<< orphan*/  ixgbe_identify_module_generic ; 
 int /*<<< orphan*/  ixgbe_identify_phy_generic ; 
 int /*<<< orphan*/  ixgbe_read_i2c_byte_generic ; 
 int /*<<< orphan*/  ixgbe_read_i2c_byte_generic_unlocked ; 
 int /*<<< orphan*/  ixgbe_read_i2c_eeprom_generic ; 
 int /*<<< orphan*/  ixgbe_read_i2c_sff8472_generic ; 
 int /*<<< orphan*/  ixgbe_read_phy_reg_generic ; 
 int /*<<< orphan*/  ixgbe_read_phy_reg_mdi ; 
 int /*<<< orphan*/  ixgbe_reset_phy_generic ; 
 int /*<<< orphan*/  ixgbe_setup_phy_link_generic ; 
 int /*<<< orphan*/  ixgbe_setup_phy_link_speed_generic ; 
 int /*<<< orphan*/  ixgbe_sfp_type_unknown ; 
 int /*<<< orphan*/  ixgbe_tn_check_overtemp ; 
 int /*<<< orphan*/  ixgbe_write_i2c_byte_generic ; 
 int /*<<< orphan*/  ixgbe_write_i2c_byte_generic_unlocked ; 
 int /*<<< orphan*/  ixgbe_write_i2c_eeprom_generic ; 
 int /*<<< orphan*/  ixgbe_write_phy_reg_generic ; 
 int /*<<< orphan*/  ixgbe_write_phy_reg_mdi ; 

s32 ixgbe_init_phy_ops_generic(struct ixgbe_hw *hw)
{
	struct ixgbe_phy_info *phy = &hw->phy;

	DEBUGFUNC("ixgbe_init_phy_ops_generic");

	/* PHY */
	phy->ops.identify = ixgbe_identify_phy_generic;
	phy->ops.reset = ixgbe_reset_phy_generic;
	phy->ops.read_reg = ixgbe_read_phy_reg_generic;
	phy->ops.write_reg = ixgbe_write_phy_reg_generic;
	phy->ops.read_reg_mdi = ixgbe_read_phy_reg_mdi;
	phy->ops.write_reg_mdi = ixgbe_write_phy_reg_mdi;
	phy->ops.setup_link = ixgbe_setup_phy_link_generic;
	phy->ops.setup_link_speed = ixgbe_setup_phy_link_speed_generic;
	phy->ops.check_link = NULL;
	phy->ops.get_firmware_version = ixgbe_get_phy_firmware_version_generic;
	phy->ops.read_i2c_byte = ixgbe_read_i2c_byte_generic;
	phy->ops.write_i2c_byte = ixgbe_write_i2c_byte_generic;
	phy->ops.read_i2c_sff8472 = ixgbe_read_i2c_sff8472_generic;
	phy->ops.read_i2c_eeprom = ixgbe_read_i2c_eeprom_generic;
	phy->ops.write_i2c_eeprom = ixgbe_write_i2c_eeprom_generic;
	phy->ops.i2c_bus_clear = ixgbe_i2c_bus_clear;
	phy->ops.identify_sfp = ixgbe_identify_module_generic;
	phy->sfp_type = ixgbe_sfp_type_unknown;
	phy->ops.read_i2c_byte_unlocked = ixgbe_read_i2c_byte_generic_unlocked;
	phy->ops.write_i2c_byte_unlocked =
				ixgbe_write_i2c_byte_generic_unlocked;
	phy->ops.check_overtemp = ixgbe_tn_check_overtemp;
	return IXGBE_SUCCESS;
}