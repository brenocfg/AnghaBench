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
typedef  int /*<<< orphan*/  u32 ;
struct clk_pll14xx {scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ GNRL_CTL ; 
 int /*<<< orphan*/  RST_MASK ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct clk_pll14xx* to_clk_pll14xx (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void clk_pll14xx_unprepare(struct clk_hw *hw)
{
	struct clk_pll14xx *pll = to_clk_pll14xx(hw);
	u32 val;

	/*
	 * Set RST to 0, power down mode is enabled and
	 * every digital block is reset
	 */
	val = readl_relaxed(pll->base + GNRL_CTL);
	val &= ~RST_MASK;
	writel_relaxed(val, pll->base + GNRL_CTL);
}