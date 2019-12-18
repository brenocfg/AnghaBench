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
typedef  int /*<<< orphan*/  u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_write_eewr_buffer_generic (struct ixgbe_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

s32 ixgbe_write_eewr_generic(struct ixgbe_hw *hw, u16 offset, u16 data)
{
	return ixgbe_write_eewr_buffer_generic(hw, offset, 1, &data);
}