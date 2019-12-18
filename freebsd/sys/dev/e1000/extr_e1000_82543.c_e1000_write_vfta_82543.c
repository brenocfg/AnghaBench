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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int E1000_READ_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E1000_VFTA ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ e1000_82544 ; 
 int /*<<< orphan*/  e1000_write_vfta_generic (struct e1000_hw*,int,int) ; 

__attribute__((used)) static void e1000_write_vfta_82543(struct e1000_hw *hw, u32 offset, u32 value)
{
	u32 temp;

	DEBUGFUNC("e1000_write_vfta_82543");

	if ((hw->mac.type == e1000_82544) && (offset & 1)) {
		temp = E1000_READ_REG_ARRAY(hw, E1000_VFTA, offset - 1);
		E1000_WRITE_REG_ARRAY(hw, E1000_VFTA, offset, value);
		E1000_WRITE_FLUSH(hw);
		E1000_WRITE_REG_ARRAY(hw, E1000_VFTA, offset - 1, temp);
		E1000_WRITE_FLUSH(hw);
	} else {
		e1000_write_vfta_generic(hw, offset, value);
	}
}