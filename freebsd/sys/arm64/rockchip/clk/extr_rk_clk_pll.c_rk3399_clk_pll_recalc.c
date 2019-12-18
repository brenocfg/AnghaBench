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
 int RK3399_CLK_PLL_DSMPD_MASK ; 
 int RK3399_CLK_PLL_DSMPD_SHIFT ; 
 int RK3399_CLK_PLL_FBDIV_MASK ; 
 int RK3399_CLK_PLL_FBDIV_SHIFT ; 
 int RK3399_CLK_PLL_FRAC_MASK ; 
 int RK3399_CLK_PLL_FRAC_SHIFT ; 
 int RK3399_CLK_PLL_MODE_DEEPSLOW ; 
 int RK3399_CLK_PLL_MODE_MASK ; 
 int RK3399_CLK_PLL_MODE_SHIFT ; 
 int RK3399_CLK_PLL_MODE_SLOW ; 
 int RK3399_CLK_PLL_POSTDIV1_MASK ; 
 int RK3399_CLK_PLL_POSTDIV1_SHIFT ; 
 int RK3399_CLK_PLL_POSTDIV2_MASK ; 
 int RK3399_CLK_PLL_POSTDIV2_SHIFT ; 
 int RK3399_CLK_PLL_REFDIV_MASK ; 
 int RK3399_CLK_PLL_REFDIV_SHIFT ; 
 struct rk_clk_pll_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  dprintf (char*,int) ; 

__attribute__((used)) static int
rk3399_clk_pll_recalc(struct clknode *clk, uint64_t *freq)
{
	struct rk_clk_pll_sc *sc;
	uint32_t dsmpd, refdiv, fbdiv;
	uint32_t postdiv1, postdiv2, fracdiv;
	uint32_t con1, con2, con3, con4;
	uint64_t foutvco;
	uint32_t mode;
	sc = clknode_get_softc(clk);

	DEVICE_LOCK(clk);
	READ4(clk, sc->base_offset, &con1);
	READ4(clk, sc->base_offset + 4, &con2);
	READ4(clk, sc->base_offset + 8, &con3);
	READ4(clk, sc->base_offset + 0xC, &con4);
	DEVICE_UNLOCK(clk);

	/*
	 * if we are in slow mode the output freq
	 * is the parent one, the 24Mhz external oscillator
	 * if we are in deep mode the output freq is 32.768khz
	 */
	mode = (con4 & RK3399_CLK_PLL_MODE_MASK) >> RK3399_CLK_PLL_MODE_SHIFT;
	if (mode == RK3399_CLK_PLL_MODE_SLOW) {
		dprintf("pll in slow mode, con4=%x\n", con4);
		return (0);
	} else if (mode == RK3399_CLK_PLL_MODE_DEEPSLOW) {
		dprintf("pll in deep slow, con4=%x\n", con4);
		*freq = 32768;
		return (0);
	}

	dprintf("con0: %x\n", con1);
	dprintf("con1: %x\n", con2);
	dprintf("con2: %x\n", con3);
	dprintf("con3: %x\n", con4);

	fbdiv = (con1 & RK3399_CLK_PLL_FBDIV_MASK)
	    >> RK3399_CLK_PLL_FBDIV_SHIFT;

	postdiv1 = (con2 & RK3399_CLK_PLL_POSTDIV1_MASK)
	    >> RK3399_CLK_PLL_POSTDIV1_SHIFT;
	postdiv2 = (con2 & RK3399_CLK_PLL_POSTDIV2_MASK)
	    >> RK3399_CLK_PLL_POSTDIV2_SHIFT;
	refdiv = (con2 & RK3399_CLK_PLL_REFDIV_MASK)
	    >> RK3399_CLK_PLL_REFDIV_SHIFT;

	fracdiv = (con3 & RK3399_CLK_PLL_FRAC_MASK)
	    >> RK3399_CLK_PLL_FRAC_SHIFT;
	fracdiv >>= 24;

	dsmpd = (con4 & RK3399_CLK_PLL_DSMPD_MASK) >> RK3399_CLK_PLL_DSMPD_SHIFT;

	dprintf("fbdiv: %d\n", fbdiv);
	dprintf("postdiv1: %d\n", postdiv1);
	dprintf("postdiv2: %d\n", postdiv2);
	dprintf("refdiv: %d\n", refdiv);
	dprintf("fracdiv: %d\n", fracdiv);
	dprintf("dsmpd: %d\n", dsmpd);

	dprintf("parent freq=%ju\n", *freq);

	if (dsmpd == 0) {
		/* Fractional mode */
		foutvco = *freq / refdiv * (fbdiv + fracdiv);
	} else {
		/* Integer mode */
		foutvco = *freq / refdiv * fbdiv;
	}
	dprintf("foutvco: %ju\n", foutvco);

	*freq = foutvco / postdiv1 / postdiv2;
	dprintf("freq: %ju\n", *freq);

	return (0);
}