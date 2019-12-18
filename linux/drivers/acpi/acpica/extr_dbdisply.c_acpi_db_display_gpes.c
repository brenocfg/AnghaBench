#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct acpi_gpe_xrupt_info {struct acpi_gpe_xrupt_info* next; int /*<<< orphan*/  interrupt_number; struct acpi_gpe_block_info* gpe_block_list_head; } ;
struct TYPE_5__ {int /*<<< orphan*/  address; } ;
struct TYPE_4__ {int /*<<< orphan*/  address; } ;
struct acpi_gpe_register_info {TYPE_2__ enable_address; TYPE_1__ status_address; int /*<<< orphan*/  enable_for_wake; int /*<<< orphan*/  enable_for_run; int /*<<< orphan*/  base_gpe_number; } ;
struct acpi_gpe_notify_info {struct acpi_gpe_notify_info* next; } ;
struct TYPE_6__ {struct acpi_gpe_notify_info* notify_list; } ;
struct acpi_gpe_event_info {int flags; TYPE_3__ dispatch; int /*<<< orphan*/  runtime_count; } ;
struct acpi_gpe_block_info {scalar_t__ node; size_t register_count; int gpe_count; struct acpi_gpe_block_info* next; int /*<<< orphan*/  block_base_number; struct acpi_gpe_event_info* event_info; struct acpi_gpe_register_info* register_info; } ;
struct acpi_buffer {int length; char* pointer; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FULL_PATHNAME_NO_TRAILING ; 
 int ACPI_GPE_CAN_WAKE ; 
#define  ACPI_GPE_DISPATCH_HANDLER 132 
#define  ACPI_GPE_DISPATCH_METHOD 131 
#define  ACPI_GPE_DISPATCH_NONE 130 
#define  ACPI_GPE_DISPATCH_NOTIFY 129 
#define  ACPI_GPE_DISPATCH_RAW_HANDLER 128 
 int ACPI_GPE_DISPATCH_TYPE (int) ; 
 int ACPI_GPE_LEVEL_TRIGGERED ; 
 int ACPI_GPE_REGISTER_WIDTH ; 
 scalar_t__ acpi_gbl_fadt_gpe_device ; 
 struct acpi_gpe_xrupt_info* acpi_gbl_gpe_xrupt_list_head ; 
 int /*<<< orphan*/  acpi_get_name (scalar_t__,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 

void acpi_db_display_gpes(void)
{
	struct acpi_gpe_block_info *gpe_block;
	struct acpi_gpe_xrupt_info *gpe_xrupt_info;
	struct acpi_gpe_event_info *gpe_event_info;
	struct acpi_gpe_register_info *gpe_register_info;
	char *gpe_type;
	struct acpi_gpe_notify_info *notify;
	u32 gpe_index;
	u32 block = 0;
	u32 i;
	u32 j;
	u32 count;
	char buffer[80];
	struct acpi_buffer ret_buf;
	acpi_status status;

	ret_buf.length = sizeof(buffer);
	ret_buf.pointer = buffer;

	block = 0;

	/* Walk the GPE lists */

	gpe_xrupt_info = acpi_gbl_gpe_xrupt_list_head;
	while (gpe_xrupt_info) {
		gpe_block = gpe_xrupt_info->gpe_block_list_head;
		while (gpe_block) {
			status = acpi_get_name(gpe_block->node,
					       ACPI_FULL_PATHNAME_NO_TRAILING,
					       &ret_buf);
			if (ACPI_FAILURE(status)) {
				acpi_os_printf
				    ("Could not convert name to pathname\n");
			}

			if (gpe_block->node == acpi_gbl_fadt_gpe_device) {
				gpe_type = "FADT-defined GPE block";
			} else {
				gpe_type = "GPE Block Device";
			}

			acpi_os_printf
			    ("\nBlock %u - Info %p  DeviceNode %p [%s] - %s\n",
			     block, gpe_block, gpe_block->node, buffer,
			     gpe_type);

			acpi_os_printf("    Registers:    %u (%u GPEs)\n",
				       gpe_block->register_count,
				       gpe_block->gpe_count);

			acpi_os_printf
			    ("    GPE range:    0x%X to 0x%X on interrupt %u\n",
			     gpe_block->block_base_number,
			     gpe_block->block_base_number +
			     (gpe_block->gpe_count - 1),
			     gpe_xrupt_info->interrupt_number);

			acpi_os_printf
			    ("    RegisterInfo: %p  Status %8.8X%8.8X Enable %8.8X%8.8X\n",
			     gpe_block->register_info,
			     ACPI_FORMAT_UINT64(gpe_block->register_info->
						status_address.address),
			     ACPI_FORMAT_UINT64(gpe_block->register_info->
						enable_address.address));

			acpi_os_printf("  EventInfo:    %p\n",
				       gpe_block->event_info);

			/* Examine each GPE Register within the block */

			for (i = 0; i < gpe_block->register_count; i++) {
				gpe_register_info =
				    &gpe_block->register_info[i];

				acpi_os_printf("    Reg %u: (GPE %.2X-%.2X)  "
					       "RunEnable %2.2X WakeEnable %2.2X"
					       " Status %8.8X%8.8X Enable %8.8X%8.8X\n",
					       i,
					       gpe_register_info->
					       base_gpe_number,
					       gpe_register_info->
					       base_gpe_number +
					       (ACPI_GPE_REGISTER_WIDTH - 1),
					       gpe_register_info->
					       enable_for_run,
					       gpe_register_info->
					       enable_for_wake,
					       ACPI_FORMAT_UINT64
					       (gpe_register_info->
						status_address.address),
					       ACPI_FORMAT_UINT64
					       (gpe_register_info->
						enable_address.address));

				/* Now look at the individual GPEs in this byte register */

				for (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++) {
					gpe_index =
					    (i * ACPI_GPE_REGISTER_WIDTH) + j;
					gpe_event_info =
					    &gpe_block->event_info[gpe_index];

					if (ACPI_GPE_DISPATCH_TYPE
					    (gpe_event_info->flags) ==
					    ACPI_GPE_DISPATCH_NONE) {

						/* This GPE is not used (no method or handler), ignore it */

						continue;
					}

					acpi_os_printf
					    ("        GPE %.2X: %p  RunRefs %2.2X Flags %2.2X (",
					     gpe_block->block_base_number +
					     gpe_index, gpe_event_info,
					     gpe_event_info->runtime_count,
					     gpe_event_info->flags);

					/* Decode the flags byte */

					if (gpe_event_info->
					    flags & ACPI_GPE_LEVEL_TRIGGERED) {
						acpi_os_printf("Level, ");
					} else {
						acpi_os_printf("Edge, ");
					}

					if (gpe_event_info->
					    flags & ACPI_GPE_CAN_WAKE) {
						acpi_os_printf("CanWake, ");
					} else {
						acpi_os_printf("RunOnly, ");
					}

					switch (ACPI_GPE_DISPATCH_TYPE
						(gpe_event_info->flags)) {
					case ACPI_GPE_DISPATCH_NONE:

						acpi_os_printf("NotUsed");
						break;

					case ACPI_GPE_DISPATCH_METHOD:

						acpi_os_printf("Method");
						break;

					case ACPI_GPE_DISPATCH_HANDLER:

						acpi_os_printf("Handler");
						break;

					case ACPI_GPE_DISPATCH_NOTIFY:

						count = 0;
						notify =
						    gpe_event_info->dispatch.
						    notify_list;
						while (notify) {
							count++;
							notify = notify->next;
						}

						acpi_os_printf
						    ("Implicit Notify on %u devices",
						     count);
						break;

					case ACPI_GPE_DISPATCH_RAW_HANDLER:

						acpi_os_printf("RawHandler");
						break;

					default:

						acpi_os_printf("UNKNOWN: %X",
							       ACPI_GPE_DISPATCH_TYPE
							       (gpe_event_info->
								flags));
						break;
					}

					acpi_os_printf(")\n");
				}
			}

			block++;
			gpe_block = gpe_block->next;
		}

		gpe_xrupt_info = gpe_xrupt_info->next;
	}
}