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
struct sirf_data {int active; int /*<<< orphan*/  gdev_mutex; scalar_t__ open; int /*<<< orphan*/  power_wait; int /*<<< orphan*/  wakeup; struct gnss_device* gdev; } ;
struct serdev_device {int dummy; } ;
struct gnss_device {int dummy; } ;

/* Variables and functions */
 int gnss_insert_raw (struct gnss_device*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sirf_data* serdev_device_get_drvdata (struct serdev_device*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sirf_receive_buf(struct serdev_device *serdev,
				const unsigned char *buf, size_t count)
{
	struct sirf_data *data = serdev_device_get_drvdata(serdev);
	struct gnss_device *gdev = data->gdev;
	int ret = 0;

	if (!data->wakeup && !data->active) {
		data->active = true;
		wake_up_interruptible(&data->power_wait);
	}

	mutex_lock(&data->gdev_mutex);
	if (data->open)
		ret = gnss_insert_raw(gdev, buf, count);
	mutex_unlock(&data->gdev_mutex);

	return ret;
}