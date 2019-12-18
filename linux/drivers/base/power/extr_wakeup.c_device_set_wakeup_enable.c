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
 int device_wakeup_disable (struct device*) ; 
 int device_wakeup_enable (struct device*) ; 

int device_set_wakeup_enable(struct device *dev, bool enable)
{
	return enable ? device_wakeup_enable(dev) : device_wakeup_disable(dev);
}