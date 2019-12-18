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
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;
struct clk_device {int div_mask; } ;

/* Variables and functions */
 struct clk_device* to_clk_device (struct clk_hw*) ; 

__attribute__((used)) static long vt8500_dclk_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *prate)
{
	struct clk_device *cdev = to_clk_device(hw);
	u32 divisor;

	if (rate == 0)
		return 0;

	divisor = *prate / rate;

	/* If prate / rate would be decimal, incr the divisor */
	if (rate * divisor < *prate)
		divisor++;

	/*
	 * If this is a request for SDMMC we have to adjust the divisor
	 * when >31 to use the fixed predivisor
	 */
	if ((cdev->div_mask == 0x3F) && (divisor > 31)) {
		divisor = 64 * ((divisor / 64) + 1);
	}

	return *prate / divisor;
}