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
typedef  size_t u32 ;
struct acpi_gpe_xrupt_info {int dummy; } ;
struct acpi_gpe_register_info {int /*<<< orphan*/  enable_for_wake; } ;
struct acpi_gpe_block_info {size_t register_count; struct acpi_gpe_register_info* register_info; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_hw_gpe_enable_write (int /*<<< orphan*/ ,struct acpi_gpe_register_info*) ; 

__attribute__((used)) static acpi_status
acpi_hw_enable_wakeup_gpe_block(struct acpi_gpe_xrupt_info *gpe_xrupt_info,
				struct acpi_gpe_block_info *gpe_block,
				void *context)
{
	u32 i;
	acpi_status status;
	struct acpi_gpe_register_info *gpe_register_info;

	/* Examine each GPE Register within the block */

	for (i = 0; i < gpe_block->register_count; i++) {
		gpe_register_info = &gpe_block->register_info[i];

		/*
		 * Enable all "wake" GPEs in this register and disable the
		 * remaining ones.
		 */

		status =
		    acpi_hw_gpe_enable_write(gpe_register_info->enable_for_wake,
					     gpe_register_info);
		if (ACPI_FAILURE(status)) {
			return (status);
		}
	}

	return (AE_OK);
}