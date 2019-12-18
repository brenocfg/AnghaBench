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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_phy_info {int addr; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 int /*<<< orphan*/  E1000_ERR_PHY ; 
 int /*<<< orphan*/  E1000_I2CCMD ; 
 int E1000_I2CCMD_ERROR ; 
 int E1000_I2CCMD_OPCODE_WRITE ; 
 int E1000_I2CCMD_PHY_ADDR_SHIFT ; 
 int E1000_I2CCMD_PHY_TIMEOUT ; 
 int E1000_I2CCMD_READY ; 
 int E1000_I2CCMD_REG_ADDR_SHIFT ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 e1000_write_phy_reg_i2c(struct e1000_hw *hw, u32 offset, u16 data)
{
	struct e1000_phy_info *phy = &hw->phy;
	u32 i, i2ccmd = 0;
	u16 phy_data_swapped;

	DEBUGFUNC("e1000_write_phy_reg_i2c");

	/* Prevent overwritting SFP I2C EEPROM which is at A0 address.*/
	if ((hw->phy.addr == 0) || (hw->phy.addr > 7)) {
		DEBUGOUT1("PHY I2C Address %d is out of range.\n",
			  hw->phy.addr);
		return -E1000_ERR_CONFIG;
	}

	/* Swap the data bytes for the I2C interface */
	phy_data_swapped = ((data >> 8) & 0x00FF) | ((data << 8) & 0xFF00);

	/* Set up Op-code, Phy Address, and register address in the I2CCMD
	 * register.  The MAC will take care of interfacing with the
	 * PHY to retrieve the desired data.
	 */
	i2ccmd = ((offset << E1000_I2CCMD_REG_ADDR_SHIFT) |
		  (phy->addr << E1000_I2CCMD_PHY_ADDR_SHIFT) |
		  E1000_I2CCMD_OPCODE_WRITE |
		  phy_data_swapped);

	E1000_WRITE_REG(hw, E1000_I2CCMD, i2ccmd);

	/* Poll the ready bit to see if the I2C read completed */
	for (i = 0; i < E1000_I2CCMD_PHY_TIMEOUT; i++) {
		usec_delay(50);
		i2ccmd = E1000_READ_REG(hw, E1000_I2CCMD);
		if (i2ccmd & E1000_I2CCMD_READY)
			break;
	}
	if (!(i2ccmd & E1000_I2CCMD_READY)) {
		DEBUGOUT("I2CCMD Write did not complete\n");
		return -E1000_ERR_PHY;
	}
	if (i2ccmd & E1000_I2CCMD_ERROR) {
		DEBUGOUT("I2CCMD Error bit set\n");
		return -E1000_ERR_PHY;
	}

	return E1000_SUCCESS;
}