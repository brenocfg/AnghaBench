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
struct tegra_clk_periph_gate {scalar_t__* enable_refcnt; size_t clk_num; int flags; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int TEGRA_PERIPH_ON_APB ; 
 int /*<<< orphan*/  periph_clk_to_bit (struct tegra_clk_periph_gate*) ; 
 int /*<<< orphan*/  periph_ref_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_read_chipid () ; 
 struct tegra_clk_periph_gate* to_clk_periph_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  write_enb_clr (int /*<<< orphan*/ ,struct tegra_clk_periph_gate*) ; 

__attribute__((used)) static void clk_periph_disable(struct clk_hw *hw)
{
	struct tegra_clk_periph_gate *gate = to_clk_periph_gate(hw);
	unsigned long flags = 0;

	spin_lock_irqsave(&periph_ref_lock, flags);

	gate->enable_refcnt[gate->clk_num]--;
	if (gate->enable_refcnt[gate->clk_num] > 0) {
		spin_unlock_irqrestore(&periph_ref_lock, flags);
		return;
	}

	/*
	 * If peripheral is in the APB bus then read the APB bus to
	 * flush the write operation in apb bus. This will avoid the
	 * peripheral access after disabling clock
	 */
	if (gate->flags & TEGRA_PERIPH_ON_APB)
		tegra_read_chipid();

	write_enb_clr(periph_clk_to_bit(gate), gate);

	spin_unlock_irqrestore(&periph_ref_lock, flags);
}