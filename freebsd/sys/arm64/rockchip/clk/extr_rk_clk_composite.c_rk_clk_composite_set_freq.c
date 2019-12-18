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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct rk_clk_composite_sc {scalar_t__ div_mask; scalar_t__ div_shift; scalar_t__ muxdiv_offset; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int CLK_SET_DRYRUN ; 
 int CLK_SET_ROUND_DOWN ; 
 int CLK_SET_ROUND_UP ; 
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int ERANGE ; 
 scalar_t__ RK_CLK_COMPOSITE_MASK_SHIFT ; 
 int /*<<< orphan*/  WRITE4 (struct clknode*,scalar_t__,scalar_t__) ; 
 struct clknode* clknode_find_by_name (char const*) ; 
 int /*<<< orphan*/  clknode_get_freq (struct clknode*,scalar_t__*) ; 
 int /*<<< orphan*/  clknode_get_name (struct clknode*) ; 
 int clknode_get_parent_idx (struct clknode*) ; 
 char** clknode_get_parent_names (struct clknode*) ; 
 int clknode_get_parents_num (struct clknode*) ; 
 struct rk_clk_composite_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_set_parent_by_idx (struct clknode*,int) ; 
 int /*<<< orphan*/  dprintf (char*,scalar_t__,...) ; 
 scalar_t__ rk_clk_composite_find_best (struct rk_clk_composite_sc*,scalar_t__,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int
rk_clk_composite_set_freq(struct clknode *clk, uint64_t fparent, uint64_t *fout,
    int flags, int *stop)
{
	struct rk_clk_composite_sc *sc;
	struct clknode *p_clk;
	const char **p_names;
	uint64_t best, cur;
	uint32_t div, div_reg, best_div, best_div_reg, val;
	int p_idx, best_parent;

	sc = clknode_get_softc(clk);
	dprintf("Finding best parent/div for target freq of %ju\n", *fout);
	p_names = clknode_get_parent_names(clk);
	for (best_div = 0, best = 0, p_idx = 0;
	     p_idx != clknode_get_parents_num(clk); p_idx++) {
		p_clk = clknode_find_by_name(p_names[p_idx]);
		clknode_get_freq(p_clk, &fparent);
		dprintf("Testing with parent %s (%d) at freq %ju\n",
		    clknode_get_name(p_clk), p_idx, fparent);
		div = rk_clk_composite_find_best(sc, fparent, *fout, &div_reg);
		cur = fparent / div;
		if ((*fout - cur) < (*fout - best)) {
			best = cur;
			best_div = div;
			best_div_reg = div_reg;
			best_parent = p_idx;
			dprintf("Best parent so far %s (%d) with best freq at "
			    "%ju\n", clknode_get_name(p_clk), p_idx, best);
		}
	}

	*stop = 1;
	if (best_div == 0)
		return (ERANGE);

	if ((best < *fout) && ((flags & CLK_SET_ROUND_DOWN) == 0))
		return (ERANGE);

	if ((best > *fout) && ((flags & CLK_SET_ROUND_UP) == 0)) {
		return (ERANGE);
	}

	if ((flags & CLK_SET_DRYRUN) != 0) {
		*fout = best;
		return (0);
	}

	p_idx = clknode_get_parent_idx(clk);
	if (p_idx != best_parent) {
		dprintf("Switching parent index from %d to %d\n", p_idx,
		    best_parent);
		clknode_set_parent_by_idx(clk, best_parent);
	}

	dprintf("Setting divider to %d (reg: %d)\n", best_div, best_div_reg);
	dprintf(" div_mask: 0x%X, div_shift: %d\n", sc->div_mask,
	    sc->div_shift);

	DEVICE_LOCK(clk);
	val = best_div_reg << sc->div_shift;
	val |= sc->div_mask << RK_CLK_COMPOSITE_MASK_SHIFT;
	dprintf("Write: muxdiv_offset=%x, val=%x\n", sc->muxdiv_offset, val);
	WRITE4(clk, sc->muxdiv_offset, val);
	DEVICE_UNLOCK(clk);

	*fout = best;
	return (0);
}