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
struct da8xx_cfgchip_gate_clk {unsigned int mask; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct da8xx_cfgchip_gate_clk* to_da8xx_cfgchip_gate_clk (struct clk_hw*) ; 

__attribute__((used)) static int da8xx_cfgchip_gate_clk_is_enabled(struct clk_hw *hw)
{
	struct da8xx_cfgchip_gate_clk *clk = to_da8xx_cfgchip_gate_clk(hw);
	unsigned int val;

	regmap_read(clk->regmap, clk->reg, &val);

	return !!(val & clk->mask);
}