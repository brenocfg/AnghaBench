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
struct serdev_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nokia_flow_control (struct serdev_device*,int) ; 
 struct serdev_device* to_serdev_device (struct device*) ; 

__attribute__((used)) static int nokia_bluetooth_runtime_suspend(struct device *dev)
{
	struct serdev_device *serdev = to_serdev_device(dev);

	nokia_flow_control(serdev, false);
	return 0;
}