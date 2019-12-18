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
struct acpi_gpe_xrupt_info {struct acpi_gpe_xrupt_info* next; struct acpi_gpe_xrupt_info* register_info; struct acpi_gpe_xrupt_info* event_info; struct acpi_gpe_xrupt_info* gpe_block_list_head; } ;
struct acpi_gpe_block_info {struct acpi_gpe_block_info* next; struct acpi_gpe_block_info* register_info; struct acpi_gpe_block_info* event_info; struct acpi_gpe_block_info* gpe_block_list_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (struct acpi_gpe_xrupt_info*) ; 
 struct acpi_gpe_xrupt_info* acpi_gbl_gpe_xrupt_list_head ; 

__attribute__((used)) static void acpi_ut_free_gpe_lists(void)
{
	struct acpi_gpe_block_info *gpe_block;
	struct acpi_gpe_block_info *next_gpe_block;
	struct acpi_gpe_xrupt_info *gpe_xrupt_info;
	struct acpi_gpe_xrupt_info *next_gpe_xrupt_info;

	/* Free global GPE blocks and related info structures */

	gpe_xrupt_info = acpi_gbl_gpe_xrupt_list_head;
	while (gpe_xrupt_info) {
		gpe_block = gpe_xrupt_info->gpe_block_list_head;
		while (gpe_block) {
			next_gpe_block = gpe_block->next;
			ACPI_FREE(gpe_block->event_info);
			ACPI_FREE(gpe_block->register_info);
			ACPI_FREE(gpe_block);

			gpe_block = next_gpe_block;
		}
		next_gpe_xrupt_info = gpe_xrupt_info->next;
		ACPI_FREE(gpe_xrupt_info);
		gpe_xrupt_info = next_gpe_xrupt_info;
	}
}