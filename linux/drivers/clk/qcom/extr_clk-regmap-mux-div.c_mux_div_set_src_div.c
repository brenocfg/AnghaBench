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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; int /*<<< orphan*/  hw; } ;
struct clk_regmap_mux_div {int hid_shift; int src_shift; scalar_t__ reg_offset; TYPE_1__ clkr; int /*<<< orphan*/  src_width; int /*<<< orphan*/  hid_width; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CFG_RCGR ; 
 scalar_t__ CMD_RCGR ; 
 int CMD_RCGR_UPDATE ; 
 int EBUSY ; 
 char* clk_hw_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int mux_div_set_src_div(struct clk_regmap_mux_div *md, u32 src, u32 div)
{
	int ret, count;
	u32 val, mask;
	const char *name = clk_hw_get_name(&md->clkr.hw);

	val = (div << md->hid_shift) | (src << md->src_shift);
	mask = ((BIT(md->hid_width) - 1) << md->hid_shift) |
	       ((BIT(md->src_width) - 1) << md->src_shift);

	ret = regmap_update_bits(md->clkr.regmap, CFG_RCGR + md->reg_offset,
				 mask, val);
	if (ret)
		return ret;

	ret = regmap_update_bits(md->clkr.regmap, CMD_RCGR + md->reg_offset,
				 CMD_RCGR_UPDATE, CMD_RCGR_UPDATE);
	if (ret)
		return ret;

	/* Wait for update to take effect */
	for (count = 500; count > 0; count--) {
		ret = regmap_read(md->clkr.regmap, CMD_RCGR + md->reg_offset,
				  &val);
		if (ret)
			return ret;
		if (!(val & CMD_RCGR_UPDATE))
			return 0;
		udelay(1);
	}

	pr_err("%s: RCG did not update its configuration", name);
	return -EBUSY;
}