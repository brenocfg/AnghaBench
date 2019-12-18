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
typedef  int uint32_t ;
struct pll_sc {int lock_enable; scalar_t__ type; int /*<<< orphan*/  misc_reg; int /*<<< orphan*/  base_reg; } ;
struct clknode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PLL_BASE_ENABLE ; 
 scalar_t__ PLL_REFE ; 
 int /*<<< orphan*/  RD4 (struct pll_sc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  WR4 (struct pll_sc*,int /*<<< orphan*/ ,int) ; 
 struct pll_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_init_parent_idx (struct clknode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra124_pll_init(struct clknode *clk, device_t dev)
{
	struct pll_sc *sc;
	uint32_t reg;

	sc = clknode_get_softc(clk);

	/* If PLL is enabled, enable lock detect too. */
	RD4(sc, sc->base_reg, &reg);
	if (reg & PLL_BASE_ENABLE) {
		RD4(sc, sc->misc_reg, &reg);
		reg |= sc->lock_enable;
		WR4(sc, sc->misc_reg, reg);
	}
	if (sc->type == PLL_REFE) {
		RD4(sc, sc->misc_reg, &reg);
		reg &= ~(1 << 29);	/* Diasble lock override */
		WR4(sc, sc->misc_reg, reg);
	}

	clknode_init_parent_idx(clk, 0);
	return(0);
}