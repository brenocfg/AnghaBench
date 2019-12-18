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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_ascii_char_to_hex (int) ; 
 int /*<<< orphan*/  acpi_ut_strtoul_add64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_strtoul_multiply64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status
acpi_ut_insert_digit(u64 *accumulated_value, u32 base, int ascii_digit)
{
	acpi_status status;
	u64 product;

	/* Make room in the accumulated value for the incoming digit */

	status = acpi_ut_strtoul_multiply64(*accumulated_value, base, &product);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/* Add in the new digit, and store the sum to the accumulated value */

	status =
	    acpi_ut_strtoul_add64(product,
				  acpi_ut_ascii_char_to_hex(ascii_digit),
				  accumulated_value);

	return (status);
}