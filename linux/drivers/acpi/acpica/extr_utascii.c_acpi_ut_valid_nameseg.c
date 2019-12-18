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
typedef  size_t u32 ;

/* Variables and functions */
 size_t ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ut_valid_name_char (char,size_t) ; 

u8 acpi_ut_valid_nameseg(char *name)
{
	u32 i;

	/* Validate each character in the signature */

	for (i = 0; i < ACPI_NAMESEG_SIZE; i++) {
		if (!acpi_ut_valid_name_char(name[i], i)) {
			return (FALSE);
		}
	}

	return (TRUE);
}