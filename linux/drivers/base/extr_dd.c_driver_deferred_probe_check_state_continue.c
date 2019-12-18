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
struct device {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int __driver_deferred_probe_check_state (struct device*) ; 

int driver_deferred_probe_check_state_continue(struct device *dev)
{
	int ret;

	ret = __driver_deferred_probe_check_state(dev);
	if (ret < 0)
		return ret;

	return -EPROBE_DEFER;
}