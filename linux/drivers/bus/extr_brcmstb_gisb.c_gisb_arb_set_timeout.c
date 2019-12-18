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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct brcmstb_gisb_arb_device {int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_TIMER ; 
 int EINVAL ; 
 struct brcmstb_gisb_arb_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gisb_write (struct brcmstb_gisb_arb_device*,int,int /*<<< orphan*/ ) ; 
 int kstrtoint (char const*,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t gisb_arb_set_timeout(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	struct brcmstb_gisb_arb_device *gdev = dev_get_drvdata(dev);
	int val, ret;

	ret = kstrtoint(buf, 10, &val);
	if (ret < 0)
		return ret;

	if (val == 0 || val >= 0xffffffff)
		return -EINVAL;

	mutex_lock(&gdev->lock);
	gisb_write(gdev, val, ARB_TIMER);
	mutex_unlock(&gdev->lock);

	return count;
}