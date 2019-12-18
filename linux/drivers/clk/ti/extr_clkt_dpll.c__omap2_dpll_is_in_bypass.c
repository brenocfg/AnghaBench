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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int dpll_bypass_vals; } ;

/* Variables and functions */
 int __ffs (int) ; 
 TYPE_1__* ti_clk_get_features () ; 

__attribute__((used)) static int _omap2_dpll_is_in_bypass(u32 v)
{
	u8 mask, val;

	mask = ti_clk_get_features()->dpll_bypass_vals;

	/*
	 * Each set bit in the mask corresponds to a bypass value equal
	 * to the bitshift. Go through each set-bit in the mask and
	 * compare against the given register value.
	 */
	while (mask) {
		val = __ffs(mask);
		mask ^= (1 << val);
		if (v == val)
			return 1;
	}

	return 0;
}