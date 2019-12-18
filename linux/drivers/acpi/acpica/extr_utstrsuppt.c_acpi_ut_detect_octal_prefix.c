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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 char ACPI_ASCII_ZERO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

u8 acpi_ut_detect_octal_prefix(char **string)
{

	if (**string == ACPI_ASCII_ZERO) {
		*string += 1;	/* Go past the leading 0 */
		return (TRUE);
	}

	return (FALSE);		/* Not an octal string */
}