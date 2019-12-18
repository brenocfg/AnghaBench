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
typedef  int u8 ;
typedef  int u32 ;
struct clk_pm_cpu {int shift_mux; int mask_mux; int /*<<< orphan*/  reg_mux; int /*<<< orphan*/  nb_pm_base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int armada_3700_pm_dvfs_get_cpu_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ armada_3700_pm_dvfs_is_enabled (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct clk_pm_cpu* to_clk_pm_cpu (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_pm_cpu_get_parent(struct clk_hw *hw)
{
	struct clk_pm_cpu *pm_cpu = to_clk_pm_cpu(hw);
	u32 val;

	if (armada_3700_pm_dvfs_is_enabled(pm_cpu->nb_pm_base)) {
		val = armada_3700_pm_dvfs_get_cpu_parent(pm_cpu->nb_pm_base);
	} else {
		val = readl(pm_cpu->reg_mux) >> pm_cpu->shift_mux;
		val &= pm_cpu->mask_mux;
	}

	return val;
}