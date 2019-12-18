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
struct gnss_device {int dummy; } ;

/* Variables and functions */
 struct sirf_data* gnss_get_drvdata (struct gnss_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sirf_serdev_close (struct sirf_data*) ; 

__attribute__((used)) static void sirf_close(struct gnss_device *gdev)
{
	struct sirf_data *data = gnss_get_drvdata(gdev);
	struct serdev_device *serdev = data->serdev;

	sirf_serdev_close(data);

	pm_runtime_put(&serdev->dev);

	mutex_lock(&data->gdev_mutex);
	data->open = false;
	mutex_unlock(&data->gdev_mutex);
}