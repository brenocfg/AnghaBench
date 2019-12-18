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
struct sirf_data {int serdev_count; int /*<<< orphan*/  serdev_mutex; int /*<<< orphan*/  serdev; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int serdev_device_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdev_device_set_baudrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdev_device_set_flow_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sirf_serdev_open(struct sirf_data *data)
{
	int ret = 0;

	mutex_lock(&data->serdev_mutex);
	if (++data->serdev_count == 1) {
		ret = serdev_device_open(data->serdev);
		if (ret) {
			data->serdev_count--;
			goto out_unlock;
		}

		serdev_device_set_baudrate(data->serdev, data->speed);
		serdev_device_set_flow_control(data->serdev, false);
	}

out_unlock:
	mutex_unlock(&data->serdev_mutex);

	return ret;
}