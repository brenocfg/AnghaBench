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
struct clk_hw {int dummy; } ;
struct clk_hisi_phase {int mask; int shift; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int hisi_phase_degrees_to_regval (struct clk_hisi_phase*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_hisi_phase* to_clk_hisi_phase (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_clk_set_phase(struct clk_hw *hw, int degrees)
{
	struct clk_hisi_phase *phase = to_clk_hisi_phase(hw);
	unsigned long flags = 0;
	int regval;
	u32 val;

	regval = hisi_phase_degrees_to_regval(phase, degrees);
	if (regval < 0)
		return regval;

	spin_lock_irqsave(phase->lock, flags);

	val = readl(phase->reg);
	val &= ~phase->mask;
	val |= regval << phase->shift;
	writel(val, phase->reg);

	spin_unlock_irqrestore(phase->lock, flags);

	return 0;
}