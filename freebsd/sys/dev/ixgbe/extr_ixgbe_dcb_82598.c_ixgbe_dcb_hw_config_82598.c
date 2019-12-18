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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (int) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_rx_arbiter_82598 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tc_stats_82598 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tx_data_arbiter_82598 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_dcb_config_tx_desc_arbiter_82598 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

s32 ixgbe_dcb_hw_config_82598(struct ixgbe_hw *hw, int link_speed,
			      u16 *refill, u16 *max, u8 *bwg_id,
			      u8 *tsa)
{
	UNREFERENCED_1PARAMETER(link_speed);

	ixgbe_dcb_config_rx_arbiter_82598(hw, refill, max, tsa);
	ixgbe_dcb_config_tx_desc_arbiter_82598(hw, refill, max, bwg_id,
					       tsa);
	ixgbe_dcb_config_tx_data_arbiter_82598(hw, refill, max, bwg_id,
					       tsa);
	ixgbe_dcb_config_tc_stats_82598(hw);


	return IXGBE_SUCCESS;
}