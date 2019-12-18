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
struct acpi_video_bus {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_osi_is_win8 () ; 
 int acpi_video_bus_DOS (struct acpi_video_bus*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int acpi_video_bus_stop_devices(struct acpi_video_bus *video)
{
	return acpi_video_bus_DOS(video, 0,
				  acpi_osi_is_win8() ? 0 : 1);
}