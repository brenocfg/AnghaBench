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
typedef  int u32 ;

/* Variables and functions */
 int ACPI_NUM_RTYPES ; 
 int ACPI_RTYPE_INTEGER ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/ ** ut_rtype_names ; 

void acpi_ut_get_expected_return_types(char *buffer, u32 expected_btypes)
{
	u32 this_rtype;
	u32 i;
	u32 j;

	if (!expected_btypes) {
		strcpy(buffer, "NONE");
		return;
	}

	j = 1;
	buffer[0] = 0;
	this_rtype = ACPI_RTYPE_INTEGER;

	for (i = 0; i < ACPI_NUM_RTYPES; i++) {

		/* If one of the expected types, concatenate the name of this type */

		if (expected_btypes & this_rtype) {
			strcat(buffer, &ut_rtype_names[i][j]);
			j = 0;	/* Use name separator from now on */
		}

		this_rtype <<= 1;	/* Next Rtype */
	}
}