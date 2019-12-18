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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_table_header {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_PPTT ; 
 int acpi_find_cache_levels (struct acpi_table_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_table_header**) ; 
 int /*<<< orphan*/  acpi_pptt_warn_missing () ; 
 int /*<<< orphan*/  acpi_put_table (struct acpi_table_header*) ; 
 int /*<<< orphan*/  get_acpi_id_for_cpu (unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

int acpi_find_last_cache_level(unsigned int cpu)
{
	u32 acpi_cpu_id;
	struct acpi_table_header *table;
	int number_of_levels = 0;
	acpi_status status;

	pr_debug("Cache Setup find last level CPU=%d\n", cpu);

	acpi_cpu_id = get_acpi_id_for_cpu(cpu);
	status = acpi_get_table(ACPI_SIG_PPTT, 0, &table);
	if (ACPI_FAILURE(status)) {
		acpi_pptt_warn_missing();
	} else {
		number_of_levels = acpi_find_cache_levels(table, acpi_cpu_id);
		acpi_put_table(table);
	}
	pr_debug("Cache Setup find last level level=%d\n", number_of_levels);

	return number_of_levels;
}