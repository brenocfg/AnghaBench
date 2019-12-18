#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_3__ {TYPE_2__ ops; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA ; 
 int E1000_KMRNCTRLSTA_OFFSET ; 
 int E1000_KMRNCTRLSTA_OFFSET_SHIFT ; 
 int E1000_KMRNCTRLSTA_REN ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 __e1000_read_kmrn_reg(struct e1000_hw *hw, u32 offset, u16 *data,
				 bool locked)
{
	u32 kmrnctrlsta;

	DEBUGFUNC("__e1000_read_kmrn_reg");

	if (!locked) {
		s32 ret_val = E1000_SUCCESS;

		if (!hw->phy.ops.acquire)
			return E1000_SUCCESS;

		ret_val = hw->phy.ops.acquire(hw);
		if (ret_val)
			return ret_val;
	}

	kmrnctrlsta = ((offset << E1000_KMRNCTRLSTA_OFFSET_SHIFT) &
		       E1000_KMRNCTRLSTA_OFFSET) | E1000_KMRNCTRLSTA_REN;
	E1000_WRITE_REG(hw, E1000_KMRNCTRLSTA, kmrnctrlsta);
	E1000_WRITE_FLUSH(hw);

	usec_delay(2);

	kmrnctrlsta = E1000_READ_REG(hw, E1000_KMRNCTRLSTA);
	*data = (u16)kmrnctrlsta;

	if (!locked)
		hw->phy.ops.release(hw);

	return E1000_SUCCESS;
}