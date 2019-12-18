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
struct rk_clk_composite_sc {int div_mask; int div_shift; int flags; int /*<<< orphan*/  muxdiv_offset; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int /*<<< orphan*/  READ4 (struct clknode*,int /*<<< orphan*/ ,int*) ; 
 int RK_CLK_COMPOSITE_DIV_EXP ; 
 struct rk_clk_composite_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  dprintf (char*,int,...) ; 

__attribute__((used)) static int
rk_clk_composite_recalc(struct clknode *clk, uint64_t *freq)
{
	struct rk_clk_composite_sc *sc;
	uint32_t reg, div;

	sc = clknode_get_softc(clk);

	DEVICE_LOCK(clk);

	READ4(clk, sc->muxdiv_offset, &reg);
	dprintf("Read: muxdiv_offset=%x, val=%x\n", sc->muxdiv_offset, reg);

	DEVICE_UNLOCK(clk);

	div = ((reg & sc->div_mask) >> sc->div_shift);
	if (sc->flags & RK_CLK_COMPOSITE_DIV_EXP)
		div = 1 << div;
	else
		div += 1;
	dprintf("parent_freq=%ju, div=%u\n", *freq, div);
	*freq = *freq / div;
	dprintf("Final freq=%ju\n", *freq);
	return (0);
}