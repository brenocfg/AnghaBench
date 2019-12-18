#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ notify; } ;
struct acpi_video_device {TYPE_2__ flags; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_video_device_notify ; 

__attribute__((used)) static void acpi_video_dev_remove_notify_handler(struct acpi_video_device *dev)
{
	if (dev->flags.notify) {
		acpi_remove_notify_handler(dev->dev->handle, ACPI_DEVICE_NOTIFY,
					   acpi_video_device_notify);
		dev->flags.notify = 0;
	}
}