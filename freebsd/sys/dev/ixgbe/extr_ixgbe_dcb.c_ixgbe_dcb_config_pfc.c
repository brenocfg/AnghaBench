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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int s32 ;

/* Variables and functions */
 int IXGBE_ERR_PARAM ; 
 int ixgbe_dcb_config_pfc_82598 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int ixgbe_dcb_config_pfc_82599 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  ixgbe_mac_82598EB 133 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 

s32 ixgbe_dcb_config_pfc(struct ixgbe_hw *hw, u8 pfc_en, u8 *map)
{
	int ret = IXGBE_ERR_PARAM;

	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		ret = ixgbe_dcb_config_pfc_82598(hw, pfc_en);
		break;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_X550EM_a:
#if !defined(NO_82599_SUPPORT) || !defined(NO_X540_SUPPORT)
		ret = ixgbe_dcb_config_pfc_82599(hw, pfc_en, map);
		break;
#endif
	default:
		break;
	}
	return ret;
}