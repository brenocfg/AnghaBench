#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_8__ {int /*<<< orphan*/ * handler; } ;
struct TYPE_7__ {scalar_t__ use_count; int /*<<< orphan*/  thread_id; int /*<<< orphan*/ * mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  integer; } ;
struct TYPE_6__ {int /*<<< orphan*/ * object; int /*<<< orphan*/ * peer; int /*<<< orphan*/ * child; int /*<<< orphan*/ * parent; int /*<<< orphan*/  type; int /*<<< orphan*/  descriptor_type; TYPE_1__ name; } ;

/* Variables and functions */
 size_t ACPI_ADDRESS_RANGE_MAX ; 
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_NAMED ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MUTEX_NOT_ACQUIRED ; 
 size_t ACPI_NUM_FIXED_EVENTS ; 
 size_t ACPI_NUM_MUTEX ; 
 size_t ACPI_NUM_OWNERID_MASKS ; 
 int /*<<< orphan*/  ACPI_ROOT_NAME ; 
 int /*<<< orphan*/  ACPI_SIZE_MAX ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  DEBUGGER_THREADING ; 
 void* FALSE ; 
 void* TRUE ; 
 scalar_t__ acpi_current_gpe_count ; 
 scalar_t__* acpi_fixed_event_count ; 
 int /*<<< orphan*/ * acpi_gbl_DSDT ; 
 void* acpi_gbl_acpi_hardware_present ; 
 int /*<<< orphan*/ ** acpi_gbl_address_range_list ; 
 void* acpi_gbl_all_gpes_initialized ; 
 void* acpi_gbl_cm_single_step ; 
 int /*<<< orphan*/  acpi_gbl_debugger_configuration ; 
 void* acpi_gbl_disable_mem_tracking ; 
 void* acpi_gbl_display_final_mem_stats ; 
 void* acpi_gbl_events_initialized ; 
 int /*<<< orphan*/ * acpi_gbl_exception_handler ; 
 int /*<<< orphan*/ * acpi_gbl_external_list ; 
 int /*<<< orphan*/ * acpi_gbl_global_event_handler ; 
 void* acpi_gbl_global_lock_acquired ; 
 scalar_t__ acpi_gbl_global_lock_handle ; 
 int /*<<< orphan*/ * acpi_gbl_global_lock_mutex ; 
 void* acpi_gbl_global_lock_present ; 
 int /*<<< orphan*/ * acpi_gbl_global_lock_semaphore ; 
 TYPE_4__* acpi_gbl_global_notify ; 
 int /*<<< orphan*/ ** acpi_gbl_gpe_fadt_blocks ; 
 int /*<<< orphan*/ * acpi_gbl_gpe_xrupt_list_head ; 
 int /*<<< orphan*/ * acpi_gbl_init_handler ; 
 int /*<<< orphan*/ * acpi_gbl_interface_handler ; 
 scalar_t__ acpi_gbl_last_owner_id_index ; 
 int /*<<< orphan*/  acpi_gbl_lowest_stack_pointer ; 
 TYPE_3__* acpi_gbl_mutex_info ; 
 scalar_t__ acpi_gbl_next_owner_id_offset ; 
 scalar_t__ acpi_gbl_ns_lookup_count ; 
 scalar_t__ acpi_gbl_num_external_methods ; 
 int /*<<< orphan*/ * acpi_gbl_osi_mutex ; 
 int* acpi_gbl_owner_id_mask ; 
 scalar_t__ acpi_gbl_ps_find_count ; 
 scalar_t__ acpi_gbl_resolved_external_methods ; 
 int /*<<< orphan*/ * acpi_gbl_root_node ; 
 TYPE_2__ acpi_gbl_root_node_struct ; 
 int /*<<< orphan*/ * acpi_gbl_sci_handler_list ; 
 void* acpi_gbl_shutdown ; 
 void* acpi_gbl_system_awake_and_running ; 
 int /*<<< orphan*/ * acpi_gbl_table_handler ; 
 scalar_t__ acpi_gpe_count ; 
 scalar_t__ acpi_method_count ; 
 scalar_t__ acpi_sci_count ; 
 int /*<<< orphan*/  acpi_size ; 
 int /*<<< orphan*/  acpi_ut_create_caches () ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_init_globals ; 

acpi_status acpi_ut_init_globals(void)
{
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TRACE(ut_init_globals);

	/* Create all memory caches */

	status = acpi_ut_create_caches();
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Address Range lists */

	for (i = 0; i < ACPI_ADDRESS_RANGE_MAX; i++) {
		acpi_gbl_address_range_list[i] = NULL;
	}

	/* Mutex locked flags */

	for (i = 0; i < ACPI_NUM_MUTEX; i++) {
		acpi_gbl_mutex_info[i].mutex = NULL;
		acpi_gbl_mutex_info[i].thread_id = ACPI_MUTEX_NOT_ACQUIRED;
		acpi_gbl_mutex_info[i].use_count = 0;
	}

	for (i = 0; i < ACPI_NUM_OWNERID_MASKS; i++) {
		acpi_gbl_owner_id_mask[i] = 0;
	}

	/* Last owner_ID is never valid */

	acpi_gbl_owner_id_mask[ACPI_NUM_OWNERID_MASKS - 1] = 0x80000000;

	/* Event counters */

	acpi_method_count = 0;
	acpi_sci_count = 0;
	acpi_gpe_count = 0;

	for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) {
		acpi_fixed_event_count[i] = 0;
	}

#if (!ACPI_REDUCED_HARDWARE)

	/* GPE/SCI support */

	acpi_gbl_all_gpes_initialized = FALSE;
	acpi_gbl_gpe_xrupt_list_head = NULL;
	acpi_gbl_gpe_fadt_blocks[0] = NULL;
	acpi_gbl_gpe_fadt_blocks[1] = NULL;
	acpi_current_gpe_count = 0;

	acpi_gbl_global_event_handler = NULL;
	acpi_gbl_sci_handler_list = NULL;

#endif				/* !ACPI_REDUCED_HARDWARE */

	/* Global handlers */

	acpi_gbl_global_notify[0].handler = NULL;
	acpi_gbl_global_notify[1].handler = NULL;
	acpi_gbl_exception_handler = NULL;
	acpi_gbl_init_handler = NULL;
	acpi_gbl_table_handler = NULL;
	acpi_gbl_interface_handler = NULL;

	/* Global Lock support */

	acpi_gbl_global_lock_semaphore = NULL;
	acpi_gbl_global_lock_mutex = NULL;
	acpi_gbl_global_lock_acquired = FALSE;
	acpi_gbl_global_lock_handle = 0;
	acpi_gbl_global_lock_present = FALSE;

	/* Miscellaneous variables */

	acpi_gbl_DSDT = NULL;
	acpi_gbl_cm_single_step = FALSE;
	acpi_gbl_shutdown = FALSE;
	acpi_gbl_ns_lookup_count = 0;
	acpi_gbl_ps_find_count = 0;
	acpi_gbl_acpi_hardware_present = TRUE;
	acpi_gbl_last_owner_id_index = 0;
	acpi_gbl_next_owner_id_offset = 0;
	acpi_gbl_debugger_configuration = DEBUGGER_THREADING;
	acpi_gbl_osi_mutex = NULL;

	/* Hardware oriented */

	acpi_gbl_events_initialized = FALSE;
	acpi_gbl_system_awake_and_running = TRUE;

	/* Namespace */

	acpi_gbl_root_node = NULL;
	acpi_gbl_root_node_struct.name.integer = ACPI_ROOT_NAME;
	acpi_gbl_root_node_struct.descriptor_type = ACPI_DESC_TYPE_NAMED;
	acpi_gbl_root_node_struct.type = ACPI_TYPE_DEVICE;
	acpi_gbl_root_node_struct.parent = NULL;
	acpi_gbl_root_node_struct.child = NULL;
	acpi_gbl_root_node_struct.peer = NULL;
	acpi_gbl_root_node_struct.object = NULL;

#ifdef ACPI_DISASSEMBLER
	acpi_gbl_external_list = NULL;
	acpi_gbl_num_external_methods = 0;
	acpi_gbl_resolved_external_methods = 0;
#endif

#ifdef ACPI_DEBUG_OUTPUT
	acpi_gbl_lowest_stack_pointer = ACPI_CAST_PTR(acpi_size, ACPI_SIZE_MAX);
#endif

#ifdef ACPI_DBG_TRACK_ALLOCATIONS
	acpi_gbl_display_final_mem_stats = FALSE;
	acpi_gbl_disable_mem_tracking = FALSE;
#endif

	return_ACPI_STATUS(AE_OK);
}