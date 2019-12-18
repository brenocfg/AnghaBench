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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {int original_ms_type; int ms_type; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int CR_1000T_MS_ENABLE ; 
 int CR_1000T_MS_VALUE ; 
 int /*<<< orphan*/  PHY_1000T_CTRL ; 
#define  e1000_ms_auto 130 
#define  e1000_ms_force_master 129 
#define  e1000_ms_force_slave 128 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_set_master_slave_mode(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 phy_data;

	/* Resolve Master/Slave mode */
	ret_val = hw->phy.ops.read_reg(hw, PHY_1000T_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	/* load defaults for future use */
	hw->phy.original_ms_type = (phy_data & CR_1000T_MS_ENABLE) ?
				   ((phy_data & CR_1000T_MS_VALUE) ?
				    e1000_ms_force_master :
				    e1000_ms_force_slave) : e1000_ms_auto;

	switch (hw->phy.ms_type) {
	case e1000_ms_force_master:
		phy_data |= (CR_1000T_MS_ENABLE | CR_1000T_MS_VALUE);
		break;
	case e1000_ms_force_slave:
		phy_data |= CR_1000T_MS_ENABLE;
		phy_data &= ~(CR_1000T_MS_VALUE);
		break;
	case e1000_ms_auto:
		phy_data &= ~CR_1000T_MS_ENABLE;
		/* fall-through */
	default:
		break;
	}

	return hw->phy.ops.write_reg(hw, PHY_1000T_CTRL, phy_data);
}