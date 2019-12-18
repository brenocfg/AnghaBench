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
struct div6_clock {int src_shift; size_t* parents; int /*<<< orphan*/  reg; int /*<<< orphan*/  src_width; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 size_t clk_hw_get_num_parents (struct clk_hw*) ; 
 size_t readl (int /*<<< orphan*/ ) ; 
 struct div6_clock* to_div6_clock (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpg_div6_clock_set_parent(struct clk_hw *hw, u8 index)
{
	struct div6_clock *clock = to_div6_clock(hw);
	u8 hw_index;
	u32 mask;

	if (index >= clk_hw_get_num_parents(hw))
		return -EINVAL;

	mask = ~((BIT(clock->src_width) - 1) << clock->src_shift);
	hw_index = clock->parents[index];

	writel((readl(clock->reg) & mask) | (hw_index << clock->src_shift),
	       clock->reg);

	return 0;
}