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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_STR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AE_OK ; 
 int acpi_gbl_integer_bit_width ; 
 int /*<<< orphan*/  acpi_ut_convert_decimal_string (char*,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_ut_convert_hex_string (char*,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_ut_convert_octal_string (char*,scalar_t__*) ; 
 scalar_t__ acpi_ut_detect_hex_prefix (char**) ; 
 scalar_t__ acpi_ut_detect_octal_prefix (char**) ; 
 int /*<<< orphan*/  acpi_ut_remove_leading_zeros (char**) ; 
 int /*<<< orphan*/  acpi_ut_remove_whitespace (char**) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_strtoul64 ; 

acpi_status acpi_ut_strtoul64(char *string, u64 *return_value)
{
	acpi_status status = AE_OK;
	u8 original_bit_width;
	u32 base = 10;		/* Default is decimal */

	ACPI_FUNCTION_TRACE_STR(ut_strtoul64, string);

	*return_value = 0;

	/* A NULL return string returns a value of zero */

	if (*string == 0) {
		return_ACPI_STATUS(AE_OK);
	}

	if (!acpi_ut_remove_whitespace(&string)) {
		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * 1) Check for a hex constant. A "0x" prefix indicates base 16.
	 */
	if (acpi_ut_detect_hex_prefix(&string)) {
		base = 16;
	}

	/*
	 * 2) Check for an octal constant, defined to be a leading zero
	 * followed by sequence of octal digits (0-7)
	 */
	else if (acpi_ut_detect_octal_prefix(&string)) {
		base = 8;
	}

	if (!acpi_ut_remove_leading_zeros(&string)) {
		return_ACPI_STATUS(AE_OK);	/* Return value 0 */
	}

	/*
	 * Force a full 64-bit conversion. The caller (usually iASL) must
	 * check for a 32-bit overflow later as necessary (If current mode
	 * is 32-bit, meaning a 32-bit DSDT).
	 */
	original_bit_width = acpi_gbl_integer_bit_width;
	acpi_gbl_integer_bit_width = 64;

	/*
	 * Perform the base 8, 10, or 16 conversion. A 64-bit numeric overflow
	 * will return an exception (to allow iASL to flag the statement).
	 */
	switch (base) {
	case 8:
		status = acpi_ut_convert_octal_string(string, return_value);
		break;

	case 10:
		status = acpi_ut_convert_decimal_string(string, return_value);
		break;

	case 16:
	default:
		status = acpi_ut_convert_hex_string(string, return_value);
		break;
	}

	/* Only possible exception from above is a 64-bit overflow */

	acpi_gbl_integer_bit_width = original_bit_width;
	return_ACPI_STATUS(status);
}