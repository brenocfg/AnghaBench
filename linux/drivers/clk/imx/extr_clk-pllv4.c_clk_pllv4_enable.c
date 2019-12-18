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
struct clk_pllv4 {int /*<<< orphan*/  base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_EN ; 
 int clk_pllv4_wait_lock (struct clk_pllv4*) ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_pllv4* to_clk_pllv4 (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_pllv4_enable(struct clk_hw *hw)
{
	u32 val;
	struct clk_pllv4 *pll = to_clk_pllv4(hw);

	val = readl_relaxed(pll->base);
	val |= PLL_EN;
	writel_relaxed(val, pll->base);

	return clk_pllv4_wait_lock(pll);
}