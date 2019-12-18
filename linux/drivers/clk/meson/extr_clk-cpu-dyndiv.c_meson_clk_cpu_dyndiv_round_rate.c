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
struct TYPE_2__ {int /*<<< orphan*/  width; } ;
struct meson_clk_cpu_dyndiv_data {TYPE_1__ div; } ;
struct clk_regmap {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long divider_round_rate (struct clk_hw*,unsigned long,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct meson_clk_cpu_dyndiv_data* meson_clk_cpu_dyndiv_data (struct clk_regmap*) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static long meson_clk_cpu_dyndiv_round_rate(struct clk_hw *hw,
					    unsigned long rate,
					    unsigned long *prate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_cpu_dyndiv_data *data = meson_clk_cpu_dyndiv_data(clk);

	return divider_round_rate(hw, rate, prate, NULL, data->div.width, 0);
}