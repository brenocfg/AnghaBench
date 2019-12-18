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
struct dock_station {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  add_dock_dependent_device (struct dock_station*,struct acpi_device*) ; 
 int /*<<< orphan*/  find_dock_dependent_device (struct dock_station*,struct acpi_device*) ; 
 struct dock_station* find_dock_station (int /*<<< orphan*/ ) ; 

void register_dock_dependent_device(struct acpi_device *adev,
				    acpi_handle dshandle)
{
	struct dock_station *ds = find_dock_station(dshandle);

	if (ds && !find_dock_dependent_device(ds, adev))
		add_dock_dependent_device(ds, adev);
}