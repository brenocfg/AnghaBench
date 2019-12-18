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
struct sirf_data {int /*<<< orphan*/  vcc; scalar_t__ on_off; int /*<<< orphan*/  lna; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct sirf_data* dev_get_drvdata (struct device*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int sirf_set_active (struct sirf_data*,int) ; 

__attribute__((used)) static int sirf_runtime_suspend(struct device *dev)
{
	struct sirf_data *data = dev_get_drvdata(dev);
	int ret2;
	int ret;

	if (data->on_off)
		ret = sirf_set_active(data, false);
	else
		ret = regulator_disable(data->vcc);

	if (ret)
		return ret;

	ret = regulator_disable(data->lna);
	if (ret)
		goto err_reenable;

	return 0;

err_reenable:
	if (data->on_off)
		ret2 = sirf_set_active(data, true);
	else
		ret2 = regulator_enable(data->vcc);

	if (ret2)
		dev_err(dev,
			"failed to reenable power on failed suspend: %d\n",
			ret2);

	return ret;
}