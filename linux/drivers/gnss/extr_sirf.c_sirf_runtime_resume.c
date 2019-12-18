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
struct sirf_data {int /*<<< orphan*/  lna; int /*<<< orphan*/  vcc; scalar_t__ on_off; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sirf_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int sirf_set_active (struct sirf_data*,int) ; 

__attribute__((used)) static int sirf_runtime_resume(struct device *dev)
{
	struct sirf_data *data = dev_get_drvdata(dev);
	int ret;

	ret = regulator_enable(data->lna);
	if (ret)
		return ret;

	if (data->on_off)
		ret = sirf_set_active(data, true);
	else
		ret = regulator_enable(data->vcc);

	if (ret)
		goto err_disable_lna;

	return 0;

err_disable_lna:
	regulator_disable(data->lna);

	return ret;
}