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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;
struct socfpga_pll {TYPE_1__ hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_MGR_PLL_CLK_SRC_MASK ; 
 int CLK_MGR_PLL_CLK_SRC_SHIFT ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct socfpga_pll* to_socfpga_clk (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_pll_get_parent(struct clk_hw *hwclk)
{
	struct socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	u32 pll_src;

	pll_src = readl(socfpgaclk->hw.reg);

	return (pll_src >> CLK_MGR_PLL_CLK_SRC_SHIFT) &
		CLK_MGR_PLL_CLK_SRC_MASK;
}