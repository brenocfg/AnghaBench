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
struct e1000_hw {TYPE_1__ nvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_CS ; 
 int E1000_EECD_DI ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e1000_lower_eec_clk (struct e1000_hw*,int*) ; 
 scalar_t__ e1000_nvm_eeprom_microwire ; 
 scalar_t__ e1000_nvm_eeprom_spi ; 
 int /*<<< orphan*/  e1000_raise_eec_clk (struct e1000_hw*,int*) ; 

void e1000_stop_nvm(struct e1000_hw *hw)
{
	u32 eecd;

	DEBUGFUNC("e1000_stop_nvm");

	eecd = E1000_READ_REG(hw, E1000_EECD);
	if (hw->nvm.type == e1000_nvm_eeprom_spi) {
		/* Pull CS high */
		eecd |= E1000_EECD_CS;
		e1000_lower_eec_clk(hw, &eecd);
	} else if (hw->nvm.type == e1000_nvm_eeprom_microwire) {
		/* CS on Microwire is active-high */
		eecd &= ~(E1000_EECD_CS | E1000_EECD_DI);
		E1000_WRITE_REG(hw, E1000_EECD, eecd);
		e1000_raise_eec_clk(hw, &eecd);
		e1000_lower_eec_clk(hw, &eecd);
	}
}