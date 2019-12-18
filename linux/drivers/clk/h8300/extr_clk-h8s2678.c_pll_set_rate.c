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
struct pll_clock {int /*<<< orphan*/  pllcr; int /*<<< orphan*/  sckcr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clklock ; 
 unsigned char readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pll_clock* to_pll_clock (struct clk_hw*) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pll_set_rate(struct clk_hw *hw, unsigned long rate,
			unsigned long parent_rate)
{
	int pll;
	unsigned char val;
	unsigned long flags;
	struct pll_clock *pll_clock = to_pll_clock(hw);

	pll = ((rate / parent_rate) / 2) & 0x03;
	spin_lock_irqsave(&clklock, flags);
	val = readb(pll_clock->sckcr);
	val |= 0x08;
	writeb(val, pll_clock->sckcr);
	val = readb(pll_clock->pllcr);
	val &= ~0x03;
	val |= pll;
	writeb(val, pll_clock->pllcr);
	spin_unlock_irqrestore(&clklock, flags);
	return 0;
}