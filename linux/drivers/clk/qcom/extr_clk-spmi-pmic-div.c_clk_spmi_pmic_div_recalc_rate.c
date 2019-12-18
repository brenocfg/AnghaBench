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
struct clkdiv {scalar_t__ base; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_CTL1_DIV_FACTOR_MASK ; 
 scalar_t__ REG_DIV_CTL1 ; 
 unsigned long div_factor_to_div (unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 struct clkdiv* to_clkdiv (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
clk_spmi_pmic_div_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct clkdiv *clkdiv = to_clkdiv(hw);
	unsigned int div_factor;

	regmap_read(clkdiv->regmap, clkdiv->base + REG_DIV_CTL1, &div_factor);
	div_factor &= DIV_CTL1_DIV_FACTOR_MASK;

	return parent_rate / div_factor_to_div(div_factor);
}