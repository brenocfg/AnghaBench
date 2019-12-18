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
typedef  scalar_t__ u32 ;
struct clk_regmap_mux_div {scalar_t__* parent_map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 char* clk_hw_get_name (struct clk_hw*) ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 
 unsigned long mult_frac (unsigned long,int,scalar_t__) ; 
 int /*<<< orphan*/  mux_div_get_src_div (struct clk_regmap_mux_div*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,scalar_t__) ; 
 struct clk_regmap_mux_div* to_clk_regmap_mux_div (struct clk_hw*) ; 

__attribute__((used)) static unsigned long mux_div_recalc_rate(struct clk_hw *hw, unsigned long prate)
{
	struct clk_regmap_mux_div *md = to_clk_regmap_mux_div(hw);
	u32 div, src;
	int i, num_parents = clk_hw_get_num_parents(hw);
	const char *name = clk_hw_get_name(hw);

	mux_div_get_src_div(md, &src, &div);
	for (i = 0; i < num_parents; i++)
		if (src == md->parent_map[i]) {
			struct clk_hw *p = clk_hw_get_parent_by_index(hw, i);
			unsigned long parent_rate = clk_hw_get_rate(p);

			return mult_frac(parent_rate, 2, div + 1);
		}

	pr_err("%s: Can't find parent %d\n", name, src);
	return 0;
}