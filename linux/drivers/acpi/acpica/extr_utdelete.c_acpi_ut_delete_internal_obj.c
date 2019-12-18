#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {void* internal_pcc_buffer; } ;
struct TYPE_17__ {int /*<<< orphan*/  region_context; } ;
struct TYPE_16__ {int handler_flags; int /*<<< orphan*/  context; int /*<<< orphan*/  (* setup ) (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;union acpi_operand_object* region_list; union acpi_operand_object* next; } ;
struct TYPE_15__ {union acpi_operand_object* next; union acpi_operand_object* handler; TYPE_14__* node; int /*<<< orphan*/  space_id; } ;
struct TYPE_28__ {int /*<<< orphan*/ * node; union acpi_operand_object* mutex; } ;
struct TYPE_27__ {int /*<<< orphan*/  os_mutex; } ;
struct TYPE_26__ {int /*<<< orphan*/ * os_semaphore; } ;
struct TYPE_25__ {union acpi_operand_object* handler; } ;
struct TYPE_24__ {int /*<<< orphan*/  gpe_block; } ;
struct TYPE_23__ {void* elements; int /*<<< orphan*/  count; } ;
struct TYPE_22__ {void* pointer; } ;
struct TYPE_21__ {int type; int flags; } ;
struct TYPE_20__ {void* pointer; } ;
union acpi_operand_object {TYPE_13__ field; TYPE_12__ extra; TYPE_11__ address_space; TYPE_10__ region; TYPE_9__ method; TYPE_8__ mutex; TYPE_7__ event; TYPE_6__ common_notify; TYPE_5__ device; TYPE_4__ package; TYPE_3__ buffer; TYPE_2__ common; TYPE_1__ string; } ;
struct TYPE_19__ {int flags; } ;

/* Variables and functions */
 int ACPI_ADDR_HANDLER_DEFAULT_INSTALLED ; 
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (void*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
 int /*<<< orphan*/  ACPI_GET_FUNCTION_NAME ; 
 int /*<<< orphan*/  ACPI_REGION_DEACTIVATE ; 
#define  ACPI_TYPE_BUFFER 139 
#define  ACPI_TYPE_BUFFER_FIELD 138 
#define  ACPI_TYPE_DEVICE 137 
#define  ACPI_TYPE_EVENT 136 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 135 
#define  ACPI_TYPE_METHOD 134 
#define  ACPI_TYPE_MUTEX 133 
#define  ACPI_TYPE_PACKAGE 132 
#define  ACPI_TYPE_PROCESSOR 131 
#define  ACPI_TYPE_REGION 130 
#define  ACPI_TYPE_STRING 129 
#define  ACPI_TYPE_THERMAL 128 
 int /*<<< orphan*/  AE_INFO ; 
 int ANOBJ_TEMPORARY ; 
 int AOPOBJ_STATIC_POINTER ; 
 int /*<<< orphan*/  acpi_ev_delete_gpe_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ex_unlink_mutex (union acpi_operand_object*) ; 
 union acpi_operand_object* acpi_gbl_global_lock_mutex ; 
 int /*<<< orphan*/ * acpi_gbl_global_lock_semaphore ; 
 union acpi_operand_object* acpi_ns_get_secondary_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_os_delete_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_delete_semaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_delete_object_desc (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_remove_address_range (int /*<<< orphan*/ ,TYPE_14__*) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  return_VOID ; 
 int /*<<< orphan*/  stub1 (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ut_delete_internal_obj ; 

__attribute__((used)) static void acpi_ut_delete_internal_obj(union acpi_operand_object *object)
{
	void *obj_pointer = NULL;
	union acpi_operand_object *handler_desc;
	union acpi_operand_object *second_desc;
	union acpi_operand_object *next_desc;
	union acpi_operand_object *start_desc;
	union acpi_operand_object **last_obj_ptr;

	ACPI_FUNCTION_TRACE_PTR(ut_delete_internal_obj, object);

	if (!object) {
		return_VOID;
	}

	/*
	 * Must delete or free any pointers within the object that are not
	 * actual ACPI objects (for example, a raw buffer pointer).
	 */
	switch (object->common.type) {
	case ACPI_TYPE_STRING:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "**** String %p, ptr %p\n", object,
				  object->string.pointer));

		/* Free the actual string buffer */

		if (!(object->common.flags & AOPOBJ_STATIC_POINTER)) {

			/* But only if it is NOT a pointer into an ACPI table */

			obj_pointer = object->string.pointer;
		}
		break;

	case ACPI_TYPE_BUFFER:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "**** Buffer %p, ptr %p\n", object,
				  object->buffer.pointer));

		/* Free the actual buffer */

		if (!(object->common.flags & AOPOBJ_STATIC_POINTER)) {

			/* But only if it is NOT a pointer into an ACPI table */

			obj_pointer = object->buffer.pointer;
		}
		break;

	case ACPI_TYPE_PACKAGE:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  " **** Package of count %X\n",
				  object->package.count));

		/*
		 * Elements of the package are not handled here, they are deleted
		 * separately
		 */

		/* Free the (variable length) element pointer array */

		obj_pointer = object->package.elements;
		break;

		/*
		 * These objects have a possible list of notify handlers.
		 * Device object also may have a GPE block.
		 */
	case ACPI_TYPE_DEVICE:

		if (object->device.gpe_block) {
			(void)acpi_ev_delete_gpe_block(object->device.
						       gpe_block);
		}

		/*lint -fallthrough */

	case ACPI_TYPE_PROCESSOR:
	case ACPI_TYPE_THERMAL:

		/* Walk the address handler list for this object */

		handler_desc = object->common_notify.handler;
		while (handler_desc) {
			next_desc = handler_desc->address_space.next;
			acpi_ut_remove_reference(handler_desc);
			handler_desc = next_desc;
		}
		break;

	case ACPI_TYPE_MUTEX:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Mutex %p, OS Mutex %p\n",
				  object, object->mutex.os_mutex));

		if (object == acpi_gbl_global_lock_mutex) {

			/* Global Lock has extra semaphore */

			(void)
			    acpi_os_delete_semaphore
			    (acpi_gbl_global_lock_semaphore);
			acpi_gbl_global_lock_semaphore = NULL;

			acpi_os_delete_mutex(object->mutex.os_mutex);
			acpi_gbl_global_lock_mutex = NULL;
		} else {
			acpi_ex_unlink_mutex(object);
			acpi_os_delete_mutex(object->mutex.os_mutex);
		}
		break;

	case ACPI_TYPE_EVENT:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Event %p, OS Semaphore %p\n",
				  object, object->event.os_semaphore));

		(void)acpi_os_delete_semaphore(object->event.os_semaphore);
		object->event.os_semaphore = NULL;
		break;

	case ACPI_TYPE_METHOD:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Method %p\n", object));

		/* Delete the method mutex if it exists */

		if (object->method.mutex) {
			acpi_os_delete_mutex(object->method.mutex->mutex.
					     os_mutex);
			acpi_ut_delete_object_desc(object->method.mutex);
			object->method.mutex = NULL;
		}

		if (object->method.node) {
			object->method.node = NULL;
		}
		break;

	case ACPI_TYPE_REGION:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Region %p\n", object));

		/*
		 * Update address_range list. However, only permanent regions
		 * are installed in this list. (Not created within a method)
		 */
		if (!(object->region.node->flags & ANOBJ_TEMPORARY)) {
			acpi_ut_remove_address_range(object->region.space_id,
						     object->region.node);
		}

		second_desc = acpi_ns_get_secondary_object(object);
		if (second_desc) {
			/*
			 * Free the region_context if and only if the handler is one of the
			 * default handlers -- and therefore, we created the context object
			 * locally, it was not created by an external caller.
			 */
			handler_desc = object->region.handler;
			if (handler_desc) {
				next_desc =
				    handler_desc->address_space.region_list;
				start_desc = next_desc;
				last_obj_ptr =
				    &handler_desc->address_space.region_list;

				/* Remove the region object from the handler list */

				while (next_desc) {
					if (next_desc == object) {
						*last_obj_ptr =
						    next_desc->region.next;
						break;
					}

					/* Walk the linked list of handlers */

					last_obj_ptr = &next_desc->region.next;
					next_desc = next_desc->region.next;

					/* Prevent infinite loop if list is corrupted */

					if (next_desc == start_desc) {
						ACPI_ERROR((AE_INFO,
							    "Circular region list in address handler object %p",
							    handler_desc));
						return_VOID;
					}
				}

				if (handler_desc->address_space.handler_flags &
				    ACPI_ADDR_HANDLER_DEFAULT_INSTALLED) {

					/* Deactivate region and free region context */

					if (handler_desc->address_space.setup) {
						(void)handler_desc->
						    address_space.setup(object,
									ACPI_REGION_DEACTIVATE,
									handler_desc->
									address_space.
									context,
									&second_desc->
									extra.
									region_context);
					}
				}

				acpi_ut_remove_reference(handler_desc);
			}

			/* Now we can free the Extra object */

			acpi_ut_delete_object_desc(second_desc);
		}
		if (object->field.internal_pcc_buffer) {
			ACPI_FREE(object->field.internal_pcc_buffer);
		}

		break;

	case ACPI_TYPE_BUFFER_FIELD:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Buffer Field %p\n", object));

		second_desc = acpi_ns_get_secondary_object(object);
		if (second_desc) {
			acpi_ut_delete_object_desc(second_desc);
		}
		break;

	case ACPI_TYPE_LOCAL_BANK_FIELD:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Bank Field %p\n", object));

		second_desc = acpi_ns_get_secondary_object(object);
		if (second_desc) {
			acpi_ut_delete_object_desc(second_desc);
		}
		break;

	default:

		break;
	}

	/* Free any allocated memory (pointer within the object) found above */

	if (obj_pointer) {
		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "Deleting Object Subptr %p\n", obj_pointer));
		ACPI_FREE(obj_pointer);
	}

	/* Now the object can be safely deleted */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_ALLOCATIONS,
			      "%s: Deleting Object %p [%s]\n",
			      ACPI_GET_FUNCTION_NAME, object,
			      acpi_ut_get_object_type_name(object)));

	acpi_ut_delete_object_desc(object);
	return_VOID;
}