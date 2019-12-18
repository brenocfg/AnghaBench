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
typedef  int uint32_t ;
struct jz4780_clk_gen_sc {TYPE_1__* clk_descr; } ;
struct clknode {int dummy; } ;
struct TYPE_2__ {scalar_t__ clk_gate_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_LOCK (struct jz4780_clk_gen_sc*) ; 
 int CLK_RD_4 (struct jz4780_clk_gen_sc*,int) ; 
 int /*<<< orphan*/  CLK_UNLOCK (struct jz4780_clk_gen_sc*) ; 
 int /*<<< orphan*/  CLK_WR_4 (struct jz4780_clk_gen_sc*,int,int) ; 
 int JZ_CLKGR0 ; 
 int JZ_CLKGR1 ; 
 struct jz4780_clk_gen_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
jz4780_clk_gen_set_gate(struct clknode *clk, bool enable)
{
	struct jz4780_clk_gen_sc *sc;
	uint32_t off, reg, bit;

	sc = clknode_get_softc(clk);

	/* Check is clock can be gated */
	if (sc->clk_descr->clk_gate_bit < 0)
		return 0;

	bit = sc->clk_descr->clk_gate_bit;
	if (bit < 32) {
		off = JZ_CLKGR0;
	} else {
		off = JZ_CLKGR1;
		bit -= 32;
	}

	CLK_LOCK(sc);
	reg = CLK_RD_4(sc, off);
	if (enable)
		reg &= ~(1u << bit);
	else
		reg |= (1u << bit);
	CLK_WR_4(sc, off, reg);
	CLK_UNLOCK(sc);

	return (0);
}