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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int addr; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int /*<<< orphan*/  E1000_ERR_PARAM ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int MAX_PHY_REG_ADDRESS ; 
 int PHY_OP_READ ; 
 int PHY_PREAMBLE ; 
 int PHY_PREAMBLE_SIZE ; 
 int PHY_SOF ; 
 int /*<<< orphan*/  e1000_shift_in_mdi_bits_82543 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_shift_out_mdi_bits_82543 (struct e1000_hw*,int,int) ; 

__attribute__((used)) static s32 e1000_read_phy_reg_82543(struct e1000_hw *hw, u32 offset, u16 *data)
{
	u32 mdic;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_read_phy_reg_82543");

	if (offset > MAX_PHY_REG_ADDRESS) {
		DEBUGOUT1("PHY Address %d is out of range\n", offset);
		ret_val = -E1000_ERR_PARAM;
		goto out;
	}

	/*
	 * We must first send a preamble through the MDIO pin to signal the
	 * beginning of an MII instruction.  This is done by sending 32
	 * consecutive "1" bits.
	 */
	e1000_shift_out_mdi_bits_82543(hw, PHY_PREAMBLE, PHY_PREAMBLE_SIZE);

	/*
	 * Now combine the next few fields that are required for a read
	 * operation.  We use this method instead of calling the
	 * e1000_shift_out_mdi_bits routine five different times.  The format
	 * of an MII read instruction consists of a shift out of 14 bits and
	 * is defined as follows:
	 *         <Preamble><SOF><Op Code><Phy Addr><Offset>
	 * followed by a shift in of 18 bits.  This first two bits shifted in
	 * are TurnAround bits used to avoid contention on the MDIO pin when a
	 * READ operation is performed.  These two bits are thrown away
	 * followed by a shift in of 16 bits which contains the desired data.
	 */
	mdic = (offset | (hw->phy.addr << 5) |
		(PHY_OP_READ << 10) | (PHY_SOF << 12));

	e1000_shift_out_mdi_bits_82543(hw, mdic, 14);

	/*
	 * Now that we've shifted out the read command to the MII, we need to
	 * "shift in" the 16-bit value (18 total bits) of the requested PHY
	 * register address.
	 */
	*data = e1000_shift_in_mdi_bits_82543(hw);

out:
	return ret_val;
}