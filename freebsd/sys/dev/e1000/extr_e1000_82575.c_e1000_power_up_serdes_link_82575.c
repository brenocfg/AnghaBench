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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int /*<<< orphan*/  E1000_CTRL_EXT_SDP3_DATA ; 
 int /*<<< orphan*/  E1000_PCS_CFG0 ; 
 int /*<<< orphan*/  E1000_PCS_CFG_PCS_EN ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  e1000_sgmii_active_82575 (struct e1000_hw*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

__attribute__((used)) static void e1000_power_up_serdes_link_82575(struct e1000_hw *hw)
{
	u32 reg;

	DEBUGFUNC("e1000_power_up_serdes_link_82575");

	if ((hw->phy.media_type != e1000_media_type_internal_serdes) &&
	    !e1000_sgmii_active_82575(hw))
		return;

	/* Enable PCS to turn on link */
	reg = E1000_READ_REG(hw, E1000_PCS_CFG0);
	reg |= E1000_PCS_CFG_PCS_EN;
	E1000_WRITE_REG(hw, E1000_PCS_CFG0, reg);

	/* Power up the laser */
	reg = E1000_READ_REG(hw, E1000_CTRL_EXT);
	reg &= ~E1000_CTRL_EXT_SDP3_DATA;
	E1000_WRITE_REG(hw, E1000_CTRL_EXT, reg);

	/* flush the write to verify completion */
	E1000_WRITE_FLUSH(hw);
	msec_delay(1);
}