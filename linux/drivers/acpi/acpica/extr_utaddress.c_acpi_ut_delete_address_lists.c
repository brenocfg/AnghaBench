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
struct acpi_address_range {struct acpi_address_range* next; } ;

/* Variables and functions */
 int ACPI_ADDRESS_RANGE_MAX ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_address_range*) ; 
 struct acpi_address_range** acpi_gbl_address_range_list ; 

void acpi_ut_delete_address_lists(void)
{
	struct acpi_address_range *next;
	struct acpi_address_range *range_info;
	int i;

	/* Delete all elements in all address range lists */

	for (i = 0; i < ACPI_ADDRESS_RANGE_MAX; i++) {
		next = acpi_gbl_address_range_list[i];

		while (next) {
			range_info = next;
			next = range_info->next;
			ACPI_FREE(range_info);
		}

		acpi_gbl_address_range_list[i] = NULL;
	}
}