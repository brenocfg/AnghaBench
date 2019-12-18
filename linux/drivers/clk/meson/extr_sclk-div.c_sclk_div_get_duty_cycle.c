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
struct meson_sclk_div_data {int cached_div; int /*<<< orphan*/  hi; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;
struct clk_duty {int num; int den; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_PARM_APPLICABLE (int /*<<< orphan*/ *) ; 
 int meson_parm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct meson_sclk_div_data* meson_sclk_div_data (struct clk_regmap*) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static int sclk_div_get_duty_cycle(struct clk_hw *hw,
				   struct clk_duty *duty)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_sclk_div_data *sclk = meson_sclk_div_data(clk);
	int hi;

	if (!MESON_PARM_APPLICABLE(&sclk->hi)) {
		duty->num = 1;
		duty->den = 2;
		return 0;
	}

	hi = meson_parm_read(clk->map, &sclk->hi);
	duty->num = hi + 1;
	duty->den = sclk->cached_div;
	return 0;
}