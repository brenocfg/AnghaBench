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
struct ingenic_tcu_clk_info {int /*<<< orphan*/  gate_bit; } ;
struct ingenic_tcu_clk {struct ingenic_tcu* tcu; struct ingenic_tcu_clk_info* info; } ;
struct ingenic_tcu {int /*<<< orphan*/  map; int /*<<< orphan*/  clk; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCU_REG_TSCR ; 
 int /*<<< orphan*/  ingenic_tcu_is_enabled (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ingenic_tcu_clk* to_tcu_clk (struct clk_hw*) ; 

__attribute__((used)) static bool ingenic_tcu_enable_regs(struct clk_hw *hw)
{
	struct ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	const struct ingenic_tcu_clk_info *info = tcu_clk->info;
	struct ingenic_tcu *tcu = tcu_clk->tcu;
	bool enabled = false;

	/*
	 * If the SoC has no global TCU clock, we must ungate the channel's
	 * clock to be able to access its registers.
	 * If we have a TCU clock, it will be enabled automatically as it has
	 * been attached to the regmap.
	 */
	if (!tcu->clk) {
		enabled = !!ingenic_tcu_is_enabled(hw);
		regmap_write(tcu->map, TCU_REG_TSCR, BIT(info->gate_bit));
	}

	return enabled;
}