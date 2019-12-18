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
struct acpi_battinfo {int cap; int min; int rate; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BATT_STAT_NOT_PRESENT ; 

__attribute__((used)) static void
acpi_reset_battinfo(struct acpi_battinfo *info)
{
    info->cap = -1;
    info->min = -1;
    info->state = ACPI_BATT_STAT_NOT_PRESENT;
    info->rate = -1;
}