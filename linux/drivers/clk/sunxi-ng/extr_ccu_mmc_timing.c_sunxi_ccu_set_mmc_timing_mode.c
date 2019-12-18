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
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;
struct clk {int dummy; } ;
struct ccu_common {int features; int /*<<< orphan*/  lock; scalar_t__ reg; scalar_t__ base; } ;

/* Variables and functions */
 int CCU_FEATURE_MMC_TIMING_SWITCH ; 
 int /*<<< orphan*/  CCU_MMC_NEW_TIMING_MODE ; 
 int ENOTSUPP ; 
 struct clk_hw* __clk_get_hw (struct clk*) ; 
 struct ccu_common* hw_to_ccu_common (struct clk_hw*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int sunxi_ccu_set_mmc_timing_mode(struct clk *clk, bool new_mode)
{
	struct clk_hw *hw = __clk_get_hw(clk);
	struct ccu_common *cm = hw_to_ccu_common(hw);
	unsigned long flags;
	u32 val;

	if (!(cm->features & CCU_FEATURE_MMC_TIMING_SWITCH))
		return -ENOTSUPP;

	spin_lock_irqsave(cm->lock, flags);

	val = readl(cm->base + cm->reg);
	if (new_mode)
		val |= CCU_MMC_NEW_TIMING_MODE;
	else
		val &= ~CCU_MMC_NEW_TIMING_MODE;
	writel(val, cm->base + cm->reg);

	spin_unlock_irqrestore(cm->lock, flags);

	return 0;
}