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
struct rockchip_clk_pll {scalar_t__ reg_base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIWORD_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RK3399_PLLCON (int) ; 
 int /*<<< orphan*/  RK3399_PLLCON3_PWRDOWN ; 
 int /*<<< orphan*/  rockchip_rk3399_pll_wait_lock (struct rockchip_clk_pll*) ; 
 struct rockchip_clk_pll* to_rockchip_clk_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rockchip_rk3399_pll_enable(struct clk_hw *hw)
{
	struct rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);

	writel(HIWORD_UPDATE(0, RK3399_PLLCON3_PWRDOWN, 0),
	       pll->reg_base + RK3399_PLLCON(3));
	rockchip_rk3399_pll_wait_lock(pll);

	return 0;
}