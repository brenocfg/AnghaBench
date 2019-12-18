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
struct sirf_data {int open; int /*<<< orphan*/  gdev_mutex; struct serdev_device* serdev; } ;
struct serdev_device {int /*<<< orphan*/  dev; } ;
struct gnss_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct sirf_data* gnss_get_drvdata (struct gnss_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sirf_serdev_close (struct sirf_data*) ; 
 int sirf_serdev_open (struct sirf_data*) ; 

__attribute__((used)) static int sirf_open(struct gnss_device *gdev)
{
	struct sirf_data *data = gnss_get_drvdata(gdev);
	struct serdev_device *serdev = data->serdev;
	int ret;

	mutex_lock(&data->gdev_mutex);
	data->open = true;
	mutex_unlock(&data->gdev_mutex);

	ret = sirf_serdev_open(data);
	if (ret) {
		mutex_lock(&data->gdev_mutex);
		data->open = false;
		mutex_unlock(&data->gdev_mutex);
		return ret;
	}

	ret = pm_runtime_get_sync(&serdev->dev);
	if (ret < 0) {
		dev_err(&gdev->dev, "failed to runtime resume: %d\n", ret);
		pm_runtime_put_noidle(&serdev->dev);
		goto err_close;
	}

	return 0;

err_close:
	sirf_serdev_close(data);

	mutex_lock(&data->gdev_mutex);
	data->open = false;
	mutex_unlock(&data->gdev_mutex);

	return ret;
}