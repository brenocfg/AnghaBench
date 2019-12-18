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
struct ixgbe_hw {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_clock_in_i2c_bit (struct ixgbe_hw*,int*) ; 

__attribute__((used)) static s32 ixgbe_clock_in_i2c_byte(struct ixgbe_hw *hw, u8 *data)
{
	s32 i;
	bool bit = 0;

	DEBUGFUNC("ixgbe_clock_in_i2c_byte");

	*data = 0;
	for (i = 7; i >= 0; i--) {
		ixgbe_clock_in_i2c_bit(hw, &bit);
		*data |= bit << i;
	}

	return IXGBE_SUCCESS;
}