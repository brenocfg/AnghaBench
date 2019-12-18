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
struct meson_sclk_div_data {unsigned int cached_div; int /*<<< orphan*/  cached_duty; int /*<<< orphan*/  div; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int meson_parm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct meson_sclk_div_data* meson_sclk_div_data (struct clk_regmap*) ; 
 int /*<<< orphan*/  sclk_div_get_duty_cycle (struct clk_hw*,int /*<<< orphan*/ *) ; 
 unsigned int sclk_div_maxdiv (struct meson_sclk_div_data*) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static void sclk_div_init(struct clk_hw *hw)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_sclk_div_data *sclk = meson_sclk_div_data(clk);
	unsigned int val;

	val = meson_parm_read(clk->map, &sclk->div);

	/* if the divider is initially disabled, assume max */
	if (!val)
		sclk->cached_div = sclk_div_maxdiv(sclk);
	else
		sclk->cached_div = val + 1;

	sclk_div_get_duty_cycle(hw, &sclk->cached_duty);
}