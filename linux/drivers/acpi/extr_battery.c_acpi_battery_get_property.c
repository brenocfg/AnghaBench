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
union power_supply_propval {int intval; int /*<<< orphan*/  strval; } ;
struct power_supply {int dummy; } ;
struct acpi_battery {int state; int cycle_count; int design_voltage; int voltage_now; int rate_now; int design_capacity; int full_charge_capacity; int capacity_now; int alarm; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  oem_info; int /*<<< orphan*/  model_number; int /*<<< orphan*/  flags; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BATTERY_ALARM_PRESENT ; 
 int ACPI_BATTERY_STATE_CHARGING ; 
 int ACPI_BATTERY_STATE_CRITICAL ; 
 int ACPI_BATTERY_STATE_DISCHARGING ; 
 int ACPI_BATTERY_VALUE_UNKNOWN ; 
 int EINVAL ; 
 int ENODEV ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_FULL ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_LOW ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_NORMAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 146 
#define  POWER_SUPPLY_PROP_CAPACITY_LEVEL 145 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 144 
#define  POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN 143 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 142 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 141 
#define  POWER_SUPPLY_PROP_CYCLE_COUNT 140 
#define  POWER_SUPPLY_PROP_ENERGY_FULL 139 
#define  POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN 138 
#define  POWER_SUPPLY_PROP_ENERGY_NOW 137 
#define  POWER_SUPPLY_PROP_MANUFACTURER 136 
#define  POWER_SUPPLY_PROP_MODEL_NAME 135 
#define  POWER_SUPPLY_PROP_POWER_NOW 134 
#define  POWER_SUPPLY_PROP_PRESENT 133 
#define  POWER_SUPPLY_PROP_SERIAL_NUMBER 132 
#define  POWER_SUPPLY_PROP_STATUS 131 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  acpi_battery_get_state (struct acpi_battery*) ; 
 int acpi_battery_handle_discharging (struct acpi_battery*) ; 
 int /*<<< orphan*/  acpi_battery_is_charged (struct acpi_battery*) ; 
 int acpi_battery_present (struct acpi_battery*) ; 
 int acpi_battery_technology (struct acpi_battery*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct acpi_battery* to_acpi_battery (struct power_supply*) ; 

__attribute__((used)) static int acpi_battery_get_property(struct power_supply *psy,
				     enum power_supply_property psp,
				     union power_supply_propval *val)
{
	int ret = 0;
	struct acpi_battery *battery = to_acpi_battery(psy);

	if (acpi_battery_present(battery)) {
		/* run battery update only if it is present */
		acpi_battery_get_state(battery);
	} else if (psp != POWER_SUPPLY_PROP_PRESENT)
		return -ENODEV;
	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (battery->state & ACPI_BATTERY_STATE_DISCHARGING)
			val->intval = acpi_battery_handle_discharging(battery);
		else if (battery->state & ACPI_BATTERY_STATE_CHARGING)
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else if (acpi_battery_is_charged(battery))
			val->intval = POWER_SUPPLY_STATUS_FULL;
		else
			val->intval = POWER_SUPPLY_STATUS_UNKNOWN;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = acpi_battery_present(battery);
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = acpi_battery_technology(battery);
		break;
	case POWER_SUPPLY_PROP_CYCLE_COUNT:
		val->intval = battery->cycle_count;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		if (battery->design_voltage == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		else
			val->intval = battery->design_voltage * 1000;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		if (battery->voltage_now == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		else
			val->intval = battery->voltage_now * 1000;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
	case POWER_SUPPLY_PROP_POWER_NOW:
		if (battery->rate_now == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		else
			val->intval = battery->rate_now * 1000;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
	case POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		if (battery->design_capacity == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		else
			val->intval = battery->design_capacity * 1000;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
	case POWER_SUPPLY_PROP_ENERGY_FULL:
		if (battery->full_charge_capacity == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		else
			val->intval = battery->full_charge_capacity * 1000;
		break;
	case POWER_SUPPLY_PROP_CHARGE_NOW:
	case POWER_SUPPLY_PROP_ENERGY_NOW:
		if (battery->capacity_now == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		else
			val->intval = battery->capacity_now * 1000;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		if (battery->capacity_now && battery->full_charge_capacity)
			val->intval = battery->capacity_now * 100/
					battery->full_charge_capacity;
		else
			val->intval = 0;
		break;
	case POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		if (battery->state & ACPI_BATTERY_STATE_CRITICAL)
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		else if (test_bit(ACPI_BATTERY_ALARM_PRESENT, &battery->flags) &&
			(battery->capacity_now <= battery->alarm))
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		else if (acpi_battery_is_charged(battery))
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		else
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = battery->model_number;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = battery->oem_info;
		break;
	case POWER_SUPPLY_PROP_SERIAL_NUMBER:
		val->strval = battery->serial_number;
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}