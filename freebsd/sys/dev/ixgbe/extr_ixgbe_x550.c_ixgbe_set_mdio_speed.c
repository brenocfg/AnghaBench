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
typedef  int /*<<< orphan*/  u32 ;
struct ixgbe_hw {int device_id; } ;

/* Variables and functions */
#define  IXGBE_DEV_ID_X550EM_A_10G_T 135 
#define  IXGBE_DEV_ID_X550EM_A_1G_T 134 
#define  IXGBE_DEV_ID_X550EM_A_1G_T_L 133 
#define  IXGBE_DEV_ID_X550EM_A_QSFP 132 
#define  IXGBE_DEV_ID_X550EM_A_SFP 131 
#define  IXGBE_DEV_ID_X550EM_A_SGMII 130 
#define  IXGBE_DEV_ID_X550EM_A_SGMII_L 129 
#define  IXGBE_DEV_ID_X550EM_X_10G_T 128 
 int /*<<< orphan*/  IXGBE_HLREG0 ; 
 int /*<<< orphan*/  IXGBE_HLREG0_MDCSPD ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_set_mdio_speed(struct ixgbe_hw *hw)
{
	u32 hlreg0;

	switch (hw->device_id) {
	case IXGBE_DEV_ID_X550EM_X_10G_T:
	case IXGBE_DEV_ID_X550EM_A_SGMII:
	case IXGBE_DEV_ID_X550EM_A_SGMII_L:
	case IXGBE_DEV_ID_X550EM_A_10G_T:
	case IXGBE_DEV_ID_X550EM_A_SFP:
	case IXGBE_DEV_ID_X550EM_A_QSFP:
		/* Config MDIO clock speed before the first MDIO PHY access */
		hlreg0 = IXGBE_READ_REG(hw, IXGBE_HLREG0);
		hlreg0 &= ~IXGBE_HLREG0_MDCSPD;
		IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0);
		break;
	case IXGBE_DEV_ID_X550EM_A_1G_T:
	case IXGBE_DEV_ID_X550EM_A_1G_T_L:
		/* Select fast MDIO clock speed for these devices */
		hlreg0 = IXGBE_READ_REG(hw, IXGBE_HLREG0);
		hlreg0 |= IXGBE_HLREG0_MDCSPD;
		IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0);
		break;
	default:
		break;
	}
}