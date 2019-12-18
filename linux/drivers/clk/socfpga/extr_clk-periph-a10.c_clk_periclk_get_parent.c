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
struct socfpga_periph_clk {TYPE_1__ hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_MGR_FREE_MASK ; 
 int CLK_MGR_FREE_SHIFT ; 
 int /*<<< orphan*/  SOCFPGA_MPU_FREE_CLK ; 
 int /*<<< orphan*/  SOCFPGA_NOC_FREE_CLK ; 
 int /*<<< orphan*/  SOCFPGA_SDMMC_FREE_CLK ; 
 char* clk_hw_get_name (struct clk_hw*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ streq (char const*,int /*<<< orphan*/ ) ; 
 struct socfpga_periph_clk* to_socfpga_periph_clk (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_periclk_get_parent(struct clk_hw *hwclk)
{
	struct socfpga_periph_clk *socfpgaclk = to_socfpga_periph_clk(hwclk);
	u32 clk_src;
	const char *name = clk_hw_get_name(hwclk);

	clk_src = readl(socfpgaclk->hw.reg);
	if (streq(name, SOCFPGA_MPU_FREE_CLK) ||
	    streq(name, SOCFPGA_NOC_FREE_CLK) ||
	    streq(name, SOCFPGA_SDMMC_FREE_CLK))
		return (clk_src >> CLK_MGR_FREE_SHIFT) &
			CLK_MGR_FREE_MASK;
	else
		return 0;
}