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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ (* read_posted ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* write_posted ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct ixgbe_mbx_info {TYPE_1__ ops; } ;
struct ixgbe_hw {struct ixgbe_mbx_info mbx; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbevf_write_msg_read_ack(struct ixgbe_hw *hw, u32 *msg,
				      u32 *retmsg, u16 size)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;
	s32 retval = mbx->ops.write_posted(hw, msg, size, 0);

	if (retval)
		return retval;

	return mbx->ops.read_posted(hw, retmsg, size, 0);
}