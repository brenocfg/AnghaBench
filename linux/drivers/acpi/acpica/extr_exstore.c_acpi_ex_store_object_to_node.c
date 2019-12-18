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
struct TYPE_4__ {int const type; } ;
union acpi_operand_object {TYPE_2__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
struct acpi_walk_state {scalar_t__ opcode; int /*<<< orphan*/  result_obj; } ;
struct TYPE_3__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {int type; TYPE_1__ name; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_operand_object*) ; 
#define  ACPI_TYPE_BUFFER 142 
#define  ACPI_TYPE_BUFFER_FIELD 141 
#define  ACPI_TYPE_DEVICE 140 
#define  ACPI_TYPE_EVENT 139 
#define  ACPI_TYPE_INTEGER 138 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 137 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 136 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 135 
#define  ACPI_TYPE_MUTEX 134 
#define  ACPI_TYPE_PACKAGE 133 
#define  ACPI_TYPE_POWER 132 
#define  ACPI_TYPE_PROCESSOR 131 
#define  ACPI_TYPE_REGION 130 
#define  ACPI_TYPE_STRING 129 
#define  ACPI_TYPE_THERMAL 128 
 int /*<<< orphan*/  AE_AML_TARGET_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AML_COPY_OBJECT_OP ; 
 scalar_t__ AML_STORE_OP ; 
 int /*<<< orphan*/  acpi_ex_resolve_object (union acpi_operand_object**,int,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_store_direct_to_node (union acpi_operand_object*,struct acpi_namespace_node*,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_store_object_to_object (union acpi_operand_object*,union acpi_operand_object*,union acpi_operand_object**,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  acpi_ex_write_data_to_field (union acpi_operand_object*,union acpi_operand_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,int const) ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int acpi_ns_get_type (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_get_object_type_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int) ; 
 int /*<<< orphan*/  ex_store_object_to_node ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_store_object_to_node(union acpi_operand_object *source_desc,
			     struct acpi_namespace_node *node,
			     struct acpi_walk_state *walk_state,
			     u8 implicit_conversion)
{
	acpi_status status = AE_OK;
	union acpi_operand_object *target_desc;
	union acpi_operand_object *new_desc;
	acpi_object_type target_type;

	ACPI_FUNCTION_TRACE_PTR(ex_store_object_to_node, source_desc);

	/* Get current type of the node, and object attached to Node */

	target_type = acpi_ns_get_type(node);
	target_desc = acpi_ns_get_attached_object(node);

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Storing %p [%s] to node %p [%s]\n",
			  source_desc,
			  acpi_ut_get_object_type_name(source_desc), node,
			  acpi_ut_get_type_name(target_type)));

	/* Only limited target types possible for everything except copy_object */

	if (walk_state->opcode != AML_COPY_OBJECT_OP) {
		/*
		 * Only copy_object allows all object types to be overwritten. For
		 * target_ref(s), there are restrictions on the object types that
		 * are allowed.
		 *
		 * Allowable operations/typing for Store:
		 *
		 * 1) Simple Store
		 *      Integer     --> Integer (Named/Local/Arg)
		 *      String      --> String  (Named/Local/Arg)
		 *      Buffer      --> Buffer  (Named/Local/Arg)
		 *      Package     --> Package (Named/Local/Arg)
		 *
		 * 2) Store with implicit conversion
		 *      Integer     --> String or Buffer  (Named)
		 *      String      --> Integer or Buffer (Named)
		 *      Buffer      --> Integer or String (Named)
		 */
		switch (target_type) {
		case ACPI_TYPE_PACKAGE:
			/*
			 * Here, can only store a package to an existing package.
			 * Storing a package to a Local/Arg is OK, and handled
			 * elsewhere.
			 */
			if (walk_state->opcode == AML_STORE_OP) {
				if (source_desc->common.type !=
				    ACPI_TYPE_PACKAGE) {
					ACPI_ERROR((AE_INFO,
						    "Cannot assign type [%s] to [Package] "
						    "(source must be type Pkg)",
						    acpi_ut_get_object_type_name
						    (source_desc)));

					return_ACPI_STATUS(AE_AML_TARGET_TYPE);
				}
				break;
			}

			/* Fallthrough */

		case ACPI_TYPE_DEVICE:
		case ACPI_TYPE_EVENT:
		case ACPI_TYPE_MUTEX:
		case ACPI_TYPE_REGION:
		case ACPI_TYPE_POWER:
		case ACPI_TYPE_PROCESSOR:
		case ACPI_TYPE_THERMAL:

			ACPI_ERROR((AE_INFO,
				    "Target must be [Buffer/Integer/String/Reference]"
				    ", found [%s] (%4.4s)",
				    acpi_ut_get_type_name(node->type),
				    node->name.ascii));

			return_ACPI_STATUS(AE_AML_TARGET_TYPE);

		default:
			break;
		}
	}

	/*
	 * Resolve the source object to an actual value
	 * (If it is a reference object)
	 */
	status = acpi_ex_resolve_object(&source_desc, target_type, walk_state);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Do the actual store operation */

	switch (target_type) {
		/*
		 * The simple data types all support implicit source operand
		 * conversion before the store.
		 */
	case ACPI_TYPE_INTEGER:
	case ACPI_TYPE_STRING:
	case ACPI_TYPE_BUFFER:

		if ((walk_state->opcode == AML_COPY_OBJECT_OP) ||
		    !implicit_conversion) {
			/*
			 * However, copy_object and Stores to arg_x do not perform
			 * an implicit conversion, as per the ACPI specification.
			 * A direct store is performed instead.
			 */
			status =
			    acpi_ex_store_direct_to_node(source_desc, node,
							 walk_state);
			break;
		}

		/* Store with implicit source operand conversion support */

		status =
		    acpi_ex_store_object_to_object(source_desc, target_desc,
						   &new_desc, walk_state);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		if (new_desc != target_desc) {
			/*
			 * Store the new new_desc as the new value of the Name, and set
			 * the Name's type to that of the value being stored in it.
			 * source_desc reference count is incremented by attach_object.
			 *
			 * Note: This may change the type of the node if an explicit
			 * store has been performed such that the node/object type
			 * has been changed.
			 */
			status =
			    acpi_ns_attach_object(node, new_desc,
						  new_desc->common.type);

			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "Store type [%s] into [%s] via Convert/Attach\n",
					  acpi_ut_get_object_type_name
					  (source_desc),
					  acpi_ut_get_object_type_name
					  (new_desc)));
		}
		break;

	case ACPI_TYPE_BUFFER_FIELD:
	case ACPI_TYPE_LOCAL_REGION_FIELD:
	case ACPI_TYPE_LOCAL_BANK_FIELD:
	case ACPI_TYPE_LOCAL_INDEX_FIELD:
		/*
		 * For all fields, always write the source data to the target
		 * field. Any required implicit source operand conversion is
		 * performed in the function below as necessary. Note, field
		 * objects must retain their original type permanently.
		 */
		status = acpi_ex_write_data_to_field(source_desc, target_desc,
						     &walk_state->result_obj);
		break;

	default:
		/*
		 * copy_object operator: No conversions for all other types.
		 * Instead, directly store a copy of the source object.
		 *
		 * This is the ACPI spec-defined behavior for the copy_object
		 * operator. (Note, for this default case, all normal
		 * Store/Target operations exited above with an error).
		 */
		status =
		    acpi_ex_store_direct_to_node(source_desc, node, walk_state);
		break;
	}

	return_ACPI_STATUS(status);
}