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
struct sirf_data {scalar_t__ serdev_count; int /*<<< orphan*/  serdev_mutex; int /*<<< orphan*/  serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sirf_serdev_close(struct sirf_data *data)
{
	mutex_lock(&data->serdev_mutex);
	if (--data->serdev_count == 0)
		serdev_device_close(data->serdev);
	mutex_unlock(&data->serdev_mutex);
}