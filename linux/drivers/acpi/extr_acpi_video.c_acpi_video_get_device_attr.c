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
struct acpi_video_device_attrib {int dummy; } ;
struct TYPE_2__ {int int_val; struct acpi_video_device_attrib attrib; } ;
struct acpi_video_enumerated_device {TYPE_1__ value; } ;
struct acpi_video_bus {int attached_count; struct acpi_video_enumerated_device* attached_array; } ;

/* Variables and functions */

__attribute__((used)) static struct acpi_video_device_attrib *
acpi_video_get_device_attr(struct acpi_video_bus *video, unsigned long device_id)
{
	struct acpi_video_enumerated_device *ids;
	int i;

	for (i = 0; i < video->attached_count; i++) {
		ids = &video->attached_array[i];
		if ((ids->value.int_val & 0xffff) == device_id)
			return &ids->value.attrib;
	}

	return NULL;
}