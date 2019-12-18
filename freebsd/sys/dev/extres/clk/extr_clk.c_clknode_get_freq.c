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
typedef  int /*<<< orphan*/  uint64_t ;
struct clknode {scalar_t__ parent_cnt; char* name; int /*<<< orphan*/  freq; struct clknode* parent; } ;

/* Variables and functions */
 int CLKNODE_RECALC_FREQ (struct clknode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLKNODE_UNLOCK (struct clknode*) ; 
 int /*<<< orphan*/  CLKNODE_XLOCK (struct clknode*) ; 
 int /*<<< orphan*/  CLK_TOPO_ASSERT () ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

int
clknode_get_freq(struct clknode *clknode, uint64_t *freq)
{
	int rv;

	CLK_TOPO_ASSERT();

	/* Use cached value, if it exists. */
	*freq  = clknode->freq;
	if (*freq != 0)
		return (0);

	/* Get frequency from parent, if the clock has a parent. */
	if (clknode->parent_cnt > 0) {
		rv = clknode_get_freq(clknode->parent, freq);
		if (rv != 0) {
			return (rv);
		}
	}

	/* And recalculate my output frequency. */
	CLKNODE_XLOCK(clknode);
	rv = CLKNODE_RECALC_FREQ(clknode, freq);
	if (rv != 0) {
		CLKNODE_UNLOCK(clknode);
		printf("Cannot get frequency for clk: %s, error: %d\n",
		    clknode->name, rv);
		return (rv);
	}

	/* Save new frequency to cache. */
	clknode->freq = *freq;
	CLKNODE_UNLOCK(clknode);
	return (0);
}