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
struct userspace_data {int /*<<< orphan*/  user_frequency; scalar_t__ valid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct devfreq {int /*<<< orphan*/  lock; struct userspace_data* data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,...) ; 
 struct devfreq* to_devfreq (struct device*) ; 

__attribute__((used)) static ssize_t show_freq(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct devfreq *devfreq = to_devfreq(dev);
	struct userspace_data *data;
	int err = 0;

	mutex_lock(&devfreq->lock);
	data = devfreq->data;

	if (data->valid)
		err = sprintf(buf, "%lu\n", data->user_frequency);
	else
		err = sprintf(buf, "undefined\n");
	mutex_unlock(&devfreq->lock);
	return err;
}