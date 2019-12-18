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

/* Variables and functions */
 int /*<<< orphan*/  acpi_backlight_cmdline ; 
 int /*<<< orphan*/  acpi_backlight_native ; 
 int /*<<< orphan*/  acpi_backlight_none ; 
 int /*<<< orphan*/  acpi_backlight_vendor ; 
 int /*<<< orphan*/  acpi_backlight_video ; 
 int /*<<< orphan*/  acpi_video_backlight_string ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_video_parse_cmdline(void)
{
	if (!strcmp("vendor", acpi_video_backlight_string))
		acpi_backlight_cmdline = acpi_backlight_vendor;
	if (!strcmp("video", acpi_video_backlight_string))
		acpi_backlight_cmdline = acpi_backlight_video;
	if (!strcmp("native", acpi_video_backlight_string))
		acpi_backlight_cmdline = acpi_backlight_native;
	if (!strcmp("none", acpi_video_backlight_string))
		acpi_backlight_cmdline = acpi_backlight_none;
}