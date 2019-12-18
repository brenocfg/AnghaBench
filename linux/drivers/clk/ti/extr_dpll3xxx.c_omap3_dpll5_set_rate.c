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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int OMAP3_DPLL5_FREQ_FOR_USBHOST ; 
 scalar_t__ omap3_dpll5_apply_errata (struct clk_hw*,unsigned long) ; 
 int omap3_noncore_dpll_set_rate (struct clk_hw*,unsigned long,unsigned long) ; 

int omap3_dpll5_set_rate(struct clk_hw *hw, unsigned long rate,
			 unsigned long parent_rate)
{
	if (rate == OMAP3_DPLL5_FREQ_FOR_USBHOST * 8) {
		if (omap3_dpll5_apply_errata(hw, parent_rate))
			return 0;
	}

	return omap3_noncore_dpll_set_rate(hw, rate, parent_rate);
}