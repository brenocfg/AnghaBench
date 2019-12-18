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
struct rk_clk_pll_sc {int mode_shift; scalar_t__ mode_reg; scalar_t__ base_offset; struct rk_clk_pll_rate* frac_rates; struct rk_clk_pll_rate* rates; } ;
struct rk_clk_pll_rate {scalar_t__ freq; int postdiv1; int fbdiv; int dsmpd; int postdiv2; int refdiv; int frac; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  READ4 (struct clknode*,scalar_t__,int*) ; 
 int RK3328_CLK_PLL_DSMPD_MASK ; 
 int RK3328_CLK_PLL_DSMPD_SHIFT ; 
 int RK3328_CLK_PLL_FBDIV_MASK ; 
 int RK3328_CLK_PLL_FBDIV_SHIFT ; 
 int RK3328_CLK_PLL_FRAC_MASK ; 
 int RK3328_CLK_PLL_FRAC_SHIFT ; 
 int RK3328_CLK_PLL_LOCK_MASK ; 
 int RK3328_CLK_PLL_MODE_MASK ; 
 int RK3328_CLK_PLL_MODE_NORMAL ; 
 int RK3328_CLK_PLL_POSTDIV1_MASK ; 
 int RK3328_CLK_PLL_POSTDIV1_SHIFT ; 
 int RK3328_CLK_PLL_POSTDIV2_MASK ; 
 int RK3328_CLK_PLL_POSTDIV2_SHIFT ; 
 int RK3328_CLK_PLL_REFDIV_MASK ; 
 int RK3328_CLK_PLL_REFDIV_SHIFT ; 
 int RK_CLK_PLL_MASK_SHIFT ; 
 int /*<<< orphan*/  WRITE4 (struct clknode*,scalar_t__,int) ; 
 struct rk_clk_pll_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  dprintf (char*,int) ; 

__attribute__((used)) static int
rk3328_clk_pll_set_freq(struct clknode *clk, uint64_t fparent, uint64_t *fout,
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

	/* Setting to slow mode during frequency change */
	reg = (RK3328_CLK_PLL_MODE_MASK << sc->mode_shift) <<
		RK_CLK_PLL_MASK_SHIFT;
	dprintf("Set PLL_MODEREG to %x\n", reg);
	WRITE4(clk, sc->mode_reg, reg);

	/* Setting postdiv1 and fbdiv */
	reg = (rates->postdiv1 << RK3328_CLK_PLL_POSTDIV1_SHIFT) |
		(rates->fbdiv << RK3328_CLK_PLL_FBDIV_SHIFT);
	reg |= (RK3328_CLK_PLL_POSTDIV1_MASK | RK3328_CLK_PLL_FBDIV_MASK) << 16;
	dprintf("Set PLL_CON0 to %x\n", reg);
	WRITE4(clk, sc->base_offset, reg);

	/* Setting dsmpd, postdiv2 and refdiv */
	reg = (rates->dsmpd << RK3328_CLK_PLL_DSMPD_SHIFT) |
		(rates->postdiv2 << RK3328_CLK_PLL_POSTDIV2_SHIFT) |
		(rates->refdiv << RK3328_CLK_PLL_REFDIV_SHIFT);
	reg |= (RK3328_CLK_PLL_DSMPD_MASK |
	    RK3328_CLK_PLL_POSTDIV2_MASK |
	    RK3328_CLK_PLL_REFDIV_MASK) << RK_CLK_PLL_MASK_SHIFT;
	dprintf("Set PLL_CON1 to %x\n", reg);
	WRITE4(clk, sc->base_offset + 0x4, reg);

	/* Setting frac */
	READ4(clk, sc->base_offset + 0x8, &reg);
	reg &= ~RK3328_CLK_PLL_FRAC_MASK;
	reg |= rates->frac << RK3328_CLK_PLL_FRAC_SHIFT;
	dprintf("Set PLL_CON2 to %x\n", reg);
	WRITE4(clk, sc->base_offset + 0x8, reg);

	/* Reading lock */
	for (timeout = 1000; timeout; timeout--) {
		READ4(clk, sc->base_offset + 0x4, &reg);
		if ((reg & RK3328_CLK_PLL_LOCK_MASK) == 0)
			break;
		DELAY(1);
	}

	/* Set back to normal mode */
	reg = (RK3328_CLK_PLL_MODE_NORMAL << sc->mode_shift);
	reg |= (RK3328_CLK_PLL_MODE_MASK << sc->mode_shift) <<
		RK_CLK_PLL_MASK_SHIFT;
	dprintf("Set PLL_MODEREG to %x\n", reg);
	WRITE4(clk, sc->mode_reg, reg);

	DEVICE_UNLOCK(clk);

	*stop = 1;
	return (0);
}