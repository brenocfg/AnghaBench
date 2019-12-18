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
struct max77686_clk_init_data {TYPE_1__* clk_info; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int clk_enable_mask; int /*<<< orphan*/  clk_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct max77686_clk_init_data* to_max77686_clk_init_data (struct clk_hw*) ; 

__attribute__((used)) static int max77686_clk_is_prepared(struct clk_hw *hw)
{
	struct max77686_clk_init_data *max77686 = to_max77686_clk_init_data(hw);
	int ret;
	u32 val;

	ret = regmap_read(max77686->regmap, max77686->clk_info->clk_reg, &val);

	if (ret < 0)
		return -EINVAL;

	return val & max77686->clk_info->clk_enable_mask;
}