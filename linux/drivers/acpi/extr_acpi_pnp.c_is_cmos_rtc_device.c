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
struct acpi_device_id {char* member_0; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_match_device_ids (struct acpi_device*,struct acpi_device_id const*) ; 

__attribute__((used)) static int is_cmos_rtc_device(struct acpi_device *adev)
{
	static const struct acpi_device_id ids[] = {
		{ "PNP0B00" },
		{ "PNP0B01" },
		{ "PNP0B02" },
		{""},
	};
	return !acpi_match_device_ids(adev, ids);
}