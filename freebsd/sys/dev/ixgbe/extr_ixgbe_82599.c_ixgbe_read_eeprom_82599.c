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
typedef  scalar_t__ u16 ;
struct ixgbe_eeprom_info {scalar_t__ type; } ;
struct ixgbe_hw {struct ixgbe_eeprom_info eeprom; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ IXGBE_EERD_MAX_ADDR ; 
 int /*<<< orphan*/  IXGBE_ERR_CONFIG ; 
 scalar_t__ ixgbe_eeprom_spi ; 
 int /*<<< orphan*/  ixgbe_read_eeprom_bit_bang_generic (struct ixgbe_hw*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ixgbe_read_eerd_generic (struct ixgbe_hw*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static s32 ixgbe_read_eeprom_82599(struct ixgbe_hw *hw,
				   u16 offset, u16 *data)
{
	struct ixgbe_eeprom_info *eeprom = &hw->eeprom;
	s32 ret_val = IXGBE_ERR_CONFIG;

	DEBUGFUNC("ixgbe_read_eeprom_82599");

	/*
	 * If EEPROM is detected and can be addressed using 14 bits,
	 * use EERD otherwise use bit bang
	 */
	if ((eeprom->type == ixgbe_eeprom_spi) &&
	    (offset <= IXGBE_EERD_MAX_ADDR))
		ret_val = ixgbe_read_eerd_generic(hw, offset, data);
	else
		ret_val = ixgbe_read_eeprom_bit_bang_generic(hw, offset, data);

	return ret_val;
}