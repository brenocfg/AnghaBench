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
struct clk_hw {int dummy; } ;
struct clk_hfpll {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hfpll_disable (struct clk_hfpll*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct clk_hfpll* to_clk_hfpll (struct clk_hw*) ; 

__attribute__((used)) static void clk_hfpll_disable(struct clk_hw *hw)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	unsigned long flags;

	spin_lock_irqsave(&h->lock, flags);
	__clk_hfpll_disable(h);
	spin_unlock_irqrestore(&h->lock, flags);
}