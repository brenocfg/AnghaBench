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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_tb_install_standard_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_tb_load_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_install_and_load_table ; 

acpi_status
acpi_tb_install_and_load_table(acpi_physical_address address,
			       u8 flags, u8 override, u32 *table_index)
{
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TRACE(tb_install_and_load_table);

	/* Install the table and load it into the namespace */

	status = acpi_tb_install_standard_table(address, flags, TRUE,
						override, &i);
	if (ACPI_FAILURE(status)) {
		goto exit;
	}

	status = acpi_tb_load_table(i, acpi_gbl_root_node);

exit:
	*table_index = i;
	return_ACPI_STATUS(status);
}