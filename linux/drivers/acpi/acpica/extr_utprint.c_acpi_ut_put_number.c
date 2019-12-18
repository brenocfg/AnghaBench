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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;

/* Variables and functions */
 char* acpi_gbl_lower_hex_digits ; 
 char* acpi_gbl_upper_hex_digits ; 
 int /*<<< orphan*/  acpi_ut_divide (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static char *acpi_ut_put_number(char *string, u64 number, u8 base, u8 upper)
{
	const char *digits;
	u64 digit_index;
	char *pos;

	pos = string;
	digits = upper ? acpi_gbl_upper_hex_digits : acpi_gbl_lower_hex_digits;

	if (number == 0) {
		*(pos++) = '0';
	} else {
		while (number) {
			(void)acpi_ut_divide(number, base, &number,
					     &digit_index);
			*(pos++) = digits[digit_index];
		}
	}

	/* *(Pos++) = '0'; */
	return (pos);
}