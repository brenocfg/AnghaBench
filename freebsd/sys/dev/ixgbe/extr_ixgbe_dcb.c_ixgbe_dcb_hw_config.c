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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_dcb_config_rx_arbiter_82598 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_rx_arbiter_82599 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tx_data_arbiter_82598 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tx_data_arbiter_82599 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tx_desc_arbiter_82598 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tx_desc_arbiter_82599 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  ixgbe_mac_82598EB 133 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 

s32 ixgbe_dcb_hw_config(struct ixgbe_hw *hw, u16 *refill, u16 *max,
			    u8 *bwg_id, u8 *tsa, u8 *map)
{
	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		ixgbe_dcb_config_rx_arbiter_82598(hw, refill, max, tsa);
		ixgbe_dcb_config_tx_desc_arbiter_82598(hw, refill, max, bwg_id,
						       tsa);
		ixgbe_dcb_config_tx_data_arbiter_82598(hw, refill, max, bwg_id,
						       tsa);
		break;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_X550EM_a:
#if !defined(NO_82599_SUPPORT) || !defined(NO_X540_SUPPORT)
		ixgbe_dcb_config_rx_arbiter_82599(hw, refill, max, bwg_id,
						  tsa, map);
		ixgbe_dcb_config_tx_desc_arbiter_82599(hw, refill, max, bwg_id,
						       tsa);
		ixgbe_dcb_config_tx_data_arbiter_82599(hw, refill, max, bwg_id,
						       tsa, map);
		break;
#endif
	default:
		break;
	}
	return 0;
}