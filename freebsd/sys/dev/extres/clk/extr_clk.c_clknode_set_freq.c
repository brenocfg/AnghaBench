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
struct clknode {int enable_cnt; int flags; scalar_t__ parent_cnt; char* name; struct clknode* parent; scalar_t__ freq; } ;

/* Variables and functions */
 int CLKNODE_SET_FREQ (struct clknode*,scalar_t__,scalar_t__*,int,int*) ; 
 int CLK_NODE_GLITCH_FREE ; 
 int CLK_SET_DRYRUN ; 
 int /*<<< orphan*/  CLK_TOPO_XASSERT () ; 
 int EBUSY ; 
 int ENXIO ; 
 int clknode_get_freq (struct clknode*,scalar_t__*) ; 
 int /*<<< orphan*/  clknode_refresh_cache (struct clknode*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

int
clknode_set_freq(struct clknode *clknode, uint64_t freq, int flags,
    int enablecnt)
{
	int rv, done;
	uint64_t parent_freq;

	/* We have exclusive topology lock, node lock is not needed. */
	CLK_TOPO_XASSERT();

	/* Check for no change */
	if (clknode->freq == freq)
		return (0);

	parent_freq = 0;

	/*
	 * We can set frequency only if
	 *   clock is disabled
	 * OR
	 *   clock is glitch free and is enabled by calling consumer only
	 */
	if ((flags & CLK_SET_DRYRUN) == 0 &&
	    clknode->enable_cnt > 1 &&
	    clknode->enable_cnt > enablecnt &&
	    (clknode->flags & CLK_NODE_GLITCH_FREE) == 0) {
		return (EBUSY);
	}

	/* Get frequency from parent, if the clock has a parent. */
	if (clknode->parent_cnt > 0) {
		rv = clknode_get_freq(clknode->parent, &parent_freq);
		if (rv != 0) {
			return (rv);
		}
	}

	/* Set frequency for this clock. */
	rv = CLKNODE_SET_FREQ(clknode, parent_freq, &freq, flags, &done);
	if (rv != 0) {
		printf("Cannot set frequency for clk: %s, error: %d\n",
		    clknode->name, rv);
		if ((flags & CLK_SET_DRYRUN) == 0)
			clknode_refresh_cache(clknode, parent_freq);
		return (rv);
	}

	if (done) {
		/* Success - invalidate frequency cache for all children. */
		if ((flags & CLK_SET_DRYRUN) == 0) {
			clknode->freq = freq;
			/* Clock might have reparent during set_freq */
			if (clknode->parent_cnt > 0) {
				rv = clknode_get_freq(clknode->parent,
				    &parent_freq);
				if (rv != 0) {
					return (rv);
				}
			}
			clknode_refresh_cache(clknode, parent_freq);
		}
	} else if (clknode->parent != NULL) {
		/* Nothing changed, pass request to parent. */
		rv = clknode_set_freq(clknode->parent, freq, flags, enablecnt);
	} else {
		/* End of chain without action. */
		printf("Cannot set frequency for clk: %s, end of chain\n",
		    clknode->name);
		rv = ENXIO;
	}

	return (rv);
}