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
struct acpi_table_header {int revision; } ;
struct acpi_pptt_processor {int flags; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ACPI_PPTT_ACPI_IDENTICAL ; 
 struct acpi_pptt_processor* fetch_pptt_node (struct acpi_table_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool flag_identical(struct acpi_table_header *table_hdr,
			   struct acpi_pptt_processor *cpu)
{
	struct acpi_pptt_processor *next;

	/* heterogeneous machines must use PPTT revision > 1 */
	if (table_hdr->revision < 2)
		return false;

	/* Locate the last node in the tree with IDENTICAL set */
	if (cpu->flags & ACPI_PPTT_ACPI_IDENTICAL) {
		next = fetch_pptt_node(table_hdr, cpu->parent);
		if (!(next && next->flags & ACPI_PPTT_ACPI_IDENTICAL))
			return true;
	}

	return false;
}