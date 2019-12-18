#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int shift; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {unsigned int shift; int /*<<< orphan*/  width; int /*<<< orphan*/  reg_off; } ;
struct meson_clk_cpu_dyndiv_data {TYPE_2__ dyn; TYPE_1__ div; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int SETPMASK (int /*<<< orphan*/ ,unsigned int) ; 
 int divider_get_val (unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct meson_clk_cpu_dyndiv_data* meson_clk_cpu_dyndiv_data (struct clk_regmap*) ; 
 int /*<<< orphan*/  meson_parm_write (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static int meson_clk_cpu_dyndiv_set_rate(struct clk_hw *hw, unsigned long rate,
					  unsigned long parent_rate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_cpu_dyndiv_data *data = meson_clk_cpu_dyndiv_data(clk);
	unsigned int val;
	int ret;

	ret = divider_get_val(rate, parent_rate, NULL, data->div.width, 0);
	if (ret < 0)
		return ret;

	val = (unsigned int)ret << data->div.shift;

	/* Write the SYS_CPU_DYN_ENABLE bit before changing the divider */
	meson_parm_write(clk->map, &data->dyn, 1);

	/* Update the divider while removing the SYS_CPU_DYN_ENABLE bit */
	return regmap_update_bits(clk->map, data->div.reg_off,
				  SETPMASK(data->div.width, data->div.shift) |
				  SETPMASK(data->dyn.width, data->dyn.shift),
				  val);
}