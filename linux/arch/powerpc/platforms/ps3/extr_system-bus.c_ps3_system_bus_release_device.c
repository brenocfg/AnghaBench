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
struct ps3_system_bus_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ps3_system_bus_device*) ; 
 struct ps3_system_bus_device* ps3_dev_to_system_bus_dev (struct device*) ; 

__attribute__((used)) static void ps3_system_bus_release_device(struct device *_dev)
{
	struct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	kfree(dev);
}