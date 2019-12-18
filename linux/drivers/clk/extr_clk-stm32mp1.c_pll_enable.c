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
struct stm32_pll_obj {int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PLL_ON ; 
 int PLL_RDY ; 
 unsigned int TIMEOUT ; 
 scalar_t__ __pll_is_enabled (struct clk_hw*) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct stm32_pll_obj* to_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pll_enable(struct clk_hw *hw)
{
	struct stm32_pll_obj *clk_elem = to_pll(hw);
	u32 reg;
	unsigned long flags = 0;
	unsigned int timeout = TIMEOUT;
	int bit_status = 0;

	spin_lock_irqsave(clk_elem->lock, flags);

	if (__pll_is_enabled(hw))
		goto unlock;

	reg = readl_relaxed(clk_elem->reg);
	reg |= PLL_ON;
	writel_relaxed(reg, clk_elem->reg);

	/* We can't use readl_poll_timeout() because we can be blocked if
	 * someone enables this clock before clocksource changes.
	 * Only jiffies counter is available. Jiffies are incremented by
	 * interruptions and enable op does not allow to be interrupted.
	 */
	do {
		bit_status = !(readl_relaxed(clk_elem->reg) & PLL_RDY);

		if (bit_status)
			udelay(120);

	} while (bit_status && --timeout);

unlock:
	spin_unlock_irqrestore(clk_elem->lock, flags);

	return bit_status;
}