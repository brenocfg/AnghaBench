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
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_release_driver_internal (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void device_driver_detach(struct device *dev)
{
	device_release_driver_internal(dev, NULL, dev->parent);
}