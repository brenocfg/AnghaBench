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
typedef  int u8 ;
struct ixgbe_hw_stats {int /*<<< orphan*/ * pxoffrxc; int /*<<< orphan*/ * pxofftxc; } ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int IXGBE_DCB_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  IXGBE_ERR_PARAM ; 
 int /*<<< orphan*/  IXGBE_PXOFFRXC (int) ; 
 int /*<<< orphan*/  IXGBE_PXOFFTXC (int) ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 

s32 ixgbe_dcb_get_pfc_stats_82598(struct ixgbe_hw *hw,
				  struct ixgbe_hw_stats *stats,
				  u8 tc_count)
{
	int tc;

	DEBUGFUNC("dcb_get_pfc_stats");

	if (tc_count > IXGBE_DCB_MAX_TRAFFIC_CLASS)
		return IXGBE_ERR_PARAM;

	for (tc = 0; tc < tc_count; tc++) {
		/* Priority XOFF Transmitted */
		stats->pxofftxc[tc] += IXGBE_READ_REG(hw, IXGBE_PXOFFTXC(tc));
		/* Priority XOFF Received */
		stats->pxoffrxc[tc] += IXGBE_READ_REG(hw, IXGBE_PXOFFRXC(tc));
	}

	return IXGBE_SUCCESS;
}