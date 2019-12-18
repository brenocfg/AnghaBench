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
typedef  int u32 ;
struct owl_factor_hw {int shift; int /*<<< orphan*/  reg; int /*<<< orphan*/  table; } ;
struct owl_clk_common {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int _get_table_val (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int div_mask (struct owl_factor_hw const*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int owl_factor_helper_set_rate(const struct owl_clk_common *common,
				const struct owl_factor_hw *factor_hw,
				unsigned long rate,
				unsigned long parent_rate)
{
	u32 val, reg;

	val = _get_table_val(factor_hw->table, rate, parent_rate);

	if (val > div_mask(factor_hw))
		val = div_mask(factor_hw);

	regmap_read(common->regmap, factor_hw->reg, &reg);

	reg &= ~(div_mask(factor_hw) << factor_hw->shift);
	reg |= val << factor_hw->shift;

	regmap_write(common->regmap, factor_hw->reg, reg);

	return 0;
}