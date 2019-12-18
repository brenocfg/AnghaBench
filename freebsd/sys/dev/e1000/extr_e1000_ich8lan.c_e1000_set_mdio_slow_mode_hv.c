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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  HV_KMRN_MDIO_SLOW ; 
 int /*<<< orphan*/  HV_KMRN_MODE_CTRL ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_set_mdio_slow_mode_hv(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 data;

	DEBUGFUNC("e1000_set_mdio_slow_mode_hv");

	ret_val = hw->phy.ops.read_reg(hw, HV_KMRN_MODE_CTRL, &data);
	if (ret_val)
		return ret_val;

	data |= HV_KMRN_MDIO_SLOW;

	ret_val = hw->phy.ops.write_reg(hw, HV_KMRN_MODE_CTRL, data);

	return ret_val;
}