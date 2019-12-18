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
struct cht_wc_extcon_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHT_WC_CHGDISCTRL ; 
 unsigned int CHT_WC_CHGDISCTRL_OUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void cht_wc_extcon_enable_charging(struct cht_wc_extcon_data *ext,
					  bool enable)
{
	unsigned int val = enable ? 0 : CHT_WC_CHGDISCTRL_OUT;
	int ret;

	ret = regmap_update_bits(ext->regmap, CHT_WC_CHGDISCTRL,
				 CHT_WC_CHGDISCTRL_OUT, val);
	if (ret)
		dev_err(ext->dev, "Error updating CHGDISCTRL reg: %d\n", ret);
}