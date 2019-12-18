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
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_VF_MAX_TX_QUEUES ; 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (struct ixgbe_hw*) ; 

u32 ixgbe_get_num_of_tx_queues_vf(struct ixgbe_hw *hw)
{
	UNREFERENCED_1PARAMETER(hw);
	return IXGBE_VF_MAX_TX_QUEUES;
}