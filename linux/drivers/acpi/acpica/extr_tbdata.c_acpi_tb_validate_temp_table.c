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
struct acpi_table_header {int dummy; } ;
struct acpi_table_desc {int length; int /*<<< orphan*/  pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_gbl_enable_table_validation ; 
 int /*<<< orphan*/  acpi_tb_validate_table (struct acpi_table_desc*) ; 

acpi_status acpi_tb_validate_temp_table(struct acpi_table_desc *table_desc)
{

	if (!table_desc->pointer && !acpi_gbl_enable_table_validation) {
		/*
		 * Only validates the header of the table.
		 * Note that Length contains the size of the mapping after invoking
		 * this work around, this value is required by
		 * acpi_tb_release_temp_table().
		 * We can do this because in acpi_init_table_descriptor(), the Length
		 * field of the installed descriptor is filled with the actual
		 * table length obtaining from the table header.
		 */
		table_desc->length = sizeof(struct acpi_table_header);
	}

	return (acpi_tb_validate_table(table_desc));
}