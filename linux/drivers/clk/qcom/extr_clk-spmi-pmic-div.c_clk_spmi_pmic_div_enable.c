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
struct clkdiv {int /*<<< orphan*/  lock; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int spmi_pmic_clkdiv_set_enable_state (struct clkdiv*,int) ; 
 struct clkdiv* to_clkdiv (struct clk_hw*) ; 

__attribute__((used)) static int clk_spmi_pmic_div_enable(struct clk_hw *hw)
{
	struct clkdiv *clkdiv = to_clkdiv(hw);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&clkdiv->lock, flags);
	ret = spmi_pmic_clkdiv_set_enable_state(clkdiv, true);
	spin_unlock_irqrestore(&clkdiv->lock, flags);

	return ret;
}