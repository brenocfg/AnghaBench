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
 int CHT_WC_CHGDISCTRL_FN ; 
 int /*<<< orphan*/  CHT_WC_CHGRCTRL0 ; 
 int CHT_WC_CHGRCTRL0_CCSM_OFF ; 
 int CHT_WC_CHGRCTRL0_SWCONTROL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int cht_wc_extcon_sw_control(struct cht_wc_extcon_data *ext, bool enable)
{
	int ret, mask, val;

	val = enable ? 0 : CHT_WC_CHGDISCTRL_FN;
	ret = regmap_update_bits(ext->regmap, CHT_WC_CHGDISCTRL,
				 CHT_WC_CHGDISCTRL_FN, val);
	if (ret)
		dev_err(ext->dev,
			"Error setting sw control for CHGDIS pin: %d\n",
			ret);

	mask = CHT_WC_CHGRCTRL0_SWCONTROL | CHT_WC_CHGRCTRL0_CCSM_OFF;
	val = enable ? mask : 0;
	ret = regmap_update_bits(ext->regmap, CHT_WC_CHGRCTRL0, mask, val);
	if (ret)
		dev_err(ext->dev, "Error setting sw control: %d\n", ret);

	return ret;
}