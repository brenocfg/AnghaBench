#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* path; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {struct acpi_namespace_node* node; } ;
union acpi_parse_object {TYPE_4__ named; TYPE_3__ common; } ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {int opcode; int parse_flags; int /*<<< orphan*/  parser_state; int /*<<< orphan*/  aml; TYPE_6__* scope_info; int /*<<< orphan*/  namespace_override; int /*<<< orphan*/  method_node; struct acpi_namespace_node* deferred_node; TYPE_1__* op_info; union acpi_parse_object* op; } ;
struct TYPE_12__ {int /*<<< orphan*/  integer; } ;
struct acpi_namespace_node {int type; int flags; TYPE_5__ name; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int acpi_object_type ;
struct TYPE_9__ {int value; } ;
struct TYPE_13__ {TYPE_2__ common; } ;
struct TYPE_8__ {int flags; int object_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int /*<<< orphan*/  ACPI_NS_ERROR_IF_FOUND ; 
 int /*<<< orphan*/  ACPI_NS_NO_UPSEARCH ; 
 int /*<<< orphan*/  ACPI_NS_OVERRIDE_IF_FOUND ; 
 int /*<<< orphan*/  ACPI_NS_SEARCH_PARENT ; 
 int ACPI_PARSE_DEFERRED_OP ; 
 int ACPI_PARSE_MODULE_LEVEL ; 
#define  ACPI_TYPE_ANY 138 
#define  ACPI_TYPE_BUFFER 137 
#define  ACPI_TYPE_DEVICE 136 
#define  ACPI_TYPE_INTEGER 135 
#define  ACPI_TYPE_LOCAL_SCOPE 134 
#define  ACPI_TYPE_METHOD 133 
#define  ACPI_TYPE_POWER 132 
#define  ACPI_TYPE_PROCESSOR 131 
#define  ACPI_TYPE_STRING 130 
#define  ACPI_TYPE_THERMAL 129 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int AML_NAMED ; 
#define  AML_SCOPE_OP 128 
 int ANOBJ_IS_EXTERNAL ; 
 int /*<<< orphan*/  acpi_dm_add_op_to_external_list (union acpi_parse_object*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ds_scope_stack_push (struct acpi_namespace_node*,int,struct acpi_walk_state*) ; 
 struct acpi_namespace_node* acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_ns_lookup (TYPE_6__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_walk_state*,struct acpi_namespace_node**) ; 
 int /*<<< orphan*/  acpi_ns_opens_scope (int) ; 
 union acpi_parse_object* acpi_ps_alloc_op (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_append_arg (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 char* acpi_ps_get_next_namestring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ps_get_parent_scope (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (int) ; 
 int /*<<< orphan*/  ds_load1_begin_op ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_load1_begin_op(struct acpi_walk_state *walk_state,
		       union acpi_parse_object **out_op)
{
	union acpi_parse_object *op;
	struct acpi_namespace_node *node;
	acpi_status status;
	acpi_object_type object_type;
	char *path;
	u32 flags;

	ACPI_FUNCTION_TRACE_PTR(ds_load1_begin_op, walk_state->op);

	op = walk_state->op;
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "Op=%p State=%p\n", op,
			  walk_state));

	/* We are only interested in opcodes that have an associated name */

	if (op) {
		if (!(walk_state->op_info->flags & AML_NAMED)) {
			*out_op = op;
			return_ACPI_STATUS(AE_OK);
		}

		/* Check if this object has already been installed in the namespace */

		if (op->common.node) {
			*out_op = op;
			return_ACPI_STATUS(AE_OK);
		}
	}

	path = acpi_ps_get_next_namestring(&walk_state->parser_state);

	/* Map the raw opcode into an internal object type */

	object_type = walk_state->op_info->object_type;

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "State=%p Op=%p [%s]\n", walk_state, op,
			  acpi_ut_get_type_name(object_type)));

	switch (walk_state->opcode) {
	case AML_SCOPE_OP:
		/*
		 * The target name of the Scope() operator must exist at this point so
		 * that we can actually open the scope to enter new names underneath it.
		 * Allow search-to-root for single namesegs.
		 */
		status =
		    acpi_ns_lookup(walk_state->scope_info, path, object_type,
				   ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT,
				   walk_state, &(node));
#ifdef ACPI_ASL_COMPILER
		if (status == AE_NOT_FOUND) {
			/*
			 * Table disassembly:
			 * Target of Scope() not found. Generate an External for it, and
			 * insert the name into the namespace.
			 */
			acpi_dm_add_op_to_external_list(op, path,
							ACPI_TYPE_DEVICE, 0, 0);
			status =
			    acpi_ns_lookup(walk_state->scope_info, path,
					   object_type, ACPI_IMODE_LOAD_PASS1,
					   ACPI_NS_SEARCH_PARENT, walk_state,
					   &node);
		}
#endif
		if (ACPI_FAILURE(status)) {
			ACPI_ERROR_NAMESPACE(walk_state->scope_info, path,
					     status);
			return_ACPI_STATUS(status);
		}

		/*
		 * Check to make sure that the target is
		 * one of the opcodes that actually opens a scope
		 */
		switch (node->type) {
		case ACPI_TYPE_ANY:
		case ACPI_TYPE_LOCAL_SCOPE:	/* Scope  */
		case ACPI_TYPE_DEVICE:
		case ACPI_TYPE_POWER:
		case ACPI_TYPE_PROCESSOR:
		case ACPI_TYPE_THERMAL:

			/* These are acceptable types */
			break;

		case ACPI_TYPE_INTEGER:
		case ACPI_TYPE_STRING:
		case ACPI_TYPE_BUFFER:
			/*
			 * These types we will allow, but we will change the type.
			 * This enables some existing code of the form:
			 *
			 *  Name (DEB, 0)
			 *  Scope (DEB) { ... }
			 *
			 * Note: silently change the type here. On the second pass,
			 * we will report a warning
			 */
			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					  "Type override - [%4.4s] had invalid type (%s) "
					  "for Scope operator, changed to type ANY\n",
					  acpi_ut_get_node_name(node),
					  acpi_ut_get_type_name(node->type)));

			node->type = ACPI_TYPE_ANY;
			walk_state->scope_info->common.value = ACPI_TYPE_ANY;
			break;

		case ACPI_TYPE_METHOD:
			/*
			 * Allow scope change to root during execution of module-level
			 * code. Root is typed METHOD during this time.
			 */
			if ((node == acpi_gbl_root_node) &&
			    (walk_state->
			     parse_flags & ACPI_PARSE_MODULE_LEVEL)) {
				break;
			}

			/*lint -fallthrough */

		default:

			/* All other types are an error */

			ACPI_ERROR((AE_INFO,
				    "Invalid type (%s) for target of "
				    "Scope operator [%4.4s] (Cannot override)",
				    acpi_ut_get_type_name(node->type),
				    acpi_ut_get_node_name(node)));

			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}
		break;

	default:
		/*
		 * For all other named opcodes, we will enter the name into
		 * the namespace.
		 *
		 * Setup the search flags.
		 * Since we are entering a name into the namespace, we do not want to
		 * enable the search-to-root upsearch.
		 *
		 * There are only two conditions where it is acceptable that the name
		 * already exists:
		 *    1) the Scope() operator can reopen a scoping object that was
		 *       previously defined (Scope, Method, Device, etc.)
		 *    2) Whenever we are parsing a deferred opcode (op_region, Buffer,
		 *       buffer_field, or Package), the name of the object is already
		 *       in the namespace.
		 */
		if (walk_state->deferred_node) {

			/* This name is already in the namespace, get the node */

			node = walk_state->deferred_node;
			status = AE_OK;
			break;
		}

		/*
		 * If we are executing a method, do not create any namespace objects
		 * during the load phase, only during execution.
		 */
		if (walk_state->method_node) {
			node = NULL;
			status = AE_OK;
			break;
		}

		flags = ACPI_NS_NO_UPSEARCH;
		if ((walk_state->opcode != AML_SCOPE_OP) &&
		    (!(walk_state->parse_flags & ACPI_PARSE_DEFERRED_OP))) {
			if (walk_state->namespace_override) {
				flags |= ACPI_NS_OVERRIDE_IF_FOUND;
				ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
						  "[%s] Override allowed\n",
						  acpi_ut_get_type_name
						  (object_type)));
			} else {
				flags |= ACPI_NS_ERROR_IF_FOUND;
				ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
						  "[%s] Cannot already exist\n",
						  acpi_ut_get_type_name
						  (object_type)));
			}
		} else {
			ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
					  "[%s] Both Find or Create allowed\n",
					  acpi_ut_get_type_name(object_type)));
		}

		/*
		 * Enter the named type into the internal namespace. We enter the name
		 * as we go downward in the parse tree. Any necessary subobjects that
		 * involve arguments to the opcode must be created as we go back up the
		 * parse tree later.
		 */
		status =
		    acpi_ns_lookup(walk_state->scope_info, path, object_type,
				   ACPI_IMODE_LOAD_PASS1, flags, walk_state,
				   &node);
		if (ACPI_FAILURE(status)) {
			if (status == AE_ALREADY_EXISTS) {

				/* The name already exists in this scope */

				if (node->flags & ANOBJ_IS_EXTERNAL) {
					/*
					 * Allow one create on an object or segment that was
					 * previously declared External
					 */
					node->flags &= ~ANOBJ_IS_EXTERNAL;
					node->type = (u8) object_type;

					/* Just retyped a node, probably will need to open a scope */

					if (acpi_ns_opens_scope(object_type)) {
						status =
						    acpi_ds_scope_stack_push
						    (node, object_type,
						     walk_state);
						if (ACPI_FAILURE(status)) {
							return_ACPI_STATUS
							    (status);
						}
					}

					status = AE_OK;
				}
			}

			if (ACPI_FAILURE(status)) {
				ACPI_ERROR_NAMESPACE(walk_state->scope_info,
						     path, status);
				return_ACPI_STATUS(status);
			}
		}
		break;
	}

	/* Common exit */

	if (!op) {

		/* Create a new op */

		op = acpi_ps_alloc_op(walk_state->opcode, walk_state->aml);
		if (!op) {
			return_ACPI_STATUS(AE_NO_MEMORY);
		}
	}

	/* Initialize the op */

#ifdef ACPI_CONSTANT_EVAL_ONLY
	op->named.path = path;
#endif

	if (node) {
		/*
		 * Put the Node in the "op" object that the parser uses, so we
		 * can get it again quickly when this scope is closed
		 */
		op->common.node = node;
		op->named.name = node->name.integer;
	}

	acpi_ps_append_arg(acpi_ps_get_parent_scope(&walk_state->parser_state),
			   op);
	*out_op = op;
	return_ACPI_STATUS(status);
}