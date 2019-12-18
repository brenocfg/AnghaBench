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
typedef  scalar_t__ u8 ;
struct max9485_rate {scalar_t__ out; scalar_t__ reg_value; } ;
struct max9485_driver_data {scalar_t__ reg_value; } ;
struct max9485_clk_hw {struct max9485_driver_data* drvdata; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX9485_FREQ_MASK ; 
 struct max9485_rate* max9485_rates ; 
 struct max9485_clk_hw* to_max9485_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long max9485_clkout_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct max9485_clk_hw *clk_hw = to_max9485_clk(hw);
	struct max9485_driver_data *drvdata = clk_hw->drvdata;
	u8 val = drvdata->reg_value & MAX9485_FREQ_MASK;
	const struct max9485_rate *entry;

	for (entry = max9485_rates; entry->out != 0; entry++)
		if (val == entry->reg_value)
			return entry->out;

	return 0;
}