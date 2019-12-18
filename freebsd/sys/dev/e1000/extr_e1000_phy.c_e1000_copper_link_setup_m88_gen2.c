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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ (* commit ) (struct e1000_hw*) ;scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct e1000_phy_info {int mdix; scalar_t__ id; TYPE_1__ ops; scalar_t__ disable_polarity_correction; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  I347AT4_PSCR_DOWNSHIFT_6X ; 
 int /*<<< orphan*/  I347AT4_PSCR_DOWNSHIFT_ENABLE ; 
 int /*<<< orphan*/  I347AT4_PSCR_DOWNSHIFT_MASK ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  M88E1000_PSCR_AUTO_X_1000T ; 
 int /*<<< orphan*/  M88E1000_PSCR_AUTO_X_MODE ; 
 int /*<<< orphan*/  M88E1000_PSCR_MDIX_MANUAL_MODE ; 
 int /*<<< orphan*/  M88E1000_PSCR_MDI_MANUAL_MODE ; 
 int /*<<< orphan*/  M88E1000_PSCR_POLARITY_REVERSAL ; 
 scalar_t__ M88E1112_E_PHY_ID ; 
 scalar_t__ M88E1543_E_PHY_ID ; 
 scalar_t__ e1000_set_master_slave_mode (struct e1000_hw*) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct e1000_hw*) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (struct e1000_hw*) ; 

s32 e1000_copper_link_setup_m88_gen2(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;

	DEBUGFUNC("e1000_copper_link_setup_m88_gen2");


	/* Enable CRS on Tx. This must be set for half-duplex operation. */
	ret_val = phy->ops.read_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	/* Options:
	 *   MDI/MDI-X = 0 (default)
	 *   0 - Auto for all speeds
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 *   3 - Auto for 1000Base-T only (MDI-X for 10/100Base-T modes)
	 */
	phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;

	switch (phy->mdix) {
	case 1:
		phy_data |= M88E1000_PSCR_MDI_MANUAL_MODE;
		break;
	case 2:
		phy_data |= M88E1000_PSCR_MDIX_MANUAL_MODE;
		break;
	case 3:
		/* M88E1112 does not support this mode) */
		if (phy->id != M88E1112_E_PHY_ID) {
			phy_data |= M88E1000_PSCR_AUTO_X_1000T;
			break;
		}
		/* FALLTHROUGH */
	case 0:
	default:
		phy_data |= M88E1000_PSCR_AUTO_X_MODE;
		break;
	}

	/* Options:
	 *   disable_polarity_correction = 0 (default)
	 *       Automatic Correction for Reversed Cable Polarity
	 *   0 - Disabled
	 *   1 - Enabled
	 */
	phy_data &= ~M88E1000_PSCR_POLARITY_REVERSAL;
	if (phy->disable_polarity_correction)
		phy_data |= M88E1000_PSCR_POLARITY_REVERSAL;

	/* Enable downshift and setting it to X6 */
	if (phy->id == M88E1543_E_PHY_ID) {
		phy_data &= ~I347AT4_PSCR_DOWNSHIFT_ENABLE;
		ret_val =
		    phy->ops.write_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
		if (ret_val)
			return ret_val;

		ret_val = phy->ops.commit(hw);
		if (ret_val) {
			DEBUGOUT("Error committing the PHY changes\n");
			return ret_val;
		}
	}

	phy_data &= ~I347AT4_PSCR_DOWNSHIFT_MASK;
	phy_data |= I347AT4_PSCR_DOWNSHIFT_6X;
	phy_data |= I347AT4_PSCR_DOWNSHIFT_ENABLE;

	ret_val = phy->ops.write_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
	if (ret_val)
		return ret_val;

	/* Commit the changes. */
	ret_val = phy->ops.commit(hw);
	if (ret_val) {
		DEBUGOUT("Error committing the PHY changes\n");
		return ret_val;
	}

	ret_val = e1000_set_master_slave_mode(hw);
	if (ret_val)
		return ret_val;

	return E1000_SUCCESS;
}