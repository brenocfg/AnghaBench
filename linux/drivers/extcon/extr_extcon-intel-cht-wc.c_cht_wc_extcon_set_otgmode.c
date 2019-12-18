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
 int /*<<< orphan*/  CHT_WC_CHGRCTRL1 ; 
 unsigned int CHT_WC_CHGRCTRL1_OTGMODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void cht_wc_extcon_set_otgmode(struct cht_wc_extcon_data *ext,
				      bool enable)
{
	unsigned int val = enable ? CHT_WC_CHGRCTRL1_OTGMODE : 0;
	int ret;

	ret = regmap_update_bits(ext->regmap, CHT_WC_CHGRCTRL1,
				 CHT_WC_CHGRCTRL1_OTGMODE, val);
	if (ret)
		dev_err(ext->dev, "Error updating CHGRCTRL1 reg: %d\n", ret);
}