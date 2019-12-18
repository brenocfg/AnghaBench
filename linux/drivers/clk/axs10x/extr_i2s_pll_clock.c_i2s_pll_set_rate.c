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
struct i2s_pll_cfg {unsigned long rate; int /*<<< orphan*/  odiv1; int /*<<< orphan*/  odiv0; int /*<<< orphan*/  fbdiv; int /*<<< orphan*/  idiv; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PLL_FBDIV_REG ; 
 int /*<<< orphan*/  PLL_IDIV_REG ; 
 int /*<<< orphan*/  PLL_ODIV0_REG ; 
 int /*<<< orphan*/  PLL_ODIV1_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 struct i2s_pll_cfg* i2s_pll_get_cfg (unsigned long) ; 
 int /*<<< orphan*/  i2s_pll_write (struct i2s_pll_clk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2s_pll_clk* to_i2s_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static int i2s_pll_set_rate(struct clk_hw *hw, unsigned long rate,
			unsigned long parent_rate)
{
	struct i2s_pll_clk *clk = to_i2s_pll_clk(hw);
	const struct i2s_pll_cfg *pll_cfg = i2s_pll_get_cfg(parent_rate);
	int i;

	if (!pll_cfg) {
		dev_err(clk->dev, "invalid parent rate=%ld\n", parent_rate);
		return -EINVAL;
	}

	for (i = 0; pll_cfg[i].rate != 0; i++) {
		if (pll_cfg[i].rate == rate) {
			i2s_pll_write(clk, PLL_IDIV_REG, pll_cfg[i].idiv);
			i2s_pll_write(clk, PLL_FBDIV_REG, pll_cfg[i].fbdiv);
			i2s_pll_write(clk, PLL_ODIV0_REG, pll_cfg[i].odiv0);
			i2s_pll_write(clk, PLL_ODIV1_REG, pll_cfg[i].odiv1);
			return 0;
		}
	}

	dev_err(clk->dev, "invalid rate=%ld, parent_rate=%ld\n", rate,
			parent_rate);
	return -EINVAL;
}