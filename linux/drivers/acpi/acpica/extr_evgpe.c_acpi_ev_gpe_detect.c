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
struct acpi_namespace_node {int dummy; } ;
struct acpi_gpe_xrupt_info {struct acpi_gpe_block_info* gpe_block_list_head; } ;
struct acpi_gpe_register_info {int enable_for_run; int enable_for_wake; int base_gpe_number; } ;
struct acpi_gpe_event_info {int dummy; } ;
struct acpi_gpe_block_info {size_t register_count; struct acpi_gpe_block_info* next; struct acpi_gpe_event_info* event_info; struct acpi_gpe_register_info* register_info; struct acpi_namespace_node* node; } ;
typedef  int acpi_size ;
typedef  int /*<<< orphan*/  acpi_cpu_flags ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INTERRUPTS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int ACPI_GPE_REGISTER_WIDTH ; 
 size_t ACPI_INTERRUPT_NOT_HANDLED ; 
 size_t acpi_ev_detect_gpe (struct acpi_namespace_node*,struct acpi_gpe_event_info*,size_t) ; 
 int /*<<< orphan*/  acpi_gbl_gpe_lock ; 
 int /*<<< orphan*/  acpi_os_acquire_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_release_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_gpe_detect ; 

u32 acpi_ev_gpe_detect(struct acpi_gpe_xrupt_info *gpe_xrupt_list)
{
	struct acpi_gpe_block_info *gpe_block;
	struct acpi_namespace_node *gpe_device;
	struct acpi_gpe_register_info *gpe_register_info;
	struct acpi_gpe_event_info *gpe_event_info;
	u32 gpe_number;
	u32 int_status = ACPI_INTERRUPT_NOT_HANDLED;
	acpi_cpu_flags flags;
	u32 i;
	u32 j;

	ACPI_FUNCTION_NAME(ev_gpe_detect);

	/* Check for the case where there are no GPEs */

	if (!gpe_xrupt_list) {
		return (int_status);
	}

	/*
	 * We need to obtain the GPE lock for both the data structs and registers
	 * Note: Not necessary to obtain the hardware lock, since the GPE
	 * registers are owned by the gpe_lock.
	 */
	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Examine all GPE blocks attached to this interrupt level */

	gpe_block = gpe_xrupt_list->gpe_block_list_head;
	while (gpe_block) {
		gpe_device = gpe_block->node;

		/*
		 * Read all of the 8-bit GPE status and enable registers in this GPE
		 * block, saving all of them. Find all currently active GP events.
		 */
		for (i = 0; i < gpe_block->register_count; i++) {

			/* Get the next status/enable pair */

			gpe_register_info = &gpe_block->register_info[i];

			/*
			 * Optimization: If there are no GPEs enabled within this
			 * register, we can safely ignore the entire register.
			 */
			if (!(gpe_register_info->enable_for_run |
			      gpe_register_info->enable_for_wake)) {
				ACPI_DEBUG_PRINT((ACPI_DB_INTERRUPTS,
						  "Ignore disabled registers for GPE %02X-%02X: "
						  "RunEnable=%02X, WakeEnable=%02X\n",
						  gpe_register_info->
						  base_gpe_number,
						  gpe_register_info->
						  base_gpe_number +
						  (ACPI_GPE_REGISTER_WIDTH - 1),
						  gpe_register_info->
						  enable_for_run,
						  gpe_register_info->
						  enable_for_wake));
				continue;
			}

			/* Now look at the individual GPEs in this byte register */

			for (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++) {

				/* Detect and dispatch one GPE bit */

				gpe_event_info =
				    &gpe_block->
				    event_info[((acpi_size)i *
						ACPI_GPE_REGISTER_WIDTH) + j];
				gpe_number =
				    j + gpe_register_info->base_gpe_number;
				acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
				int_status |=
				    acpi_ev_detect_gpe(gpe_device,
						       gpe_event_info,
						       gpe_number);
				flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
			}
		}

		gpe_block = gpe_block->next;
	}

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	return (int_status);
}