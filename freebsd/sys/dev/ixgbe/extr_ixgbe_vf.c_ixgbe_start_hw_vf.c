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
struct ixgbe_hw {int /*<<< orphan*/  adapter_stopped; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 

s32 ixgbe_start_hw_vf(struct ixgbe_hw *hw)
{
	/* Clear adapter stopped flag */
	hw->adapter_stopped = FALSE;

	return IXGBE_SUCCESS;
}