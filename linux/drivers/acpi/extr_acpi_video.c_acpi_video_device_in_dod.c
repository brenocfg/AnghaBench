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
struct acpi_video_device {int device_id; struct acpi_video_bus* video; } ;
struct acpi_video_bus {int attached_count; int child_count; TYPE_2__* attached_array; } ;
struct TYPE_3__ {int int_val; } ;
struct TYPE_4__ {TYPE_1__ value; } ;

/* Variables and functions */

__attribute__((used)) static bool acpi_video_device_in_dod(struct acpi_video_device *device)
{
	struct acpi_video_bus *video = device->video;
	int i;

	/*
	 * If we have a broken _DOD or we have more than 8 output devices
	 * under the graphics controller node that we can't proper deal with
	 * in the operation region code currently, no need to test.
	 */
	if (!video->attached_count || video->child_count > 8)
		return true;

	for (i = 0; i < video->attached_count; i++) {
		if ((video->attached_array[i].value.int_val & 0xfff) ==
		    (device->device_id & 0xfff))
			return true;
	}

	return false;
}