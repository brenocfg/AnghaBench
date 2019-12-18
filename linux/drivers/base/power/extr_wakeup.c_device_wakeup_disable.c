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
struct wakeup_source {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  can_wakeup; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int EINVAL ; 
 struct wakeup_source* device_wakeup_detach (struct device*) ; 
 int /*<<< orphan*/  wakeup_source_unregister (struct wakeup_source*) ; 

int device_wakeup_disable(struct device *dev)
{
	struct wakeup_source *ws;

	if (!dev || !dev->power.can_wakeup)
		return -EINVAL;

	ws = device_wakeup_detach(dev);
	wakeup_source_unregister(ws);
	return 0;
}