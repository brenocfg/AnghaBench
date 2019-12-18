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
struct clknode_div_sc {int i_shift; int i_mask; int div_flags; int f_shift; int f_mask; int divider; int f_width; int /*<<< orphan*/  offset; } ;
struct clknode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CLK_DIV_ZERO_BASED ; 
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int RD4 (struct clknode*,int /*<<< orphan*/ ,int*) ; 
 int clknode_div_table_get_divider (struct clknode_div_sc*,int) ; 
 int /*<<< orphan*/  clknode_get_name (struct clknode*) ; 
 struct clknode_div_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_init_parent_idx (struct clknode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
clknode_div_init(struct clknode *clk, device_t dev)
{
	uint32_t reg;
	struct clknode_div_sc *sc;
	uint32_t i_div, f_div;
	int rv;

	sc = clknode_get_softc(clk);

	DEVICE_LOCK(clk);
	rv = RD4(clk, sc->offset, &reg);
	DEVICE_UNLOCK(clk);
	if (rv != 0)
		return (rv);

	i_div = (reg >> sc->i_shift) & sc->i_mask;
	if (!(sc->div_flags & CLK_DIV_ZERO_BASED))
		i_div++;
	f_div = (reg >> sc->f_shift) & sc->f_mask;
	sc->divider = i_div << sc->f_width | f_div;

	sc->divider = clknode_div_table_get_divider(sc, sc->divider);
	if (sc->divider == 0)
		panic("%s: divider is zero!\n", clknode_get_name(clk));

	clknode_init_parent_idx(clk, 0);
	return(0);
}