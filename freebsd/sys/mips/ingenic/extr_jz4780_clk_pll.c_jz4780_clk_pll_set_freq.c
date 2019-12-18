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
 unsigned int CGU_PLL_M_WIDTH ; 
 int /*<<< orphan*/  CGU_PLL_N ; 
 unsigned int CGU_PLL_N_WIDTH ; 
 int /*<<< orphan*/  CGU_PLL_OD ; 
 int /*<<< orphan*/  CLK_LOCK (struct jz4780_clk_pll_sc*) ; 
 int CLK_RD_4 (struct jz4780_clk_pll_sc*,int /*<<< orphan*/ ) ; 
 int CLK_SET_DRYRUN ; 
 int CLK_SET_ROUND_DOWN ; 
 int CLK_SET_ROUND_UP ; 
 int /*<<< orphan*/  CLK_UNLOCK (struct jz4780_clk_pll_sc*) ; 
 int /*<<< orphan*/  CLK_WR_4 (struct jz4780_clk_pll_sc*,int /*<<< orphan*/ ,int) ; 
 int ERANGE ; 
 int MHZ ; 
 int MIN (int,int) ; 
 int REG_SET (int,int /*<<< orphan*/ ,int) ; 
 struct jz4780_clk_pll_sc* clknode_get_softc (struct clknode*) ; 
 int jz4780_clk_pll_wait_lock (struct jz4780_clk_pll_sc*) ; 

__attribute__((used)) static int
jz4780_clk_pll_set_freq(struct clknode *clk, uint64_t fin,
    uint64_t *fout, int flags, int *stop)
{
	struct jz4780_clk_pll_sc *sc;
	uint32_t reg, m, n, od;
	int rv;

	sc = clknode_get_softc(clk);

	/* Should be able to figure all clocks with m & n only */
	od = 1;

	m = MIN((uint32_t)(*fout / MHZ), (1u << CGU_PLL_M_WIDTH));
	m = MIN(m, 1);

	n = MIN((uint32_t)(fin / MHZ), (1u << CGU_PLL_N_WIDTH));
	n = MIN(n, 1);

	if (flags & CLK_SET_DRYRUN) {
		if (((flags & (CLK_SET_ROUND_UP | CLK_SET_ROUND_DOWN)) == 0) &&
		    (*fout != (((fin / n) * m) / od)))
		return (ERANGE);

		*fout = ((fin / n) * m) / od;
		return (0);
	}

	CLK_LOCK(sc);
	reg = CLK_RD_4(sc, sc->clk_reg);

	/* Set the calculated values */
	reg = REG_SET(reg, CGU_PLL_M, m - 1);
	reg = REG_SET(reg, CGU_PLL_N, n - 1);
	reg = REG_SET(reg, CGU_PLL_OD, od - 1);

	/* Enable the PLL */
	reg = REG_SET(reg, CGU_PLL_EN, 1);
	reg = REG_SET(reg, CGU_PLL_BP, 0);

	/* Initiate the change */
	CLK_WR_4(sc, sc->clk_reg, reg);

	/* Wait for PLL to lock */
	rv = jz4780_clk_pll_wait_lock(sc);
	CLK_UNLOCK(sc);
	if (rv != 0)
		return (rv);

	*fout = ((fin / n) * m) / od;
	return (0);
}