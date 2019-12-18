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
struct rk_clk_armclk_sc {int mux_shift; int mux_mask; int /*<<< orphan*/  muxdiv_offset; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int RK_ARMCLK_WRITE_MASK_SHIFT ; 
 int /*<<< orphan*/  WRITE4 (struct clknode*,int /*<<< orphan*/ ,int) ; 
 struct rk_clk_armclk_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  dprintf (char*,int,...) ; 

__attribute__((used)) static int
rk_clk_armclk_set_mux(struct clknode *clk, int index)
{
	struct rk_clk_armclk_sc *sc;
	uint32_t val = 0;

	sc = clknode_get_softc(clk);

	dprintf("Set mux to %d\n", index);
	DEVICE_LOCK(clk);
	val |= index << sc->mux_shift;
	val |= sc->mux_mask << RK_ARMCLK_WRITE_MASK_SHIFT;
	dprintf("Write: muxdiv_offset=%x, val=%x\n", sc->muxdiv_offset, val);
	WRITE4(clk, sc->muxdiv_offset, val);
	DEVICE_UNLOCK(clk);

	return (0);
}