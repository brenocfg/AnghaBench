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
struct TYPE_2__ {scalar_t__* name; } ;
union acpi_predefined_info {TYPE_1__ info; } ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,scalar_t__*) ; 
 union acpi_predefined_info* acpi_gbl_predefined_methods ; 
 union acpi_predefined_info* acpi_ut_get_next_predefined_method (union acpi_predefined_info const*) ; 

const union acpi_predefined_info *acpi_ut_match_predefined_method(char *name)
{
	const union acpi_predefined_info *this_name;

	/* Quick check for a predefined name, first character must be underscore */

	if (name[0] != '_') {
		return (NULL);
	}

	/* Search info table for a predefined method/object name */

	this_name = acpi_gbl_predefined_methods;
	while (this_name->info.name[0]) {
		if (ACPI_COMPARE_NAMESEG(name, this_name->info.name)) {
			return (this_name);
		}

		this_name = acpi_ut_get_next_predefined_method(this_name);
	}

	return (NULL);		/* Not found */
}