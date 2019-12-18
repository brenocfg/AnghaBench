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
struct m10v_clk_div_fixed_data {char const* parent_name; size_t onecell_idx; int /*<<< orphan*/  div; int /*<<< orphan*/  mult; int /*<<< orphan*/  name; } ;
struct clk_hw_onecell_data {struct clk_hw** hws; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_hw* clk_hw_register_fixed_factor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m10v_reg_fixed_pre(const struct m10v_clk_div_fixed_data *factors,
			       struct clk_hw_onecell_data *clk_data,
			       const char *parent_name)
{
	struct clk_hw *hw;
	const char *pn = factors->parent_name ?
				factors->parent_name : parent_name;

	hw = clk_hw_register_fixed_factor(NULL, factors->name, pn, 0,
					  factors->mult, factors->div);

	if (factors->onecell_idx >= 0)
		clk_data->hws[factors->onecell_idx] = hw;
}