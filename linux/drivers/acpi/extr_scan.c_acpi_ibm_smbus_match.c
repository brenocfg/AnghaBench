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
struct acpi_buffer {int member_0; char* member_1; int /*<<< orphan*/  pointer; } ;
typedef  int /*<<< orphan*/  node_name ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_PATH_SEGMENT_LENGTH ; 
 int /*<<< orphan*/  ACPI_SINGLE_NAME ; 
 int /*<<< orphan*/  acpi_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 scalar_t__ acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmi_name_in_vendors (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool acpi_ibm_smbus_match(acpi_handle handle)
{
	char node_name[ACPI_PATH_SEGMENT_LENGTH];
	struct acpi_buffer path = { sizeof(node_name), node_name };

	if (!dmi_name_in_vendors("IBM"))
		return false;

	/* Look for SMBS object */
	if (ACPI_FAILURE(acpi_get_name(handle, ACPI_SINGLE_NAME, &path)) ||
	    strcmp("SMBS", path.pointer))
		return false;

	/* Does it have the necessary (but misnamed) methods? */
	if (acpi_has_method(handle, "SBI") &&
	    acpi_has_method(handle, "SBR") &&
	    acpi_has_method(handle, "SBW"))
		return true;

	return false;
}