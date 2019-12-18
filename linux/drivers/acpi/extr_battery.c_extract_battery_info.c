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
struct acpi_buffer {int /*<<< orphan*/  pointer; } ;
struct acpi_battery {int full_charge_capacity; int design_capacity; int design_voltage; int design_capacity_warning; int capacity_now; int /*<<< orphan*/  flags; scalar_t__ power_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BATTERY_QUIRK_DEGRADED_FULL_CHARGE ; 
 int /*<<< orphan*/  ACPI_BATTERY_QUIRK_PERCENTAGE_CAPACITY ; 
 int /*<<< orphan*/  ACPI_BATTERY_QUIRK_THINKPAD_MAH ; 
 scalar_t__ ARRAY_SIZE (scalar_t__) ; 
 int EFAULT ; 
 scalar_t__ battery_bix_broken_package ; 
 scalar_t__ extended_info_offsets ; 
 int extract_package (struct acpi_battery*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ info_offsets ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int extract_battery_info(const int use_bix,
			 struct acpi_battery *battery,
			 const struct acpi_buffer *buffer)
{
	int result = -EFAULT;

	if (use_bix && battery_bix_broken_package)
		result = extract_package(battery, buffer->pointer,
				extended_info_offsets + 1,
				ARRAY_SIZE(extended_info_offsets) - 1);
	else if (use_bix)
		result = extract_package(battery, buffer->pointer,
				extended_info_offsets,
				ARRAY_SIZE(extended_info_offsets));
	else
		result = extract_package(battery, buffer->pointer,
				info_offsets, ARRAY_SIZE(info_offsets));
	if (test_bit(ACPI_BATTERY_QUIRK_PERCENTAGE_CAPACITY, &battery->flags))
		battery->full_charge_capacity = battery->design_capacity;
	if (test_bit(ACPI_BATTERY_QUIRK_THINKPAD_MAH, &battery->flags) &&
	    battery->power_unit && battery->design_voltage) {
		battery->design_capacity = battery->design_capacity *
		    10000 / battery->design_voltage;
		battery->full_charge_capacity = battery->full_charge_capacity *
		    10000 / battery->design_voltage;
		battery->design_capacity_warning =
		    battery->design_capacity_warning *
		    10000 / battery->design_voltage;
		/* Curiously, design_capacity_low, unlike the rest of them,
		   is correct.  */
		/* capacity_granularity_* equal 1 on the systems tested, so
		   it's impossible to tell if they would need an adjustment
		   or not if their values were higher.  */
	}
	if (test_bit(ACPI_BATTERY_QUIRK_DEGRADED_FULL_CHARGE, &battery->flags) &&
	    battery->capacity_now > battery->full_charge_capacity)
		battery->capacity_now = battery->full_charge_capacity;

	return result;
}