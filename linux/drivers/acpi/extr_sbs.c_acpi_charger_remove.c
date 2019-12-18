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
struct acpi_sbs {scalar_t__ charger; } ;

/* Variables and functions */
 int /*<<< orphan*/  power_supply_unregister (scalar_t__) ; 

__attribute__((used)) static void acpi_charger_remove(struct acpi_sbs *sbs)
{
	if (sbs->charger)
		power_supply_unregister(sbs->charger);
}