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
typedef  scalar_t__ u32 ;
struct acpi_simple_repair_info {scalar_t__ unexpected_btypes; scalar_t__ package_index; int /*<<< orphan*/  name; scalar_t__ object_converter; } ;
struct TYPE_2__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {TYPE_1__ name; } ;

/* Variables and functions */
 scalar_t__ ACPI_ALL_PACKAGE_ELEMENTS ; 
 scalar_t__ ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct acpi_simple_repair_info* acpi_object_repair_info ; 

__attribute__((used)) static const struct acpi_simple_repair_info *acpi_ns_match_simple_repair(struct
									 acpi_namespace_node
									 *node,
									 u32
									 return_btype,
									 u32
									 package_index)
{
	const struct acpi_simple_repair_info *this_name;

	/* Search info table for a repairable predefined method/object name */

	this_name = acpi_object_repair_info;
	while (this_name->object_converter) {
		if (ACPI_COMPARE_NAMESEG(node->name.ascii, this_name->name)) {

			/* Check if we can actually repair this name/type combination */

			if ((return_btype & this_name->unexpected_btypes) &&
			    (this_name->package_index ==
			     ACPI_ALL_PACKAGE_ELEMENTS
			     || package_index == this_name->package_index)) {
				return (this_name);
			}

			return (NULL);
		}

		this_name++;
	}

	return (NULL);		/* Name was not found in the repair table */
}