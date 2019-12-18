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

/* Variables and functions */
 char ACPI_ASCII_ZERO ; 
 char tolower (int) ; 

void acpi_ut_remove_hex_prefix(char **string)
{
	if ((**string == ACPI_ASCII_ZERO) &&
	    (tolower((int)*(*string + 1)) == 'x')) {
		*string += 2;	/* Go past the leading 0x */
	}
}