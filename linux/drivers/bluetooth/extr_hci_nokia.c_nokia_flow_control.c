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

/* Variables and functions */
 int /*<<< orphan*/  serdev_device_set_flow_control (struct serdev_device*,int) ; 
 int /*<<< orphan*/  serdev_device_set_rts (struct serdev_device*,int) ; 

__attribute__((used)) static void nokia_flow_control(struct serdev_device *serdev, bool enable)
{
	if (enable) {
		serdev_device_set_rts(serdev, true);
		serdev_device_set_flow_control(serdev, true);
	} else {
		serdev_device_set_flow_control(serdev, false);
		serdev_device_set_rts(serdev, false);
	}
}