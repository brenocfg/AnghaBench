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
struct clk_hw {int dummy; } ;
struct TYPE_2__ {struct clk_hw hw; } ;
struct tegra_sdmmc_mux {TYPE_1__ gate; struct clk_ops* gate_ops; } ;
struct clk_ops {int /*<<< orphan*/  (* disable ) (struct clk_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct clk_hw*) ; 
 struct tegra_sdmmc_mux* to_clk_sdmmc_mux (struct clk_hw*) ; 

__attribute__((used)) static void clk_sdmmc_mux_disable(struct clk_hw *hw)
{
	struct tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	const struct clk_ops *gate_ops = sdmmc_mux->gate_ops;
	struct clk_hw *gate_hw = &sdmmc_mux->gate.hw;

	gate_ops->disable(gate_hw);
}