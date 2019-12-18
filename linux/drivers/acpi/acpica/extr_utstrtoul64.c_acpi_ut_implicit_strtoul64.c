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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_STR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_ut_convert_hex_string (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_remove_hex_prefix (char**) ; 
 int /*<<< orphan*/  acpi_ut_remove_leading_zeros (char**) ; 
 int /*<<< orphan*/  acpi_ut_remove_whitespace (char**) ; 
 int /*<<< orphan*/  return_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_implicit_strtoul64 ; 

u64 acpi_ut_implicit_strtoul64(char *string)
{
	u64 converted_integer = 0;

	ACPI_FUNCTION_TRACE_STR(ut_implicit_strtoul64, string);

	if (!acpi_ut_remove_whitespace(&string)) {
		return_VALUE(0);
	}

	/*
	 * Per the ACPI specification, only hexadecimal is supported for
	 * implicit conversions, and the "0x" prefix is "not allowed".
	 * However, allow a "0x" prefix as an ACPI extension.
	 */
	acpi_ut_remove_hex_prefix(&string);

	if (!acpi_ut_remove_leading_zeros(&string)) {
		return_VALUE(0);
	}

	/*
	 * Ignore overflow as per the ACPI specification. This is implemented by
	 * ignoring the return status from the conversion function called below.
	 * On overflow, the input string is simply truncated.
	 */
	acpi_ut_convert_hex_string(string, &converted_integer);
	return_VALUE(converted_integer);
}