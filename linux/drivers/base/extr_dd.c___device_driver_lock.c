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
struct device {TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ need_parent_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock (struct device*) ; 

__attribute__((used)) static void __device_driver_lock(struct device *dev, struct device *parent)
{
	if (parent && dev->bus->need_parent_lock)
		device_lock(parent);
	device_lock(dev);
}