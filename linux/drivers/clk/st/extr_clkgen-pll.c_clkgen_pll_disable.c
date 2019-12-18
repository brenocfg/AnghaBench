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
struct clkgen_pll {scalar_t__ lock; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clkgen_pll_disable (struct clk_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct clkgen_pll* to_clkgen_pll (struct clk_hw*) ; 

__attribute__((used)) static void clkgen_pll_disable(struct clk_hw *hw)
{
	struct clkgen_pll *pll = to_clkgen_pll(hw);
	unsigned long flags = 0;

	if (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	__clkgen_pll_disable(hw);

	if (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);
}