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
struct i2s_pll_clk {int /*<<< orphan*/  dev; } ;
struct i2s_pll_cfg {unsigned long rate; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 
 struct i2s_pll_cfg* i2s_pll_get_cfg (unsigned long) ; 
 struct i2s_pll_clk* to_i2s_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static long i2s_pll_round_rate(struct clk_hw *hw, unsigned long rate,
			unsigned long *prate)
{
	struct i2s_pll_clk *clk = to_i2s_pll_clk(hw);
	const struct i2s_pll_cfg *pll_cfg = i2s_pll_get_cfg(*prate);
	int i;

	if (!pll_cfg) {
		dev_err(clk->dev, "invalid parent rate=%ld\n", *prate);
		return -EINVAL;
	}

	for (i = 0; pll_cfg[i].rate != 0; i++)
		if (pll_cfg[i].rate == rate)
			return rate;

	return -EINVAL;
}