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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_STR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_ut_convert_decimal_string (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_convert_hex_string (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_ut_detect_hex_prefix (char**) ; 
 int /*<<< orphan*/  acpi_ut_remove_leading_zeros (char**) ; 
 int /*<<< orphan*/  acpi_ut_remove_whitespace (char**) ; 
 int /*<<< orphan*/  return_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_explicit_strtoul64 ; 

u64 acpi_ut_explicit_strtoul64(char *string)
{
	u64 converted_integer = 0;
	u32 base = 10;		/* Default is decimal */

	ACPI_FUNCTION_TRACE_STR(ut_explicit_strtoul64, string);

	if (!acpi_ut_remove_whitespace(&string)) {
		return_VALUE(0);
	}

	/*
	 * Only Hex and Decimal are supported, as per the ACPI specification.
	 * A "0x" prefix indicates hex; otherwise decimal is assumed.
	 */
	if (acpi_ut_detect_hex_prefix(&string)) {
		base = 16;
	}

	if (!acpi_ut_remove_leading_zeros(&string)) {
		return_VALUE(0);
	}

	/*
	 * Ignore overflow as per the ACPI specification. This is implemented by
	 * ignoring the return status from the conversion functions called below.
	 * On overflow, the input string is simply truncated.
	 */
	switch (base) {
	case 10:
	default:
		acpi_ut_convert_decimal_string(string, &converted_integer);
		break;

	case 16:
		acpi_ut_convert_hex_string(string, &converted_integer);
		break;
	}

	return_VALUE(converted_integer);
}