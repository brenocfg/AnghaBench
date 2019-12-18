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
struct wakeup_source {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 struct device* wakeup_source_device_create (struct device*,struct wakeup_source*) ; 

int wakeup_source_sysfs_add(struct device *parent, struct wakeup_source *ws)
{
	struct device *dev;

	dev = wakeup_source_device_create(parent, ws);
	if (IS_ERR(dev))
		return PTR_ERR(dev);
	ws->dev = dev;

	return 0;
}