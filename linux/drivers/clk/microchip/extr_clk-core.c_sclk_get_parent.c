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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct pic32_sys_clk {size_t* parent_map; int /*<<< orphan*/  mux_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t OSC_CUR_MASK ; 
 size_t OSC_CUR_SHIFT ; 
 size_t clk_hw_get_num_parents (struct clk_hw*) ; 
 struct pic32_sys_clk* clkhw_to_sys_clk (struct clk_hw*) ; 
 size_t readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 sclk_get_parent(struct clk_hw *hw)
{
	struct pic32_sys_clk *sclk = clkhw_to_sys_clk(hw);
	u32 i, v;

	v = (readl(sclk->mux_reg) >> OSC_CUR_SHIFT) & OSC_CUR_MASK;

	if (!sclk->parent_map)
		return v;

	for (i = 0; i < clk_hw_get_num_parents(hw); i++)
		if (sclk->parent_map[i] == v)
			return i;
	return -EINVAL;
}