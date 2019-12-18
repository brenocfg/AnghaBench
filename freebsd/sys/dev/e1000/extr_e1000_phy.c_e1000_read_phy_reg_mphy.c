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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_ERR_PHY ; 
 int E1000_MPHY_ADDRESS_FNC_OVERRIDE ; 
 int E1000_MPHY_ADDRESS_MASK ; 
 int /*<<< orphan*/  E1000_MPHY_ADDR_CTRL ; 
 int /*<<< orphan*/  E1000_MPHY_DATA ; 
 int E1000_MPHY_DIS_ACCESS ; 
 int E1000_MPHY_ENA_ACCESS ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 int TRUE ; 
 int e1000_is_mphy_ready (struct e1000_hw*) ; 

s32 e1000_read_phy_reg_mphy(struct e1000_hw *hw, u32 address, u32 *data)
{
	u32 mphy_ctrl = 0;
	bool locked = FALSE;
	bool ready;

	DEBUGFUNC("e1000_read_phy_reg_mphy");

	/* Check if mPHY is ready to read/write operations */
	ready = e1000_is_mphy_ready(hw);
	if (!ready)
		return -E1000_ERR_PHY;

	/* Check if mPHY access is disabled and enable it if so */
	mphy_ctrl = E1000_READ_REG(hw, E1000_MPHY_ADDR_CTRL);
	if (mphy_ctrl & E1000_MPHY_DIS_ACCESS) {
		locked = TRUE;
		ready = e1000_is_mphy_ready(hw);
		if (!ready)
			return -E1000_ERR_PHY;
		mphy_ctrl |= E1000_MPHY_ENA_ACCESS;
		E1000_WRITE_REG(hw, E1000_MPHY_ADDR_CTRL, mphy_ctrl);
	}

	/* Set the address that we want to read */
	ready = e1000_is_mphy_ready(hw);
	if (!ready)
		return -E1000_ERR_PHY;

	/* We mask address, because we want to use only current lane */
	mphy_ctrl = (mphy_ctrl & ~E1000_MPHY_ADDRESS_MASK &
		~E1000_MPHY_ADDRESS_FNC_OVERRIDE) |
		(address & E1000_MPHY_ADDRESS_MASK);
	E1000_WRITE_REG(hw, E1000_MPHY_ADDR_CTRL, mphy_ctrl);

	/* Read data from the address */
	ready = e1000_is_mphy_ready(hw);
	if (!ready)
		return -E1000_ERR_PHY;
	*data = E1000_READ_REG(hw, E1000_MPHY_DATA);

	/* Disable access to mPHY if it was originally disabled */
	if (locked)
		ready = e1000_is_mphy_ready(hw);
	if (!ready)
		return -E1000_ERR_PHY;
	E1000_WRITE_REG(hw, E1000_MPHY_ADDR_CTRL,
			E1000_MPHY_DIS_ACCESS);

	return E1000_SUCCESS;
}