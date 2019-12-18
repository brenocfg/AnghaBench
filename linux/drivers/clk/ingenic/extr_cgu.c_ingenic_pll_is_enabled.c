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
struct ingenic_clk {struct ingenic_cgu* cgu; } ;
struct ingenic_cgu_pll_info {int /*<<< orphan*/  enable_bit; scalar_t__ reg; } ;
struct ingenic_cgu_clk_info {struct ingenic_cgu_pll_info pll; } ;
struct ingenic_cgu {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ingenic_cgu_clk_info* to_clk_info (struct ingenic_clk*) ; 
 struct ingenic_clk* to_ingenic_clk (struct clk_hw*) ; 

__attribute__((used)) static int ingenic_pll_is_enabled(struct clk_hw *hw)
{
	struct ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	struct ingenic_cgu *cgu = ingenic_clk->cgu;
	const struct ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	const struct ingenic_cgu_pll_info *pll_info = &clk_info->pll;
	unsigned long flags;
	u32 ctl;

	spin_lock_irqsave(&cgu->lock, flags);
	ctl = readl(cgu->base + pll_info->reg);
	spin_unlock_irqrestore(&cgu->lock, flags);

	return !!(ctl & BIT(pll_info->enable_bit));
}