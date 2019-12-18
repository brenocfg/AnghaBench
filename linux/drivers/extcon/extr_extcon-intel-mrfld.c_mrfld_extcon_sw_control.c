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
struct mrfld_extcon_data {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCOVE_CHGRCTRL0 ; 
 unsigned int BCOVE_CHGRCTRL0_SWCONTROL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int mrfld_extcon_clear (struct mrfld_extcon_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int mrfld_extcon_set (struct mrfld_extcon_data*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mrfld_extcon_sw_control(struct mrfld_extcon_data *data, bool enable)
{
	unsigned int mask = BCOVE_CHGRCTRL0_SWCONTROL;
	struct device *dev = data->dev;
	int ret;

	if (enable)
		ret = mrfld_extcon_set(data, BCOVE_CHGRCTRL0, mask);
	else
		ret = mrfld_extcon_clear(data, BCOVE_CHGRCTRL0, mask);
	if (ret)
		dev_err(dev, "can't set SW control: %d\n", ret);
	return ret;
}