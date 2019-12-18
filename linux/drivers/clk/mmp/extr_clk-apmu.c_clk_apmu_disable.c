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
struct clk_apmu {unsigned long enable_mask; scalar_t__ lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 unsigned long readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct clk_apmu* to_clk_apmu (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_apmu_disable(struct clk_hw *hw)
{
	struct clk_apmu *apmu = to_clk_apmu(hw);
	unsigned long data;
	unsigned long flags = 0;

	if (apmu->lock)
		spin_lock_irqsave(apmu->lock, flags);

	data = readl_relaxed(apmu->base) & ~apmu->enable_mask;
	writel_relaxed(data, apmu->base);

	if (apmu->lock)
		spin_unlock_irqrestore(apmu->lock, flags);
}