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
struct acpi_namestring_info {char const* external_name; char* internal_name; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 char* ACPI_ALLOCATE_ZEROED (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_build_internal_name (struct acpi_namestring_info*) ; 
 int /*<<< orphan*/  acpi_ns_get_internal_name_length (struct acpi_namestring_info*) ; 
 int /*<<< orphan*/  ns_internalize_name ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ns_internalize_name(const char *external_name, char **converted_name)
{
	char *internal_name;
	struct acpi_namestring_info info;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_internalize_name);

	if ((!external_name) || (*external_name == 0) || (!converted_name)) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	/* Get the length of the new internal name */

	info.external_name = external_name;
	acpi_ns_get_internal_name_length(&info);

	/* We need a segment to store the internal  name */

	internal_name = ACPI_ALLOCATE_ZEROED(info.length);
	if (!internal_name) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Build the name */

	info.internal_name = internal_name;
	status = acpi_ns_build_internal_name(&info);
	if (ACPI_FAILURE(status)) {
		ACPI_FREE(internal_name);
		return_ACPI_STATUS(status);
	}

	*converted_name = internal_name;
	return_ACPI_STATUS(AE_OK);
}