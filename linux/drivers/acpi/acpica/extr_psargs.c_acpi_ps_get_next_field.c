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
struct TYPE_7__ {int integer; int /*<<< orphan*/  name; void* size; } ;
struct TYPE_8__ {TYPE_3__ value; int /*<<< orphan*/ * inline_comment; int /*<<< orphan*/ * name_comment; } ;
struct TYPE_5__ {int size; } ;
struct TYPE_6__ {int* data; TYPE_1__ value; } ;
union acpi_parse_object {TYPE_4__ common; TYPE_2__ named; } ;
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct acpi_parse_state {int* aml; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_GET16 (int*) ; 
 int ACPI_GET32 (int*) ; 
 int ACPI_GET8 (int*) ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (int*,int*) ; 
 int /*<<< orphan*/  ACPI_NAMESEG_SIZE ; 
 int AML_BUFFER_OP ; 
#define  AML_BYTE_OP 139 
#define  AML_DWORD_OP 138 
#define  AML_FIELD_ACCESS_OP 137 
#define  AML_FIELD_CONNECTION_OP 136 
#define  AML_FIELD_EXT_ACCESS_OP 135 
#define  AML_FIELD_OFFSET_OP 134 
#define  AML_INT_ACCESSFIELD_OP 133 
 int AML_INT_BYTELIST_OP ; 
#define  AML_INT_CONNECTION_OP 132 
#define  AML_INT_EXTACCESSFIELD_OP 131 
#define  AML_INT_NAMEDFIELD_OP 130 
 int AML_INT_NAMEPATH_OP ; 
#define  AML_INT_RESERVEDFIELD_OP 129 
#define  AML_WORD_OP 128 
 int /*<<< orphan*/  ASL_CV_CAPTURE_COMMENTS_ONLY (struct acpi_parse_state*) ; 
 int /*<<< orphan*/ * acpi_gbl_current_inline_comment ; 
 union acpi_parse_object* acpi_ps_alloc_op (int,int*) ; 
 int /*<<< orphan*/  acpi_ps_append_arg (union acpi_parse_object*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ps_free_op (union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ps_get_next_namestring (struct acpi_parse_state*) ; 
 void* acpi_ps_get_next_package_length (struct acpi_parse_state*) ; 
 int /*<<< orphan*/  acpi_ps_set_name (union acpi_parse_object*,int) ; 
 int /*<<< orphan*/  ps_get_next_field ; 
 int /*<<< orphan*/  return_PTR (union acpi_parse_object*) ; 

__attribute__((used)) static union acpi_parse_object *acpi_ps_get_next_field(struct acpi_parse_state
						       *parser_state)
{
	u8 *aml;
	union acpi_parse_object *field;
	union acpi_parse_object *arg = NULL;
	u16 opcode;
	u32 name;
	u8 access_type;
	u8 access_attribute;
	u8 access_length;
	u32 pkg_length;
	u8 *pkg_end;
	u32 buffer_length;

	ACPI_FUNCTION_TRACE(ps_get_next_field);

	ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
	aml = parser_state->aml;

	/* Determine field type */

	switch (ACPI_GET8(parser_state->aml)) {
	case AML_FIELD_OFFSET_OP:

		opcode = AML_INT_RESERVEDFIELD_OP;
		parser_state->aml++;
		break;

	case AML_FIELD_ACCESS_OP:

		opcode = AML_INT_ACCESSFIELD_OP;
		parser_state->aml++;
		break;

	case AML_FIELD_CONNECTION_OP:

		opcode = AML_INT_CONNECTION_OP;
		parser_state->aml++;
		break;

	case AML_FIELD_EXT_ACCESS_OP:

		opcode = AML_INT_EXTACCESSFIELD_OP;
		parser_state->aml++;
		break;

	default:

		opcode = AML_INT_NAMEDFIELD_OP;
		break;
	}

	/* Allocate a new field op */

	field = acpi_ps_alloc_op(opcode, aml);
	if (!field) {
		return_PTR(NULL);
	}

	/* Decode the field type */

	ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
	switch (opcode) {
	case AML_INT_NAMEDFIELD_OP:

		/* Get the 4-character name */

		ACPI_MOVE_32_TO_32(&name, parser_state->aml);
		acpi_ps_set_name(field, name);
		parser_state->aml += ACPI_NAMESEG_SIZE;

		ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);

#ifdef ACPI_ASL_COMPILER
		/*
		 * Because the package length isn't represented as a parse tree object,
		 * take comments surrounding this and add to the previously created
		 * parse node.
		 */
		if (field->common.inline_comment) {
			field->common.name_comment =
			    field->common.inline_comment;
		}
		field->common.inline_comment = acpi_gbl_current_inline_comment;
		acpi_gbl_current_inline_comment = NULL;
#endif

		/* Get the length which is encoded as a package length */

		field->common.value.size =
		    acpi_ps_get_next_package_length(parser_state);
		break;

	case AML_INT_RESERVEDFIELD_OP:

		/* Get the length which is encoded as a package length */

		field->common.value.size =
		    acpi_ps_get_next_package_length(parser_state);
		break;

	case AML_INT_ACCESSFIELD_OP:
	case AML_INT_EXTACCESSFIELD_OP:

		/*
		 * Get access_type and access_attrib and merge into the field Op
		 * access_type is first operand, access_attribute is second. stuff
		 * these bytes into the node integer value for convenience.
		 */

		/* Get the two bytes (Type/Attribute) */

		access_type = ACPI_GET8(parser_state->aml);
		parser_state->aml++;
		access_attribute = ACPI_GET8(parser_state->aml);
		parser_state->aml++;

		field->common.value.integer = (u8)access_type;
		field->common.value.integer |= (u16)(access_attribute << 8);

		/* This opcode has a third byte, access_length */

		if (opcode == AML_INT_EXTACCESSFIELD_OP) {
			access_length = ACPI_GET8(parser_state->aml);
			parser_state->aml++;

			field->common.value.integer |=
			    (u32)(access_length << 16);
		}
		break;

	case AML_INT_CONNECTION_OP:

		/*
		 * Argument for Connection operator can be either a Buffer
		 * (resource descriptor), or a name_string.
		 */
		aml = parser_state->aml;
		if (ACPI_GET8(parser_state->aml) == AML_BUFFER_OP) {
			parser_state->aml++;

			ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
			pkg_end = parser_state->aml;
			pkg_length =
			    acpi_ps_get_next_package_length(parser_state);
			pkg_end += pkg_length;

			ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
			if (parser_state->aml < pkg_end) {

				/* Non-empty list */

				arg =
				    acpi_ps_alloc_op(AML_INT_BYTELIST_OP, aml);
				if (!arg) {
					acpi_ps_free_op(field);
					return_PTR(NULL);
				}

				/* Get the actual buffer length argument */

				opcode = ACPI_GET8(parser_state->aml);
				parser_state->aml++;

				ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
				switch (opcode) {
				case AML_BYTE_OP:	/* AML_BYTEDATA_ARG */

					buffer_length =
					    ACPI_GET8(parser_state->aml);
					parser_state->aml += 1;
					break;

				case AML_WORD_OP:	/* AML_WORDDATA_ARG */

					buffer_length =
					    ACPI_GET16(parser_state->aml);
					parser_state->aml += 2;
					break;

				case AML_DWORD_OP:	/* AML_DWORDATA_ARG */

					buffer_length =
					    ACPI_GET32(parser_state->aml);
					parser_state->aml += 4;
					break;

				default:

					buffer_length = 0;
					break;
				}

				/* Fill in bytelist data */

				ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
				arg->named.value.size = buffer_length;
				arg->named.data = parser_state->aml;
			}

			/* Skip to End of byte data */

			parser_state->aml = pkg_end;
		} else {
			arg = acpi_ps_alloc_op(AML_INT_NAMEPATH_OP, aml);
			if (!arg) {
				acpi_ps_free_op(field);
				return_PTR(NULL);
			}

			/* Get the Namestring argument */

			arg->common.value.name =
			    acpi_ps_get_next_namestring(parser_state);
		}

		/* Link the buffer/namestring to parent (CONNECTION_OP) */

		acpi_ps_append_arg(field, arg);
		break;

	default:

		/* Opcode was set in previous switch */
		break;
	}

	return_PTR(field);
}