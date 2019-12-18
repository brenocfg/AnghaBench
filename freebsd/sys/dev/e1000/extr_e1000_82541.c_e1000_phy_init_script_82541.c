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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_7__ {int /*<<< orphan*/  (* write_reg ) (struct e1000_hw*,int,int) ;int /*<<< orphan*/  (* read_reg ) (struct e1000_hw*,int,int*) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_6__ {int type; } ;
struct e1000_dev_spec_82541 {int /*<<< orphan*/  phy_init_script; } ;
struct TYPE_5__ {struct e1000_dev_spec_82541 _82541; } ;
struct e1000_hw {TYPE_4__ phy; TYPE_2__ mac; TYPE_1__ dev_spec; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int IGP01E1000_ANALOG_FUSE_BYPASS ; 
 scalar_t__ IGP01E1000_ANALOG_FUSE_COARSE_10 ; 
 int IGP01E1000_ANALOG_FUSE_COARSE_MASK ; 
 int IGP01E1000_ANALOG_FUSE_COARSE_THRESH ; 
 int IGP01E1000_ANALOG_FUSE_CONTROL ; 
 int IGP01E1000_ANALOG_FUSE_ENABLE_SW_CONTROL ; 
 scalar_t__ IGP01E1000_ANALOG_FUSE_FINE_1 ; 
 scalar_t__ IGP01E1000_ANALOG_FUSE_FINE_10 ; 
 int IGP01E1000_ANALOG_FUSE_FINE_MASK ; 
 int IGP01E1000_ANALOG_FUSE_POLY_MASK ; 
 int IGP01E1000_ANALOG_FUSE_STATUS ; 
 int IGP01E1000_ANALOG_SPARE_FUSE_ENABLED ; 
 int IGP01E1000_ANALOG_SPARE_FUSE_STATUS ; 
#define  e1000_82541 131 
#define  e1000_82541_rev_2 130 
#define  e1000_82547 129 
#define  e1000_82547_rev_2 128 
 int /*<<< orphan*/  msec_delay (int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int,int*) ; 
 int /*<<< orphan*/  stub10 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub11 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub12 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub13 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub14 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub15 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub16 (struct e1000_hw*,int,int*) ; 
 int /*<<< orphan*/  stub17 (struct e1000_hw*,int,int*) ; 
 int /*<<< orphan*/  stub18 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub19 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub6 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub7 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub8 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub9 (struct e1000_hw*,int,int) ; 

__attribute__((used)) static s32 e1000_phy_init_script_82541(struct e1000_hw *hw)
{
	struct e1000_dev_spec_82541 *dev_spec = &hw->dev_spec._82541;
	u32 ret_val;
	u16 phy_saved_data;

	DEBUGFUNC("e1000_phy_init_script_82541");

	if (!dev_spec->phy_init_script) {
		ret_val = E1000_SUCCESS;
		goto out;
	}

	/* Delay after phy reset to enable NVM configuration to load */
	msec_delay(20);

	/*
	 * Save off the current value of register 0x2F5B to be restored at
	 * the end of this routine.
	 */
	ret_val = hw->phy.ops.read_reg(hw, 0x2F5B, &phy_saved_data);

	/* Disabled the PHY transmitter */
	hw->phy.ops.write_reg(hw, 0x2F5B, 0x0003);

	msec_delay(20);

	hw->phy.ops.write_reg(hw, 0x0000, 0x0140);

	msec_delay(5);

	switch (hw->mac.type) {
	case e1000_82541:
	case e1000_82547:
		hw->phy.ops.write_reg(hw, 0x1F95, 0x0001);

		hw->phy.ops.write_reg(hw, 0x1F71, 0xBD21);

		hw->phy.ops.write_reg(hw, 0x1F79, 0x0018);

		hw->phy.ops.write_reg(hw, 0x1F30, 0x1600);

		hw->phy.ops.write_reg(hw, 0x1F31, 0x0014);

		hw->phy.ops.write_reg(hw, 0x1F32, 0x161C);

		hw->phy.ops.write_reg(hw, 0x1F94, 0x0003);

		hw->phy.ops.write_reg(hw, 0x1F96, 0x003F);

		hw->phy.ops.write_reg(hw, 0x2010, 0x0008);
		break;
	case e1000_82541_rev_2:
	case e1000_82547_rev_2:
		hw->phy.ops.write_reg(hw, 0x1F73, 0x0099);
		break;
	default:
		break;
	}

	hw->phy.ops.write_reg(hw, 0x0000, 0x3300);

	msec_delay(20);

	/* Now enable the transmitter */
	hw->phy.ops.write_reg(hw, 0x2F5B, phy_saved_data);

	if (hw->mac.type == e1000_82547) {
		u16 fused, fine, coarse;

		/* Move to analog registers page */
		hw->phy.ops.read_reg(hw, IGP01E1000_ANALOG_SPARE_FUSE_STATUS,
				     &fused);

		if (!(fused & IGP01E1000_ANALOG_SPARE_FUSE_ENABLED)) {
			hw->phy.ops.read_reg(hw, IGP01E1000_ANALOG_FUSE_STATUS,
					     &fused);

			fine = fused & IGP01E1000_ANALOG_FUSE_FINE_MASK;
			coarse = fused & IGP01E1000_ANALOG_FUSE_COARSE_MASK;

			if (coarse > IGP01E1000_ANALOG_FUSE_COARSE_THRESH) {
				coarse -= IGP01E1000_ANALOG_FUSE_COARSE_10;
				fine -= IGP01E1000_ANALOG_FUSE_FINE_1;
			} else if (coarse ==
				   IGP01E1000_ANALOG_FUSE_COARSE_THRESH)
				fine -= IGP01E1000_ANALOG_FUSE_FINE_10;

			fused = (fused & IGP01E1000_ANALOG_FUSE_POLY_MASK) |
				(fine & IGP01E1000_ANALOG_FUSE_FINE_MASK) |
				(coarse & IGP01E1000_ANALOG_FUSE_COARSE_MASK);

			hw->phy.ops.write_reg(hw,
					      IGP01E1000_ANALOG_FUSE_CONTROL,
					      fused);
			hw->phy.ops.write_reg(hw,
				      IGP01E1000_ANALOG_FUSE_BYPASS,
				      IGP01E1000_ANALOG_FUSE_ENABLE_SW_CONTROL);
		}
	}

out:
	return ret_val;
}