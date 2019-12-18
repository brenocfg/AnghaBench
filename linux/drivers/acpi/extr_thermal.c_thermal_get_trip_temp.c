#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct thermal_zone_device {struct acpi_thermal* devdata; } ;
struct TYPE_14__ {scalar_t__ valid; } ;
struct TYPE_15__ {int /*<<< orphan*/  temperature; TYPE_5__ flags; } ;
struct TYPE_12__ {scalar_t__ valid; } ;
struct TYPE_13__ {int /*<<< orphan*/  temperature; TYPE_3__ flags; } ;
struct TYPE_10__ {scalar_t__ valid; } ;
struct TYPE_11__ {int /*<<< orphan*/  temperature; TYPE_1__ flags; } ;
struct TYPE_18__ {TYPE_8__* active; TYPE_6__ passive; TYPE_4__ hot; TYPE_2__ critical; } ;
struct acpi_thermal {int /*<<< orphan*/  kelvin_offset; TYPE_9__ trips; } ;
struct TYPE_16__ {scalar_t__ valid; } ;
struct TYPE_17__ {int /*<<< orphan*/  temperature; TYPE_7__ flags; } ;

/* Variables and functions */
 int ACPI_THERMAL_MAX_ACTIVE ; 
 int DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 

__attribute__((used)) static int thermal_get_trip_temp(struct thermal_zone_device *thermal,
				 int trip, int *temp)
{
	struct acpi_thermal *tz = thermal->devdata;
	int i;

	if (!tz || trip < 0)
		return -EINVAL;

	if (tz->trips.critical.flags.valid) {
		if (!trip) {
			*temp = DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET(
				tz->trips.critical.temperature,
				tz->kelvin_offset);
			return 0;
		}
		trip--;
	}

	if (tz->trips.hot.flags.valid) {
		if (!trip) {
			*temp = DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET(
				tz->trips.hot.temperature,
				tz->kelvin_offset);
			return 0;
		}
		trip--;
	}

	if (tz->trips.passive.flags.valid) {
		if (!trip) {
			*temp = DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET(
				tz->trips.passive.temperature,
				tz->kelvin_offset);
			return 0;
		}
		trip--;
	}

	for (i = 0; i < ACPI_THERMAL_MAX_ACTIVE &&
		tz->trips.active[i].flags.valid; i++) {
		if (!trip) {
			*temp = DECI_KELVIN_TO_MILLICELSIUS_WITH_OFFSET(
				tz->trips.active[i].temperature,
				tz->kelvin_offset);
			return 0;
		}
		trip--;
	}

	return -EINVAL;
}