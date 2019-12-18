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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int acpi_ata_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,char*) ; 

bool acpi_bay_match(acpi_handle handle)
{
	acpi_handle phandle;

	if (!acpi_has_method(handle, "_EJ0"))
		return false;
	if (acpi_ata_match(handle))
		return true;
	if (ACPI_FAILURE(acpi_get_parent(handle, &phandle)))
		return false;

	return acpi_ata_match(phandle);
}