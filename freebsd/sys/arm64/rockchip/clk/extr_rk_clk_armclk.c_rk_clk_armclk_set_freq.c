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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct rk_clk_armclk_sc {size_t main_parent; int nrates; int div_shift; int div_mask; char* muxdiv_offset; TYPE_1__* rates; } ;
struct clknode {int dummy; } ;
struct TYPE_2__ {int freq; int div; } ;

/* Variables and functions */
 int CLK_SET_DRYRUN ; 
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int RK_ARMCLK_WRITE_MASK_SHIFT ; 
 int /*<<< orphan*/  WRITE4 (struct clknode*,char*,int) ; 
 struct clknode* clknode_find_by_name (char const*) ; 
 int /*<<< orphan*/  clknode_get_freq (struct clknode*,int*) ; 
 char* clknode_get_name (struct clknode*) ; 
 char** clknode_get_parent_names (struct clknode*) ; 
 struct rk_clk_armclk_sc* clknode_get_softc (struct clknode*) ; 
 int clknode_set_freq (struct clknode*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clknode_set_parent_by_idx (struct clknode*,size_t) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

__attribute__((used)) static int
rk_clk_armclk_set_freq(struct clknode *clk, uint64_t fparent, uint64_t *fout,
    int flags, int *stop)
{
	struct rk_clk_armclk_sc *sc;
	struct clknode *p_main;
	const char **p_names;
	uint64_t best = 0, best_p = 0;
	uint32_t div = 0, val = 0;
	int err, i, rate = 0;

	sc = clknode_get_softc(clk);

	dprintf("Finding best parent/div for target freq of %ju\n", *fout);
	p_names = clknode_get_parent_names(clk);
	p_main = clknode_find_by_name(p_names[sc->main_parent]);

	for (i = 0; i < sc->nrates; i++) {
		if (sc->rates[i].freq == *fout) {
			best = sc->rates[i].freq;
			div = sc->rates[i].div;
			best_p = best * div;
			rate = i;
			dprintf("Best parent %s (%d) with best freq at %ju\n",
			    clknode_get_name(p_main),
			    sc->main_parent,
			    best);
			break;
		}
	}

	if (rate == sc->nrates)
		return (0);

	if ((flags & CLK_SET_DRYRUN) != 0) {
		*fout = best;
		*stop = 1;
		return (0);
	}

	dprintf("Changing parent (%s) freq to %ju\n", clknode_get_name(p_main),
	    best_p);
	err = clknode_set_freq(p_main, best_p, 0, 1);
	if (err != 0)
		printf("Cannot set %s to %ju\n",
		    clknode_get_name(p_main),
		    best_p);

	clknode_set_parent_by_idx(clk, sc->main_parent);

	clknode_get_freq(p_main, &best_p);
	dprintf("main parent freq at %ju\n", best_p);
	DEVICE_LOCK(clk);
	val |= (div - 1) << sc->div_shift;
	val |= sc->div_mask << RK_ARMCLK_WRITE_MASK_SHIFT;
	dprintf("Write: muxdiv_offset=%x, val=%x\n", sc->muxdiv_offset, val);
	WRITE4(clk, sc->muxdiv_offset, val);
	DEVICE_UNLOCK(clk);

	*fout = best;
	*stop = 1;

	return (0);
}