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
typedef  int u64 ;
struct acpi_generic_address {scalar_t__ space_id; int address; } ;
struct acpi_whea_header {scalar_t__ action; scalar_t__ instruction; struct acpi_generic_address register_region; } ;
struct acpi_einj_trigger {int entry_count; } ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_MEMORY ; 
 scalar_t__ ACPI_EINJ_TRIGGER_ERROR ; 
 scalar_t__ ACPI_EINJ_WRITE_REGISTER_VALUE ; 

__attribute__((used)) static struct acpi_generic_address *einj_get_trigger_parameter_region(
	struct acpi_einj_trigger *trigger_tab, u64 param1, u64 param2)
{
	int i;
	struct acpi_whea_header *entry;

	entry = (struct acpi_whea_header *)
		((char *)trigger_tab + sizeof(struct acpi_einj_trigger));
	for (i = 0; i < trigger_tab->entry_count; i++) {
		if (entry->action == ACPI_EINJ_TRIGGER_ERROR &&
		entry->instruction <= ACPI_EINJ_WRITE_REGISTER_VALUE &&
		entry->register_region.space_id ==
			ACPI_ADR_SPACE_SYSTEM_MEMORY &&
		(entry->register_region.address & param2) == (param1 & param2))
			return &entry->register_region;
		entry++;
	}

	return NULL;
}