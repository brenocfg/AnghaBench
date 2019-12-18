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
struct sirf_data {int /*<<< orphan*/  gdev; int /*<<< orphan*/  vcc; scalar_t__ on_off; int /*<<< orphan*/  irq; scalar_t__ wakeup; } ;
struct serdev_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sirf_data*) ; 
 int /*<<< orphan*/  gnss_deregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnss_put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct sirf_data* serdev_device_get_drvdata (struct serdev_device*) ; 
 int /*<<< orphan*/  sirf_runtime_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sirf_remove(struct serdev_device *serdev)
{
	struct sirf_data *data = serdev_device_get_drvdata(serdev);

	gnss_deregister_device(data->gdev);

	if (IS_ENABLED(CONFIG_PM))
		pm_runtime_disable(&serdev->dev);
	else
		sirf_runtime_suspend(&serdev->dev);

	if (data->wakeup)
		free_irq(data->irq, data);

	if (data->on_off)
		regulator_disable(data->vcc);

	gnss_put_device(data->gdev);
}