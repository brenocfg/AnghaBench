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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_PPTT ; 
 int ENOENT ; 
 int /*<<< orphan*/  acpi_get_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_table_header**) ; 
 int /*<<< orphan*/  acpi_pptt_warn_missing () ; 
 int /*<<< orphan*/  acpi_put_table (struct acpi_table_header*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int,int) ; 
 int topology_get_acpi_cpu_tag (struct acpi_table_header*,unsigned int,int,int) ; 

__attribute__((used)) static int find_acpi_cpu_topology_tag(unsigned int cpu, int level, int flag)
{
	struct acpi_table_header *table;
	acpi_status status;
	int retval;

	status = acpi_get_table(ACPI_SIG_PPTT, 0, &table);
	if (ACPI_FAILURE(status)) {
		acpi_pptt_warn_missing();
		return -ENOENT;
	}
	retval = topology_get_acpi_cpu_tag(table, cpu, level, flag);
	pr_debug("Topology Setup ACPI CPU %d, level %d ret = %d\n",
		 cpu, level, retval);
	acpi_put_table(table);

	return retval;
}