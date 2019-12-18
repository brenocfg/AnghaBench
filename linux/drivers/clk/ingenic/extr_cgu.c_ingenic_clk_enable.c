#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ingenic_clk {size_t idx; struct ingenic_cgu* cgu; } ;
struct TYPE_2__ {scalar_t__ delay_us; } ;
struct ingenic_cgu_clk_info {int type; TYPE_1__ gate; } ;
struct ingenic_cgu {int /*<<< orphan*/  lock; struct ingenic_cgu_clk_info* clock_info; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CGU_CLK_GATE ; 
 int /*<<< orphan*/  ingenic_cgu_gate_set (struct ingenic_cgu*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ingenic_clk* to_ingenic_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static int ingenic_clk_enable(struct clk_hw *hw)
{
	struct ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	struct ingenic_cgu *cgu = ingenic_clk->cgu;
	const struct ingenic_cgu_clk_info *clk_info;
	unsigned long flags;

	clk_info = &cgu->clock_info[ingenic_clk->idx];

	if (clk_info->type & CGU_CLK_GATE) {
		/* ungate the clock */
		spin_lock_irqsave(&cgu->lock, flags);
		ingenic_cgu_gate_set(cgu, &clk_info->gate, false);
		spin_unlock_irqrestore(&cgu->lock, flags);

		if (clk_info->gate.delay_us)
			udelay(clk_info->gate.delay_us);
	}

	return 0;
}