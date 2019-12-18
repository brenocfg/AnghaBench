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
typedef  unsigned int u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int CLK_MUX_INDEX_BIT ; 
 unsigned int CLK_MUX_INDEX_ONE ; 
 int EINVAL ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 int ffs (unsigned int) ; 

int clk_mux_val_to_index(struct clk_hw *hw, u32 *table, unsigned int flags,
			 unsigned int val)
{
	int num_parents = clk_hw_get_num_parents(hw);

	if (table) {
		int i;

		for (i = 0; i < num_parents; i++)
			if (table[i] == val)
				return i;
		return -EINVAL;
	}

	if (val && (flags & CLK_MUX_INDEX_BIT))
		val = ffs(val) - 1;

	if (val && (flags & CLK_MUX_INDEX_ONE))
		val--;

	if (val >= num_parents)
		return -EINVAL;

	return val;
}