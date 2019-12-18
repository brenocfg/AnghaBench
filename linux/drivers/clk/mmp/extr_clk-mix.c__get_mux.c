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
struct mmp_clk_mix {int mux_flags; unsigned int* mux_table; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int CLK_MUX_INDEX_BIT ; 
 int CLK_MUX_INDEX_ONE ; 
 int clk_hw_get_num_parents (int /*<<< orphan*/ *) ; 
 unsigned int ffs (unsigned int) ; 

__attribute__((used)) static unsigned int _get_mux(struct mmp_clk_mix *mix, unsigned int val)
{
	int num_parents = clk_hw_get_num_parents(&mix->hw);
	int i;

	if (mix->mux_flags & CLK_MUX_INDEX_BIT)
		return ffs(val) - 1;
	if (mix->mux_flags & CLK_MUX_INDEX_ONE)
		return val - 1;
	if (mix->mux_table) {
		for (i = 0; i < num_parents; i++)
			if (mix->mux_table[i] == val)
				return i;
		if (i == num_parents)
			return 0;
	}

	return val;
}