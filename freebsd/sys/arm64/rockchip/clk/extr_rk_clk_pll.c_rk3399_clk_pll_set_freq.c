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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct rk_clk_pll_sc {scalar_t__ base_offset; struct rk_clk_pll_rate* frac_rates; struct rk_clk_pll_rate* rates; } ;
struct rk_clk_pll_rate {scalar_t__ freq; int fbdiv; int postdiv1; int postdiv2; int refdiv; int frac; int dsmpd; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  READ4 (struct clknode*,scalar_t__,int*) ; 
 int RK3399_CLK_PLL_DSMPD_MASK ; 
 int RK3399_CLK_PLL_DSMPD_SHIFT ; 
 int RK3399_CLK_PLL_FBDIV_MASK ; 
 int RK3399_CLK_PLL_FBDIV_SHIFT ; 
 int RK3399_CLK_PLL_FRAC_MASK ; 
 int RK3399_CLK_PLL_FRAC_SHIFT ; 
 int RK3399_CLK_PLL_LOCK_MASK ; 
 scalar_t__ RK3399_CLK_PLL_LOCK_OFFSET ; 
 int RK3399_CLK_PLL_MODE_MASK ; 
 int RK3399_CLK_PLL_MODE_NORMAL ; 
 int RK3399_CLK_PLL_MODE_SHIFT ; 
 int RK3399_CLK_PLL_MODE_SLOW ; 
 int RK3399_CLK_PLL_POSTDIV1_MASK ; 
 int RK3399_CLK_PLL_POSTDIV1_SHIFT ; 
 int RK3399_CLK_PLL_POSTDIV2_MASK ; 
 int RK3399_CLK_PLL_POSTDIV2_SHIFT ; 
 int RK3399_CLK_PLL_REFDIV_MASK ; 
 int RK3399_CLK_PLL_REFDIV_SHIFT ; 
 int RK3399_CLK_PLL_WRITE_MASK ; 
 int RK_CLK_PLL_MASK_SHIFT ; 
 int /*<<< orphan*/  WRITE4 (struct clknode*,scalar_t__,int) ; 
 struct rk_clk_pll_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
rk3399_clk_pll_set_freq(struct clknode *clk, uint64_t fparent, uint64_t *fout,
    int flags, int *stop)
{
	struct rk_clk_pll_rate *rates;
	struct rk_clk_pll_sc *sc;
	uint32_t reg;
	int timeout;

	sc = clknode_get_softc(clk);

	if (sc->rates)
		rates = sc->rates;
	else if (sc->frac_rates)
		rates = sc->frac_rates;
	else
		return (EINVAL);

	for (; rates->freq; rates++) {
		if (rates->freq == *fout)
			break;
	}
	if (rates->freq == 0) {
		*stop = 1;
		return (EINVAL);
	}

	DEVICE_LOCK(clk);

	/* Set to slow mode during frequency change */
	reg = RK3399_CLK_PLL_MODE_SLOW << RK3399_CLK_PLL_MODE_SHIFT;
	reg |= RK3399_CLK_PLL_MODE_MASK << RK_CLK_PLL_MASK_SHIFT;
	WRITE4(clk, sc->base_offset + 0xC, reg);

	/* Setting fbdiv */
	reg = rates->fbdiv << RK3399_CLK_PLL_FBDIV_SHIFT;
	reg |= RK3399_CLK_PLL_FBDIV_MASK << RK_CLK_PLL_MASK_SHIFT;
	WRITE4(clk, sc->base_offset, reg);

	/* Setting postdiv1, postdiv2 and refdiv */
	reg = rates->postdiv1 << RK3399_CLK_PLL_POSTDIV1_SHIFT;
	reg |= rates->postdiv2 << RK3399_CLK_PLL_POSTDIV2_SHIFT;
	reg |= rates->refdiv << RK3399_CLK_PLL_REFDIV_SHIFT;
	reg |= (RK3399_CLK_PLL_POSTDIV1_MASK | RK3399_CLK_PLL_POSTDIV2_MASK |
	    RK3399_CLK_PLL_REFDIV_MASK) << RK_CLK_PLL_MASK_SHIFT;
	WRITE4(clk, sc->base_offset + 0x4, reg);

	/* Setting frac */
	READ4(clk, sc->base_offset + 0x8, &reg);
	reg &= ~RK3399_CLK_PLL_FRAC_MASK;
	reg |= rates->frac << RK3399_CLK_PLL_FRAC_SHIFT;
	WRITE4(clk, sc->base_offset + 0x8, reg | RK3399_CLK_PLL_WRITE_MASK);

	/* Set dsmpd */
	reg = rates->dsmpd << RK3399_CLK_PLL_DSMPD_SHIFT;
	reg |= RK3399_CLK_PLL_DSMPD_MASK << RK_CLK_PLL_MASK_SHIFT;
	WRITE4(clk, sc->base_offset + 0xC, reg);

	/* Reading lock */
	for (timeout = 1000; timeout; timeout--) {
		READ4(clk, sc->base_offset + RK3399_CLK_PLL_LOCK_OFFSET, &reg);
		if ((reg & RK3399_CLK_PLL_LOCK_MASK) == 0)
			break;
		DELAY(1);
	}

	/* Set back to normal mode */
	reg = RK3399_CLK_PLL_MODE_NORMAL << RK3399_CLK_PLL_MODE_SHIFT;
	reg |= RK3399_CLK_PLL_MODE_MASK << RK_CLK_PLL_MASK_SHIFT;
	WRITE4(clk, sc->base_offset + 0xC, reg);

	DEVICE_UNLOCK(clk);

	*stop = 1;
	return (0);
}