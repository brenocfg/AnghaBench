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
struct clknode_gate_sc {int ungated; int mask; int shift; int on_value; int off_value; int /*<<< orphan*/  offset; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int MD4 (struct clknode*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RD4 (struct clknode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clknode_gate_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
clknode_gate_set_gate(struct clknode *clk, bool enable)
{
	uint32_t reg;
	struct clknode_gate_sc *sc;
	int rv;

	sc = clknode_get_softc(clk);
	sc->ungated = enable;
	DEVICE_LOCK(clk);
	rv = MD4(clk, sc->offset, sc->mask << sc->shift,
	    (sc->ungated ? sc->on_value : sc->off_value) << sc->shift);
	if (rv != 0) {
		DEVICE_UNLOCK(clk);
		return (rv);
	}
	RD4(clk, sc->offset, &reg);
	DEVICE_UNLOCK(clk);
	return(0);
}