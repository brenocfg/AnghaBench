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
typedef  int /*<<< orphan*/  uint32_t ;
struct rk_clk_mux_sc {int mask; int shift; int /*<<< orphan*/  offset; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int MD4 (struct clknode*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RD4 (struct clknode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RK_CLK_MUX_MASK ; 
 struct rk_clk_mux_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
rk_clk_mux_set_mux(struct clknode *clk, int idx)
{
	uint32_t reg;
	struct rk_clk_mux_sc *sc;
	int rv;

	sc = clknode_get_softc(clk);

	DEVICE_LOCK(clk);
	rv = MD4(clk, sc->offset, sc->mask << sc->shift,
	    ((idx & sc->mask) << sc->shift) | RK_CLK_MUX_MASK);
	if (rv != 0) {
		DEVICE_UNLOCK(clk);
		return (rv);
	}
	RD4(clk, sc->offset, &reg);
	DEVICE_UNLOCK(clk);

	return(0);
}