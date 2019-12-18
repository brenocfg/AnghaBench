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
struct TYPE_2__ {int /*<<< orphan*/  disk; } ;
struct drbd_device {TYPE_1__ state; } ;
struct device_info {int /*<<< orphan*/  dev_disk_state; } ;

/* Variables and functions */

__attribute__((used)) static void device_to_info(struct device_info *info,
			   struct drbd_device *device)
{
	info->dev_disk_state = device->state.disk;
}