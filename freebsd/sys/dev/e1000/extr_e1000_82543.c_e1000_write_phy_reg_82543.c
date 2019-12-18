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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int addr; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int /*<<< orphan*/  E1000_ERR_PARAM ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int MAX_PHY_REG_ADDRESS ; 
 int PHY_OP_WRITE ; 
 int PHY_PREAMBLE ; 
 int PHY_PREAMBLE_SIZE ; 
 int PHY_SOF ; 
 int PHY_TURNAROUND ; 
 int /*<<< orphan*/  e1000_shift_out_mdi_bits_82543 (struct e1000_hw*,int,int) ; 

__attribute__((used)) static s32 e1000_write_phy_reg_82543(struct e1000_hw *hw, u32 offset, u16 data)
{
	u32 mdic;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_write_phy_reg_82543");

	if (offset > MAX_PHY_REG_ADDRESS) {
		DEBUGOUT1("PHY Address %d is out of range\n", offset);
		ret_val = -E1000_ERR_PARAM;
		goto out;
	}

	/*
	 * We'll need to use the SW defined pins to shift the write command
	 * out to the PHY. We first send a preamble to the PHY to signal the
	 * beginning of the MII instruction.  This is done by sending 32
	 * consecutive "1" bits.
	 */
	e1000_shift_out_mdi_bits_82543(hw, PHY_PREAMBLE, PHY_PREAMBLE_SIZE);

	/*
	 * Now combine the remaining required fields that will indicate a
	 * write operation. We use this method instead of calling the
	 * e1000_shift_out_mdi_bits routine for each field in the command. The
	 * format of a MII write instruction is as follows:
	 * <Preamble><SOF><Op Code><Phy Addr><Reg Addr><Turnaround><Data>.
	 */
	mdic = ((PHY_TURNAROUND) | (offset << 2) | (hw->phy.addr << 7) |
		(PHY_OP_WRITE << 12) | (PHY_SOF << 14));
	mdic <<= 16;
	mdic |= (u32)data;

	e1000_shift_out_mdi_bits_82543(hw, mdic, 32);

out:
	return ret_val;
}