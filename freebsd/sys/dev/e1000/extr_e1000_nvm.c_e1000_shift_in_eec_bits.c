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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_EECD ; 
 scalar_t__ E1000_EECD_DI ; 
 scalar_t__ E1000_EECD_DO ; 
 scalar_t__ E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_lower_eec_clk (struct e1000_hw*,scalar_t__*) ; 
 int /*<<< orphan*/  e1000_raise_eec_clk (struct e1000_hw*,scalar_t__*) ; 

__attribute__((used)) static u16 e1000_shift_in_eec_bits(struct e1000_hw *hw, u16 count)
{
	u32 eecd;
	u32 i;
	u16 data;

	DEBUGFUNC("e1000_shift_in_eec_bits");

	eecd = E1000_READ_REG(hw, E1000_EECD);

	eecd &= ~(E1000_EECD_DO | E1000_EECD_DI);
	data = 0;

	for (i = 0; i < count; i++) {
		data <<= 1;
		e1000_raise_eec_clk(hw, &eecd);

		eecd = E1000_READ_REG(hw, E1000_EECD);

		eecd &= ~E1000_EECD_DI;
		if (eecd & E1000_EECD_DO)
			data |= 1;

		e1000_lower_eec_clk(hw, &eecd);
	}

	return data;
}