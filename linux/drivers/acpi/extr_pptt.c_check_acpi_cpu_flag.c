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
struct acpi_table_header {int revision; } ;
struct acpi_pptt_processor {int flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_PPTT ; 
 int ENOENT ; 
 struct acpi_pptt_processor* acpi_find_processor_node (struct acpi_table_header*,int) ; 
 int /*<<< orphan*/  acpi_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_table_header**) ; 
 int /*<<< orphan*/  acpi_pptt_warn_missing () ; 
 int /*<<< orphan*/  acpi_put_table (struct acpi_table_header*) ; 
 int get_acpi_id_for_cpu (unsigned int) ; 

__attribute__((used)) static int check_acpi_cpu_flag(unsigned int cpu, int rev, u32 flag)
{
	struct acpi_table_header *table;
	acpi_status status;
	u32 acpi_cpu_id = get_acpi_id_for_cpu(cpu);
	struct acpi_pptt_processor *cpu_node = NULL;
	int ret = -ENOENT;

	status = acpi_get_table(ACPI_SIG_PPTT, 0, &table);
	if (ACPI_FAILURE(status)) {
		acpi_pptt_warn_missing();
		return ret;
	}

	if (table->revision >= rev)
		cpu_node = acpi_find_processor_node(table, acpi_cpu_id);

	if (cpu_node)
		ret = (cpu_node->flags & flag) != 0;

	acpi_put_table(table);

	return ret;
}