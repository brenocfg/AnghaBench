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
struct ixgbe_hw_stats {int dummy; } ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ixgbe_dcb_get_pfc_stats_82598 (struct ixgbe_hw*,struct ixgbe_hw_stats*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_dcb_get_pfc_stats_82599 (struct ixgbe_hw*,struct ixgbe_hw_stats*,int /*<<< orphan*/ ) ; 
#define  ixgbe_mac_82598EB 133 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 

s32 ixgbe_dcb_get_pfc_stats(struct ixgbe_hw *hw, struct ixgbe_hw_stats *stats,
			    u8 tc_count)
{
	s32 ret = IXGBE_NOT_IMPLEMENTED;
	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		ret = ixgbe_dcb_get_pfc_stats_82598(hw, stats, tc_count);
		break;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_X550EM_a:
#if !defined(NO_82599_SUPPORT) || !defined(NO_X540_SUPPORT)
		ret = ixgbe_dcb_get_pfc_stats_82599(hw, stats, tc_count);
		break;
#endif
	default:
		break;
	}
	return ret;
}