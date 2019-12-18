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
typedef  int /*<<< orphan*/  u8 ;
struct led_classdev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ar8327_led {int enable_hw_mode; int /*<<< orphan*/  lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR8327_LED_PATTERN_OFF ; 
 int /*<<< orphan*/  AR8327_LED_PATTERN_RULE ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  ar8327_led_schedule_change (struct ar8327_led*,int /*<<< orphan*/ ) ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 int kstrtou8 (char const*,int,int /*<<< orphan*/ *) ; 
 struct ar8327_led* led_cdev_to_ar8327_led (struct led_classdev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
ar8327_led_enable_hw_mode_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf,
				size_t size)
{
        struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ar8327_led *aled = led_cdev_to_ar8327_led(led_cdev);
	u8 pattern;
	u8 value;
	int ret;

	ret = kstrtou8(buf, 10, &value);
	if (ret < 0)
		return -EINVAL;

	spin_lock(&aled->lock);

	aled->enable_hw_mode = !!value;
	if (aled->enable_hw_mode)
		pattern = AR8327_LED_PATTERN_RULE;
	else
		pattern = AR8327_LED_PATTERN_OFF;

	ar8327_led_schedule_change(aled, pattern);

	spin_unlock(&aled->lock);

	return size;
}