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
struct clk_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  en_reg; int /*<<< orphan*/  en_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_device* to_clk_device (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vt8500_dclk_enable(struct clk_hw *hw)
{
	struct clk_device *cdev = to_clk_device(hw);
	u32 en_val;
	unsigned long flags = 0;

	spin_lock_irqsave(cdev->lock, flags);

	en_val = readl(cdev->en_reg);
	en_val |= BIT(cdev->en_bit);
	writel(en_val, cdev->en_reg);

	spin_unlock_irqrestore(cdev->lock, flags);
	return 0;
}