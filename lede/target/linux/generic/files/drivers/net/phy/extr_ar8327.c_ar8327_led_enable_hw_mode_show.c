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
struct led_classdev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ar8327_led {int /*<<< orphan*/  enable_hw_mode; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 struct ar8327_led* led_cdev_to_ar8327_led (struct led_classdev*) ; 
 scalar_t__ scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ar8327_led_enable_hw_mode_show(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct ar8327_led *aled = led_cdev_to_ar8327_led(led_cdev);
	ssize_t ret = 0;

	ret += scnprintf(buf, PAGE_SIZE, "%d\n", aled->enable_hw_mode);

	return ret;
}