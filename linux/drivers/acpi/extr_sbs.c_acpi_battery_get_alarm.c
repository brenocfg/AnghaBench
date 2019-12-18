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
typedef  int /*<<< orphan*/  u8 ;
struct acpi_battery {int /*<<< orphan*/  alarm_capacity; TYPE_1__* sbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  hc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SBS_BATTERY ; 
 int /*<<< orphan*/  SMBUS_READ_WORD ; 
 int acpi_smbus_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_battery_get_alarm(struct acpi_battery *battery)
{
	return acpi_smbus_read(battery->sbs->hc, SMBUS_READ_WORD,
				 ACPI_SBS_BATTERY, 0x01,
				 (u8 *)&battery->alarm_capacity);
}