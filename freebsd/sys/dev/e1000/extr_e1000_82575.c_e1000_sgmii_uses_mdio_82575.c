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
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_MDIC ; 
 int /*<<< orphan*/  E1000_MDICNFG ; 
 int E1000_MDICNFG_EXT_MDIO ; 
 int E1000_MDIC_DEST ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int FALSE ; 
#define  e1000_82575 134 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 

__attribute__((used)) static bool e1000_sgmii_uses_mdio_82575(struct e1000_hw *hw)
{
	u32 reg = 0;
	bool ext_mdio = FALSE;

	DEBUGFUNC("e1000_sgmii_uses_mdio_82575");

	switch (hw->mac.type) {
	case e1000_82575:
	case e1000_82576:
		reg = E1000_READ_REG(hw, E1000_MDIC);
		ext_mdio = !!(reg & E1000_MDIC_DEST);
		break;
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
	case e1000_i210:
	case e1000_i211:
		reg = E1000_READ_REG(hw, E1000_MDICNFG);
		ext_mdio = !!(reg & E1000_MDICNFG_EXT_MDIO);
		break;
	default:
		break;
	}
	return ext_mdio;
}