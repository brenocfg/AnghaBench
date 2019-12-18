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
struct clkdiv {int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_CTL1_DIV_FACTOR_MASK ; 
 scalar_t__ REG_DIV_CTL1 ; 
 int __spmi_pmic_clkdiv_set_enable_state (struct clkdiv*,int,unsigned int) ; 
 unsigned int div_to_div_factor (unsigned long) ; 
 int is_spmi_pmic_clkdiv_enabled (struct clkdiv*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int spmi_pmic_clkdiv_set_enable_state (struct clkdiv*,int) ; 
 struct clkdiv* to_clkdiv (struct clk_hw*) ; 

__attribute__((used)) static int clk_spmi_pmic_div_set_rate(struct clk_hw *hw, unsigned long rate,
				      unsigned long parent_rate)
{
	struct clkdiv *clkdiv = to_clkdiv(hw);
	unsigned int div_factor = div_to_div_factor(parent_rate / rate);
	unsigned long flags;
	bool enabled;
	int ret;

	spin_lock_irqsave(&clkdiv->lock, flags);
	enabled = is_spmi_pmic_clkdiv_enabled(clkdiv);
	if (enabled) {
		ret = spmi_pmic_clkdiv_set_enable_state(clkdiv, false);
		if (ret)
			goto unlock;
	}

	ret = regmap_update_bits(clkdiv->regmap, clkdiv->base + REG_DIV_CTL1,
				 DIV_CTL1_DIV_FACTOR_MASK, div_factor);
	if (ret)
		goto unlock;

	if (enabled)
		ret = __spmi_pmic_clkdiv_set_enable_state(clkdiv, true,
							  div_factor);

unlock:
	spin_unlock_irqrestore(&clkdiv->lock, flags);

	return ret;
}