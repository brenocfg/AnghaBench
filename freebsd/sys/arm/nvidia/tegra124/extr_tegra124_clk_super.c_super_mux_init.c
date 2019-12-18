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
struct super_mux_sc {int mux; int flags; int src_pllx; int src_div2; int /*<<< orphan*/  base_reg; } ;
struct clknode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_LOCK (struct super_mux_sc*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct super_mux_sc*) ; 
 int /*<<< orphan*/  RD4 (struct super_mux_sc*,int /*<<< orphan*/ ,int*) ; 
 int SMF_HAVE_DIVIDER_2 ; 
 int SUPER_MUX_LP_DIV2_BYPASS ; 
 int SUPER_MUX_MUX_WIDTH ; 
 int SUPER_MUX_STATE_IDLE ; 
 int SUPER_MUX_STATE_RUN ; 
 struct super_mux_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_init_parent_idx (struct clknode*,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int super_mux_get_state (int) ; 

__attribute__((used)) static int
super_mux_init(struct clknode *clk, device_t dev)
{
	struct super_mux_sc *sc;
	uint32_t reg;
	int shift, state;

	sc = clknode_get_softc(clk);

	DEVICE_LOCK(sc);
	RD4(sc, sc->base_reg, &reg);
	DEVICE_UNLOCK(sc);
	state = super_mux_get_state(reg);

	if ((state != SUPER_MUX_STATE_RUN) &&
	    (state != SUPER_MUX_STATE_IDLE)) {
		panic("Unexpected super mux state: %u", state);
	}

	shift = state * SUPER_MUX_MUX_WIDTH;

	sc->mux = (reg >> shift) & ((1 << SUPER_MUX_MUX_WIDTH) - 1);

	/*
	 * CCLKLP uses PLLX/2 as source if LP_DIV2_BYPASS isn't set
	 * and source mux is set to PLLX.
	 */
	if (sc->flags & SMF_HAVE_DIVIDER_2) {
		if (((reg & SUPER_MUX_LP_DIV2_BYPASS) == 0) &&
		    (sc->mux == sc->src_pllx))
		sc->mux = sc->src_div2;
	}
	clknode_init_parent_idx(clk, sc->mux);

	return(0);
}