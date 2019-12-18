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
struct stm32_pll_obj {int /*<<< orphan*/  lock; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int __pll_is_enabled (struct clk_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct stm32_pll_obj* to_pll (struct clk_hw*) ; 

__attribute__((used)) static int pll_is_enabled(struct clk_hw *hw)
{
	struct stm32_pll_obj *clk_elem = to_pll(hw);
	unsigned long flags = 0;
	int ret;

	spin_lock_irqsave(clk_elem->lock, flags);
	ret = __pll_is_enabled(hw);
	spin_unlock_irqrestore(clk_elem->lock, flags);

	return ret;
}