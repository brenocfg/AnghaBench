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
 int /*<<< orphan*/  POWER_PM_TYPE_ACPI ; 
 int /*<<< orphan*/  acpi_pm_func ; 
 int /*<<< orphan*/  cold ; 
 int /*<<< orphan*/  power_pm_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_pm_register(void *arg)
{
    if (!cold || resource_disabled("acpi", 0))
	return;

    power_pm_register(POWER_PM_TYPE_ACPI, acpi_pm_func, NULL);
}