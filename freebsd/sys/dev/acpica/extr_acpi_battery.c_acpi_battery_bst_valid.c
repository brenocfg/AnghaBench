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
struct acpi_bst {scalar_t__ state; scalar_t__ cap; scalar_t__ volt; } ;

/* Variables and functions */
 scalar_t__ ACPI_BATT_STAT_NOT_PRESENT ; 
 scalar_t__ ACPI_BATT_UNKNOWN ; 

int
acpi_battery_bst_valid(struct acpi_bst *bst)
{

    return (bst->state != ACPI_BATT_STAT_NOT_PRESENT &&
	bst->cap != ACPI_BATT_UNKNOWN && bst->volt != ACPI_BATT_UNKNOWN);
}