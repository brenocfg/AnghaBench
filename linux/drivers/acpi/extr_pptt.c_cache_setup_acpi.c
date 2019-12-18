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
typedef  int acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int) ; 
 int /*<<< orphan*/  ACPI_SIG_PPTT ; 
 int ENOENT ; 
 int acpi_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_table_header**) ; 
 int /*<<< orphan*/  acpi_pptt_warn_missing () ; 
 int /*<<< orphan*/  acpi_put_table (struct acpi_table_header*) ; 
 int /*<<< orphan*/  cache_setup_acpi_cpu (struct acpi_table_header*,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 

int cache_setup_acpi(unsigned int cpu)
{
	struct acpi_table_header *table;
	acpi_status status;

	pr_debug("Cache Setup ACPI CPU %d\n", cpu);

	status = acpi_get_table(ACPI_SIG_PPTT, 0, &table);
	if (ACPI_FAILURE(status)) {
		acpi_pptt_warn_missing();
		return -ENOENT;
	}

	cache_setup_acpi_cpu(table, cpu);
	acpi_put_table(table);

	return status;
}