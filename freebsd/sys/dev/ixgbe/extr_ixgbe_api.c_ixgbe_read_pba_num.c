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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_read_pba_num_generic (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 

s32 ixgbe_read_pba_num(struct ixgbe_hw *hw, u32 *pba_num)
{
	return ixgbe_read_pba_num_generic(hw, pba_num);
}