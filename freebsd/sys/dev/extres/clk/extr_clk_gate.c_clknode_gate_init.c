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
struct clknode_gate_sc {int shift; int mask; int ungated; int on_value; int /*<<< orphan*/  offset; } ;
struct clknode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int RD4 (struct clknode*,int /*<<< orphan*/ ,int*) ; 
 struct clknode_gate_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_init_parent_idx (struct clknode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
clknode_gate_init(struct clknode *clk, device_t dev)
{
	uint32_t reg;
	struct clknode_gate_sc *sc;
	int rv;

	sc = clknode_get_softc(clk);
	DEVICE_LOCK(clk);
	rv = RD4(clk, sc->offset, &reg);
	DEVICE_UNLOCK(clk);
	if (rv != 0)
		return (rv);
	reg = (reg >> sc->shift) & sc->mask;
	sc->ungated = reg == sc->on_value ? 1 : 0;
	clknode_init_parent_idx(clk, 0);
	return(0);
}