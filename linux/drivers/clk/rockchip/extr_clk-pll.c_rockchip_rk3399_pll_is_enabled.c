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
struct rockchip_clk_pll {scalar_t__ reg_base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ RK3399_PLLCON (int) ; 
 int RK3399_PLLCON3_PWRDOWN ; 
 int readl (scalar_t__) ; 
 struct rockchip_clk_pll* to_rockchip_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static int rockchip_rk3399_pll_is_enabled(struct clk_hw *hw)
{
	struct rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	u32 pllcon = readl(pll->reg_base + RK3399_PLLCON(3));

	return !(pllcon & RK3399_PLLCON3_PWRDOWN);
}