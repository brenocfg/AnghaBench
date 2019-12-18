#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct jz4780_clk_gen_sc {TYPE_2__* clk_descr; } ;
struct clknode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {unsigned int mux_bits; int mux_shift; int /*<<< orphan*/  mux_map; int /*<<< orphan*/  mux_reg; } ;
struct TYPE_4__ {int clk_type; TYPE_1__ clk_mux; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_LOCK (struct jz4780_clk_gen_sc*) ; 
 int CLK_MASK_MUX ; 
 int CLK_RD_4 (struct jz4780_clk_gen_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_UNLOCK (struct jz4780_clk_gen_sc*) ; 
 struct jz4780_clk_gen_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_init_parent_idx (struct clknode*,int) ; 
 int reg_to_mux (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_clk_gen_init(struct clknode *clk, device_t dev)
{
	struct jz4780_clk_gen_sc *sc;
	uint32_t reg, msk, parent_idx;

	sc = clknode_get_softc(clk);
	CLK_LOCK(sc);
	/* Figure our parent out */
	if (sc->clk_descr->clk_type & CLK_MASK_MUX) {
		msk = (1u << sc->clk_descr->clk_mux.mux_bits) - 1;
		reg = CLK_RD_4(sc, sc->clk_descr->clk_mux.mux_reg);
		reg = (reg >> sc->clk_descr->clk_mux.mux_shift) & msk;
		parent_idx = reg_to_mux(reg, sc->clk_descr->clk_mux.mux_map);
	} else
		parent_idx = 0;
	CLK_UNLOCK(sc);

	clknode_init_parent_idx(clk, parent_idx);
	return (0);
}