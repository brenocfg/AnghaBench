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
struct acpi_table_desc {int /*<<< orphan*/  pointer; int /*<<< orphan*/  flags; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_tb_acquire_table (struct acpi_table_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_validate_table ; 

acpi_status acpi_tb_validate_table(struct acpi_table_desc *table_desc)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(tb_validate_table);

	/* Validate the table if necessary */

	if (!table_desc->pointer) {
		status = acpi_tb_acquire_table(table_desc, &table_desc->pointer,
					       &table_desc->length,
					       &table_desc->flags);
		if (!table_desc->pointer) {
			status = AE_NO_MEMORY;
		}
	}

	return_ACPI_STATUS(status);
}