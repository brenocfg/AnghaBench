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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct jz4780_clk_pll_sc {int /*<<< orphan*/  clk_reg; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGU_PLL_BP ; 
 int /*<<< orphan*/  CGU_PLL_EN ; 
 int /*<<< orphan*/  CGU_PLL_M ; 
 int /*<<< orphan*/  CGU_PLL_N ; 
 int /*<<< orphan*/  CGU_PLL_OD ; 
 int CLK_RD_4 (struct jz4780_clk_pll_sc*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ REG_GET (int,int /*<<< orphan*/ ) ; 
 struct jz4780_clk_pll_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
jz4780_clk_pll_recalc_freq(struct clknode *clk, uint64_t *freq)
{
	struct jz4780_clk_pll_sc *sc;
	uint32_t reg, m, n, od;

	sc = clknode_get_softc(clk);
	reg = CLK_RD_4(sc, sc->clk_reg);

	/* Check for PLL enabled status */
	if (REG_GET(reg, CGU_PLL_EN) == 0) {
		*freq = 0;
		return 0;
	}

	/* Return parent frequency if PPL is being bypassed */
	if (REG_GET(reg, CGU_PLL_BP) != 0)
		return 0;

	m = REG_GET(reg, CGU_PLL_M) + 1;
	n = REG_GET(reg, CGU_PLL_N) + 1;
	od = REG_GET(reg, CGU_PLL_OD) + 1;

	/* Sanity check values */
	if (m == 0 || n == 0 || od == 0) {
		*freq = 0;
		return (EINVAL);
	}

	*freq = ((*freq / n) * m) / od;
	return (0);
}