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
struct meson_clk_dualdiv_param {void* m2; void* n2; void* m1; void* n1; void* dual; } ;
struct meson_clk_dualdiv_data {int /*<<< orphan*/  m2; int /*<<< orphan*/  n2; int /*<<< orphan*/  m1; int /*<<< orphan*/  n1; int /*<<< orphan*/  dual; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long __dualdiv_param_to_rate (unsigned long,struct meson_clk_dualdiv_param*) ; 
 struct meson_clk_dualdiv_data* meson_clk_dualdiv_data (struct clk_regmap*) ; 
 void* meson_parm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static unsigned long meson_clk_dualdiv_recalc_rate(struct clk_hw *hw,
						   unsigned long parent_rate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_dualdiv_data *dualdiv = meson_clk_dualdiv_data(clk);
	struct meson_clk_dualdiv_param setting;

	setting.dual = meson_parm_read(clk->map, &dualdiv->dual);
	setting.n1 = meson_parm_read(clk->map, &dualdiv->n1) + 1;
	setting.m1 = meson_parm_read(clk->map, &dualdiv->m1) + 1;
	setting.n2 = meson_parm_read(clk->map, &dualdiv->n2) + 1;
	setting.m2 = meson_parm_read(clk->map, &dualdiv->m2) + 1;

	return __dualdiv_param_to_rate(parent_rate, &setting);
}