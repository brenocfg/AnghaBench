#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {void* length; int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {int aml_opcode; TYPE_2__* parent; int /*<<< orphan*/  aml_op_name; } ;
union acpi_parse_object {TYPE_4__ named; TYPE_3__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct TYPE_16__ {int /*<<< orphan*/ * pkg_end; int /*<<< orphan*/ * aml; } ;
struct acpi_walk_state {TYPE_7__ parser_state; TYPE_6__* control_state; int /*<<< orphan*/  arg_count; int /*<<< orphan*/  pass_number; int /*<<< orphan*/  arg_types; int /*<<< orphan*/ * aml; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_14__ {int /*<<< orphan*/ * package_end; } ;
struct TYPE_15__ {TYPE_5__ control; } ;
struct TYPE_10__ {int /*<<< orphan*/  aml_opcode; } ;
struct TYPE_11__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_walk_state*) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS2 ; 
 int /*<<< orphan*/  ACPI_POSSIBLE_METHOD_CALL ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_BUFFER_OP 138 
#define  AML_BYTE_OP 137 
#define  AML_DWORD_OP 136 
#define  AML_INT_NAMEPATH_OP 135 
#define  AML_METHOD_OP 134 
 int /*<<< orphan*/  AML_NAME_OP ; 
#define  AML_PACKAGE_OP 133 
#define  AML_QWORD_OP 132 
#define  AML_STRING_OP 131 
#define  AML_VARIABLE_PACKAGE_OP 130 
#define  AML_WHILE_OP 129 
#define  AML_WORD_OP 128 
 int /*<<< orphan*/  ASL_CV_CAPTURE_COMMENTS (struct acpi_walk_state*) ; 
 int /*<<< orphan*/  GET_CURRENT_ARG_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INCREMENT_ARG_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_append_arg (union acpi_parse_object*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ps_get_next_arg (struct acpi_walk_state*,TYPE_7__*,int /*<<< orphan*/ ,union acpi_parse_object**) ; 
 int /*<<< orphan*/  acpi_ps_get_next_namepath (struct acpi_walk_state*,TYPE_7__*,union acpi_parse_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ps_get_next_simple_arg (TYPE_7__*,int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ps_get_arguments ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_ps_get_arguments(struct acpi_walk_state *walk_state,
		      u8 * aml_op_start, union acpi_parse_object *op)
{
	acpi_status status = AE_OK;
	union acpi_parse_object *arg = NULL;

	ACPI_FUNCTION_TRACE_PTR(ps_get_arguments, walk_state);

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
			  "Get arguments for opcode [%s]\n",
			  op->common.aml_op_name));

	switch (op->common.aml_opcode) {
	case AML_BYTE_OP:	/* AML_BYTEDATA_ARG */
	case AML_WORD_OP:	/* AML_WORDDATA_ARG */
	case AML_DWORD_OP:	/* AML_DWORDATA_ARG */
	case AML_QWORD_OP:	/* AML_QWORDATA_ARG */
	case AML_STRING_OP:	/* AML_ASCIICHARLIST_ARG */

		/* Fill in constant or string argument directly */

		acpi_ps_get_next_simple_arg(&(walk_state->parser_state),
					    GET_CURRENT_ARG_TYPE(walk_state->
								 arg_types),
					    op);
		break;

	case AML_INT_NAMEPATH_OP:	/* AML_NAMESTRING_ARG */

		status = acpi_ps_get_next_namepath(walk_state,
						   &(walk_state->parser_state),
						   op,
						   ACPI_POSSIBLE_METHOD_CALL);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

		walk_state->arg_types = 0;
		break;

	default:
		/*
		 * Op is not a constant or string, append each argument to the Op
		 */
		while (GET_CURRENT_ARG_TYPE(walk_state->arg_types) &&
		       !walk_state->arg_count) {
			walk_state->aml = walk_state->parser_state.aml;

			switch (op->common.aml_opcode) {
			case AML_METHOD_OP:
			case AML_BUFFER_OP:
			case AML_PACKAGE_OP:
			case AML_VARIABLE_PACKAGE_OP:
			case AML_WHILE_OP:

				break;

			default:

				ASL_CV_CAPTURE_COMMENTS(walk_state);
				break;
			}

			status =
			    acpi_ps_get_next_arg(walk_state,
						 &(walk_state->parser_state),
						 GET_CURRENT_ARG_TYPE
						 (walk_state->arg_types), &arg);
			if (ACPI_FAILURE(status)) {
				return_ACPI_STATUS(status);
			}

			if (arg) {
				acpi_ps_append_arg(op, arg);
			}

			INCREMENT_ARG_LIST(walk_state->arg_types);
		}

		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "Final argument count: %8.8X pass %u\n",
				  walk_state->arg_count,
				  walk_state->pass_number));

		/* Special processing for certain opcodes */

		switch (op->common.aml_opcode) {
		case AML_METHOD_OP:
			/*
			 * Skip parsing of control method because we don't have enough
			 * info in the first pass to parse it correctly.
			 *
			 * Save the length and address of the body
			 */
			op->named.data = walk_state->parser_state.aml;
			op->named.length = (u32)
			    (walk_state->parser_state.pkg_end -
			     walk_state->parser_state.aml);

			/* Skip body of method */

			walk_state->parser_state.aml =
			    walk_state->parser_state.pkg_end;
			walk_state->arg_count = 0;
			break;

		case AML_BUFFER_OP:
		case AML_PACKAGE_OP:
		case AML_VARIABLE_PACKAGE_OP:

			if ((op->common.parent) &&
			    (op->common.parent->common.aml_opcode ==
			     AML_NAME_OP)
			    && (walk_state->pass_number <=
				ACPI_IMODE_LOAD_PASS2)) {
				ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
						  "Setup Package/Buffer: Pass %u, AML Ptr: %p\n",
						  walk_state->pass_number,
						  aml_op_start));

				/*
				 * Skip parsing of Buffers and Packages because we don't have
				 * enough info in the first pass to parse them correctly.
				 */
				op->named.data = aml_op_start;
				op->named.length = (u32)
				    (walk_state->parser_state.pkg_end -
				     aml_op_start);

				/* Skip body */

				walk_state->parser_state.aml =
				    walk_state->parser_state.pkg_end;
				walk_state->arg_count = 0;
			}
			break;

		case AML_WHILE_OP:

			if (walk_state->control_state) {
				walk_state->control_state->control.package_end =
				    walk_state->parser_state.pkg_end;
			}
			break;

		default:

			/* No action for all other opcodes */

			break;
		}

		break;
	}

	return_ACPI_STATUS(AE_OK);
}