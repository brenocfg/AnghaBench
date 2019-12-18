#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  void* u16 ;
struct TYPE_3__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {TYPE_1__ name; } ;
struct acpi_gpe_walk_info {void* execute_by_owner_id; struct acpi_namespace_node* gpe_device; struct acpi_gpe_block_info* gpe_block; } ;
struct acpi_gpe_block_info {int gpe_count; int register_count; int block_base_number; struct acpi_gpe_block_info* event_info; struct acpi_gpe_block_info* register_info; void* initialized; struct acpi_namespace_node* node; int /*<<< orphan*/  space_id; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {int sci_interrupt; } ;

/* Variables and functions */
 struct acpi_gpe_block_info* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_gpe_block_info*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_GPE_REGISTER_WIDTH ; 
 int /*<<< orphan*/  ACPI_NS_WALK_NO_UNLOCK ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 void* FALSE ; 
 int acpi_current_gpe_count ; 
 int /*<<< orphan*/  acpi_ev_create_gpe_info_blocks (struct acpi_gpe_block_info*) ; 
 int /*<<< orphan*/  acpi_ev_install_gpe_block (struct acpi_gpe_block_info*,int) ; 
 int /*<<< orphan*/  acpi_ev_match_gpe_method ; 
 TYPE_2__ acpi_gbl_FADT ; 
 void* acpi_gbl_all_gpes_initialized ; 
 int /*<<< orphan*/  acpi_ns_walk_namespace (int /*<<< orphan*/ ,struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_gpe_walk_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_create_gpe_block ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_create_gpe_block(struct acpi_namespace_node *gpe_device,
			 u64 address,
			 u8 space_id,
			 u32 register_count,
			 u16 gpe_block_base_number,
			 u32 interrupt_number,
			 struct acpi_gpe_block_info **return_gpe_block)
{
	acpi_status status;
	struct acpi_gpe_block_info *gpe_block;
	struct acpi_gpe_walk_info walk_info;

	ACPI_FUNCTION_TRACE(ev_create_gpe_block);

	if (!register_count) {
		return_ACPI_STATUS(AE_OK);
	}

	/* Allocate a new GPE block */

	gpe_block = ACPI_ALLOCATE_ZEROED(sizeof(struct acpi_gpe_block_info));
	if (!gpe_block) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}

	/* Initialize the new GPE block */

	gpe_block->address = address;
	gpe_block->space_id = space_id;
	gpe_block->node = gpe_device;
	gpe_block->gpe_count = (u16)(register_count * ACPI_GPE_REGISTER_WIDTH);
	gpe_block->initialized = FALSE;
	gpe_block->register_count = register_count;
	gpe_block->block_base_number = gpe_block_base_number;

	/*
	 * Create the register_info and event_info sub-structures
	 * Note: disables and clears all GPEs in the block
	 */
	status = acpi_ev_create_gpe_info_blocks(gpe_block);
	if (ACPI_FAILURE(status)) {
		ACPI_FREE(gpe_block);
		return_ACPI_STATUS(status);
	}

	/* Install the new block in the global lists */

	status = acpi_ev_install_gpe_block(gpe_block, interrupt_number);
	if (ACPI_FAILURE(status)) {
		ACPI_FREE(gpe_block->register_info);
		ACPI_FREE(gpe_block->event_info);
		ACPI_FREE(gpe_block);
		return_ACPI_STATUS(status);
	}

	acpi_gbl_all_gpes_initialized = FALSE;

	/* Find all GPE methods (_Lxx or_Exx) for this block */

	walk_info.gpe_block = gpe_block;
	walk_info.gpe_device = gpe_device;
	walk_info.execute_by_owner_id = FALSE;

	status = acpi_ns_walk_namespace(ACPI_TYPE_METHOD, gpe_device,
					ACPI_UINT32_MAX, ACPI_NS_WALK_NO_UNLOCK,
					acpi_ev_match_gpe_method, NULL,
					&walk_info, NULL);

	/* Return the new block */

	if (return_gpe_block) {
		(*return_gpe_block) = gpe_block;
	}

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
			      "    Initialized GPE %02X to %02X [%4.4s] %u regs on interrupt 0x%X%s\n",
			      (u32)gpe_block->block_base_number,
			      (u32)(gpe_block->block_base_number +
				    (gpe_block->gpe_count - 1)),
			      gpe_device->name.ascii, gpe_block->register_count,
			      interrupt_number,
			      interrupt_number ==
			      acpi_gbl_FADT.sci_interrupt ? " (SCI)" : ""));

	/* Update global count of currently available GPEs */

	acpi_current_gpe_count += gpe_block->gpe_count;
	return_ACPI_STATUS(AE_OK);
}