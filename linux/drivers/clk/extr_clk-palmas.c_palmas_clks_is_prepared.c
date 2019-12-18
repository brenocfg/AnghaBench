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
struct palmas_clock_info {TYPE_1__* clk_desc; int /*<<< orphan*/  dev; int /*<<< orphan*/  palmas; scalar_t__ ext_control_pin; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int enable_mask; int /*<<< orphan*/  control_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_RESOURCE_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int palmas_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct palmas_clock_info* to_palmas_clks_info (struct clk_hw*) ; 

__attribute__((used)) static int palmas_clks_is_prepared(struct clk_hw *hw)
{
	struct palmas_clock_info *cinfo = to_palmas_clks_info(hw);
	int ret;
	u32 val;

	if (cinfo->ext_control_pin)
		return 1;

	ret = palmas_read(cinfo->palmas, PALMAS_RESOURCE_BASE,
			  cinfo->clk_desc->control_reg, &val);
	if (ret < 0) {
		dev_err(cinfo->dev, "Reg 0x%02x read failed, %d\n",
			cinfo->clk_desc->control_reg, ret);
		return ret;
	}
	return !!(val & cinfo->clk_desc->enable_mask);
}