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
typedef  int u8 ;
struct ingenic_tcu_clk_info {int /*<<< orphan*/  tcsr_reg; } ;
struct ingenic_tcu_clk {int /*<<< orphan*/  idx; TYPE_1__* tcu; struct ingenic_tcu_clk_info* info; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int TCU_TCSR_PRESCALE_LSB ; 
 int /*<<< orphan*/  TCU_TCSR_PRESCALE_MASK ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ingenic_tcu_disable_regs (struct clk_hw*) ; 
 int ingenic_tcu_enable_regs (struct clk_hw*) ; 
 int ingenic_tcu_get_prescale (unsigned long,unsigned long) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ingenic_tcu_clk* to_tcu_clk (struct clk_hw*) ; 

__attribute__((used)) static int ingenic_tcu_set_rate(struct clk_hw *hw, unsigned long req_rate,
		unsigned long parent_rate)
{
	struct ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	const struct ingenic_tcu_clk_info *info = tcu_clk->info;
	u8 prescale = ingenic_tcu_get_prescale(parent_rate, req_rate);
	bool was_enabled;
	int ret;

	was_enabled = ingenic_tcu_enable_regs(hw);

	ret = regmap_update_bits(tcu_clk->tcu->map, info->tcsr_reg,
				 TCU_TCSR_PRESCALE_MASK,
				 prescale << TCU_TCSR_PRESCALE_LSB);
	WARN_ONCE(ret < 0, "Unable to update TCSR %d", tcu_clk->idx);

	if (!was_enabled)
		ingenic_tcu_disable_regs(hw);

	return 0;
}