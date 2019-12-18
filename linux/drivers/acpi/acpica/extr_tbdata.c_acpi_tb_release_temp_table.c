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
struct acpi_table_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_tb_invalidate_table (struct acpi_table_desc*) ; 

void acpi_tb_release_temp_table(struct acpi_table_desc *table_desc)
{

	/*
	 * Note that the .Address is maintained by the callers of
	 * acpi_tb_acquire_temp_table(), thus do not invoke acpi_tb_uninstall_table()
	 * where .Address will be freed.
	 */
	acpi_tb_invalidate_table(table_desc);
}