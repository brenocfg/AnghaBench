#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct devfreq {TYPE_1__* governor; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* event_handler ) (struct devfreq*,int /*<<< orphan*/ ,unsigned int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_GOV_INTERVAL ; 
 int EINVAL ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 int /*<<< orphan*/  stub1 (struct devfreq*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct devfreq* to_devfreq (struct device*) ; 

__attribute__((used)) static ssize_t polling_interval_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct devfreq *df = to_devfreq(dev);
	unsigned int value;
	int ret;

	if (!df->governor)
		return -EINVAL;

	ret = sscanf(buf, "%u", &value);
	if (ret != 1)
		return -EINVAL;

	df->governor->event_handler(df, DEVFREQ_GOV_INTERVAL, &value);
	ret = count;

	return ret;
}