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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ut_remove_hex_prefix (char**) ; 

u8 acpi_ut_detect_hex_prefix(char **string)
{
	char *initial_position = *string;

	acpi_ut_remove_hex_prefix(string);
	if (*string != initial_position) {
		return (TRUE);	/* String is past leading 0x */
	}

	return (FALSE);		/* Not a hex string */
}