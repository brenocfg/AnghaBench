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
struct rk_clk_pll_sc {scalar_t__ base_offset; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int /*<<< orphan*/  READ4 (struct clknode*,scalar_t__,int*) ; 
 int RK3328_CLK_PLL_DSMPD_MASK ; 
 int RK3328_CLK_PLL_DSMPD_SHIFT ; 
 int RK3328_CLK_PLL_FBDIV_MASK ; 
 int RK3328_CLK_PLL_FBDIV_SHIFT ; 
 int RK3328_CLK_PLL_FRAC_MASK ; 
 int RK3328_CLK_PLL_FRAC_SHIFT ; 
 int RK3328_CLK_PLL_POSTDIV1_MASK ; 
 int RK3328_CLK_PLL_POSTDIV1_SHIFT ; 
 int RK3328_CLK_PLL_POSTDIV2_MASK ; 
 int RK3328_CLK_PLL_POSTDIV2_SHIFT ; 
 int RK3328_CLK_PLL_REFDIV_MASK ; 
 int RK3328_CLK_PLL_REFDIV_SHIFT ; 
 struct rk_clk_pll_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
rk3328_clk_pll_recalc(struct clknode *clk, uint64_t *freq)
{
	struct rk_clk_pll_sc *sc;
	uint64_t rate;
	uint32_t dsmpd, refdiv, fbdiv;
	uint32_t postdiv1, postdiv2, frac;
	uint32_t raw1, raw2, raw3;

	sc = clknode_get_softc(clk);

	DEVICE_LOCK(clk);

	READ4(clk, sc->base_offset, &raw1);
	READ4(clk, sc->base_offset + 4, &raw2);
	READ4(clk, sc->base_offset + 8, &raw3);

	fbdiv = (raw1 & RK3328_CLK_PLL_FBDIV_MASK) >> RK3328_CLK_PLL_FBDIV_SHIFT;
	postdiv1 = (raw1 & RK3328_CLK_PLL_POSTDIV1_MASK) >> RK3328_CLK_PLL_POSTDIV1_SHIFT;

	dsmpd = (raw2 & RK3328_CLK_PLL_DSMPD_MASK) >> RK3328_CLK_PLL_DSMPD_SHIFT;
	refdiv = (raw2 & RK3328_CLK_PLL_REFDIV_MASK) >> RK3328_CLK_PLL_REFDIV_SHIFT;
	postdiv2 = (raw2 & RK3328_CLK_PLL_POSTDIV2_MASK) >> RK3328_CLK_PLL_POSTDIV2_SHIFT;

	frac = (raw3 & RK3328_CLK_PLL_FRAC_MASK) >> RK3328_CLK_PLL_FRAC_SHIFT;

	DEVICE_UNLOCK(clk);

	rate = *freq * fbdiv / refdiv;
	if (dsmpd == 0) {
		/* Fractional mode */
		uint64_t frac_rate;

		frac_rate = *freq * frac / refdiv;
		rate += frac_rate >> 24;
	}

	*freq = rate / postdiv1 / postdiv2;

	if (*freq % 2)
		*freq = *freq + 1;

	return (0);
}