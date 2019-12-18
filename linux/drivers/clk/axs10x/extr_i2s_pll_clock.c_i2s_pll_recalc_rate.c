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
struct i2s_pll_clk {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_FBDIV_REG ; 
 int /*<<< orphan*/  PLL_IDIV_REG ; 
 int /*<<< orphan*/  PLL_ODIV0_REG ; 
 unsigned int i2s_pll_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_pll_read (struct i2s_pll_clk*,int /*<<< orphan*/ ) ; 
 struct i2s_pll_clk* to_i2s_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long i2s_pll_recalc_rate(struct clk_hw *hw,
			unsigned long parent_rate)
{
	struct i2s_pll_clk *clk = to_i2s_pll_clk(hw);
	unsigned int idiv, fbdiv, odiv;

	idiv = i2s_pll_get_value(i2s_pll_read(clk, PLL_IDIV_REG));
	fbdiv = i2s_pll_get_value(i2s_pll_read(clk, PLL_FBDIV_REG));
	odiv = i2s_pll_get_value(i2s_pll_read(clk, PLL_ODIV0_REG));

	return ((parent_rate / idiv) * fbdiv) / odiv;
}