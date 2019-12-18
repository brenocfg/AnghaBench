#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct acpi_repair_info {int /*<<< orphan*/  name; scalar_t__ repair_function; } ;
struct TYPE_2__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {TYPE_1__ name; } ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_repair_info* acpi_ns_repairable_names ; 

__attribute__((used)) static const struct acpi_repair_info *acpi_ns_match_complex_repair(struct
								   acpi_namespace_node
								   *node)
{
	const struct acpi_repair_info *this_name;

	/* Search info table for a repairable predefined method/object name */

	this_name = acpi_ns_repairable_names;
	while (this_name->repair_function) {
		if (ACPI_COMPARE_NAMESEG(node->name.ascii, this_name->name)) {
			return (this_name);
		}

		this_name++;
	}

	return (NULL);		/* Not found */
}