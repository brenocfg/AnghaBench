#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {union acpi_operand_object* object; int /*<<< orphan*/  class; } ;
struct TYPE_19__ {union acpi_operand_object* data_obj; union acpi_operand_object* index_obj; } ;
struct TYPE_18__ {union acpi_operand_object* region_obj; union acpi_operand_object* bank_obj; } ;
struct TYPE_17__ {union acpi_operand_object* region_obj; } ;
struct TYPE_16__ {union acpi_operand_object* buffer_obj; } ;
struct TYPE_15__ {int type; } ;
struct TYPE_14__ {size_t count; union acpi_operand_object** elements; } ;
struct TYPE_13__ {union acpi_operand_object** next; } ;
struct TYPE_12__ {union acpi_operand_object** notify_list; } ;
union acpi_operand_object {TYPE_9__ reference; TYPE_8__ index_field; TYPE_7__ bank_field; TYPE_6__ field; TYPE_5__ buffer_field; TYPE_4__ common; TYPE_3__ package; TYPE_2__ notify; TYPE_1__ common_notify; } ;
struct TYPE_11__ {union acpi_operand_object* object; } ;
union acpi_generic_state {TYPE_10__ update; } ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 size_t ACPI_NUM_NOTIFY_TYPES ; 
 int /*<<< orphan*/  ACPI_REFCLASS_INDEX ; 
 int /*<<< orphan*/  ACPI_REFCLASS_NAME ; 
#define  ACPI_TYPE_BUFFER 141 
#define  ACPI_TYPE_BUFFER_FIELD 140 
#define  ACPI_TYPE_DEVICE 139 
#define  ACPI_TYPE_INTEGER 138 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 137 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 136 
#define  ACPI_TYPE_LOCAL_REFERENCE 135 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 134 
#define  ACPI_TYPE_PACKAGE 133 
#define  ACPI_TYPE_POWER 132 
#define  ACPI_TYPE_PROCESSOR 131 
#define  ACPI_TYPE_REGION 130 
#define  ACPI_TYPE_STRING 129 
#define  ACPI_TYPE_THERMAL 128 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ut_create_update_state_and_push (union acpi_operand_object*,int /*<<< orphan*/ ,union acpi_generic_state**) ; 
 int /*<<< orphan*/  acpi_ut_delete_generic_state (union acpi_generic_state*) ; 
 union acpi_generic_state* acpi_ut_pop_generic_state (union acpi_generic_state**) ; 
 int /*<<< orphan*/  acpi_ut_update_ref_count (union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_update_object_reference ; 

acpi_status
acpi_ut_update_object_reference(union acpi_operand_object *object, u16 action)
{
	acpi_status status = AE_OK;
	union acpi_generic_state *state_list = NULL;
	union acpi_operand_object *next_object = NULL;
	union acpi_operand_object *prev_object;
	union acpi_generic_state *state;
	u32 i;

	ACPI_FUNCTION_NAME(ut_update_object_reference);

	while (object) {

		/* Make sure that this isn't a namespace handle */

		if (ACPI_GET_DESCRIPTOR_TYPE(object) == ACPI_DESC_TYPE_NAMED) {
			ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
					  "Object %p is NS handle\n", object));
			return (AE_OK);
		}

		/*
		 * All sub-objects must have their reference count incremented
		 * also. Different object types have different subobjects.
		 */
		switch (object->common.type) {
		case ACPI_TYPE_DEVICE:
		case ACPI_TYPE_PROCESSOR:
		case ACPI_TYPE_POWER:
		case ACPI_TYPE_THERMAL:
			/*
			 * Update the notify objects for these types (if present)
			 * Two lists, system and device notify handlers.
			 */
			for (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) {
				prev_object =
				    object->common_notify.notify_list[i];
				while (prev_object) {
					next_object =
					    prev_object->notify.next[i];
					acpi_ut_update_ref_count(prev_object,
								 action);
					prev_object = next_object;
				}
			}
			break;

		case ACPI_TYPE_PACKAGE:
			/*
			 * We must update all the sub-objects of the package,
			 * each of whom may have their own sub-objects.
			 */
			for (i = 0; i < object->package.count; i++) {
				/*
				 * Null package elements are legal and can be simply
				 * ignored.
				 */
				next_object = object->package.elements[i];
				if (!next_object) {
					continue;
				}

				switch (next_object->common.type) {
				case ACPI_TYPE_INTEGER:
				case ACPI_TYPE_STRING:
				case ACPI_TYPE_BUFFER:
					/*
					 * For these very simple sub-objects, we can just
					 * update the reference count here and continue.
					 * Greatly increases performance of this operation.
					 */
					acpi_ut_update_ref_count(next_object,
								 action);
					break;

				default:
					/*
					 * For complex sub-objects, push them onto the stack
					 * for later processing (this eliminates recursion.)
					 */
					status =
					    acpi_ut_create_update_state_and_push
					    (next_object, action, &state_list);
					if (ACPI_FAILURE(status)) {
						goto error_exit;
					}
					break;
				}
			}
			next_object = NULL;
			break;

		case ACPI_TYPE_BUFFER_FIELD:

			next_object = object->buffer_field.buffer_obj;
			break;

		case ACPI_TYPE_LOCAL_REGION_FIELD:

			next_object = object->field.region_obj;
			break;

		case ACPI_TYPE_LOCAL_BANK_FIELD:

			next_object = object->bank_field.bank_obj;
			status =
			    acpi_ut_create_update_state_and_push(object->
								 bank_field.
								 region_obj,
								 action,
								 &state_list);
			if (ACPI_FAILURE(status)) {
				goto error_exit;
			}
			break;

		case ACPI_TYPE_LOCAL_INDEX_FIELD:

			next_object = object->index_field.index_obj;
			status =
			    acpi_ut_create_update_state_and_push(object->
								 index_field.
								 data_obj,
								 action,
								 &state_list);
			if (ACPI_FAILURE(status)) {
				goto error_exit;
			}
			break;

		case ACPI_TYPE_LOCAL_REFERENCE:
			/*
			 * The target of an Index (a package, string, or buffer) or a named
			 * reference must track changes to the ref count of the index or
			 * target object.
			 */
			if ((object->reference.class == ACPI_REFCLASS_INDEX) ||
			    (object->reference.class == ACPI_REFCLASS_NAME)) {
				next_object = object->reference.object;
			}
			break;

		case ACPI_TYPE_REGION:
		default:

			break;	/* No subobjects for all other types */
		}

		/*
		 * Now we can update the count in the main object. This can only
		 * happen after we update the sub-objects in case this causes the
		 * main object to be deleted.
		 */
		acpi_ut_update_ref_count(object, action);
		object = NULL;

		/* Move on to the next object to be updated */

		if (next_object) {
			object = next_object;
			next_object = NULL;
		} else if (state_list) {
			state = acpi_ut_pop_generic_state(&state_list);
			object = state->update.object;
			acpi_ut_delete_generic_state(state);
		}
	}

	return (AE_OK);

error_exit:

	ACPI_EXCEPTION((AE_INFO, status,
			"Could not update object reference count"));

	/* Free any stacked Update State objects */

	while (state_list) {
		state = acpi_ut_pop_generic_state(&state_list);
		acpi_ut_delete_generic_state(state);
	}

	return (status);
}