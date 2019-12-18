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
struct hb_clk {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int HB_PLL_LOCK ; 
 int HB_PLL_LOCK_500 ; 
 int HB_PLL_RESET ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct hb_clk* to_hb_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_pll_prepare(struct clk_hw *hwclk)
	{
	struct hb_clk *hbclk = to_hb_clk(hwclk);
	u32 reg;

	reg = readl(hbclk->reg);
	reg &= ~HB_PLL_RESET;
	writel(reg, hbclk->reg);

	while ((readl(hbclk->reg) & HB_PLL_LOCK) == 0)
		;
	while ((readl(hbclk->reg) & HB_PLL_LOCK_500) == 0)
		;

	return 0;
}