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
struct rockchip_cpuclk_reg_data {int div_core_shift; int div_core_mask; scalar_t__ core_reg; } ;
struct rockchip_cpuclk {scalar_t__ reg_base; struct rockchip_cpuclk_reg_data* reg_data; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int readl_relaxed (scalar_t__) ; 
 struct rockchip_cpuclk* to_rockchip_cpuclk_hw (struct clk_hw*) ; 

__attribute__((used)) static unsigned long rockchip_cpuclk_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	struct rockchip_cpuclk *cpuclk = to_rockchip_cpuclk_hw(hw);
	const struct rockchip_cpuclk_reg_data *reg_data = cpuclk->reg_data;
	u32 clksel0 = readl_relaxed(cpuclk->reg_base + reg_data->core_reg);

	clksel0 >>= reg_data->div_core_shift;
	clksel0 &= reg_data->div_core_mask;
	return parent_rate / (clksel0 + 1);
}