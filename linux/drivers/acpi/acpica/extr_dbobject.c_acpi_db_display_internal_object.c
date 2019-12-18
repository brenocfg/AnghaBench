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
struct TYPE_8__ {size_t value; int /*<<< orphan*/  class; union acpi_operand_object* node; union acpi_operand_object* object; union acpi_operand_object** where; int /*<<< orphan*/  target_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
union acpi_operand_object {TYPE_4__ reference; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {TYPE_3__* arguments; TYPE_2__* local_variables; } ;
struct acpi_namespace_node {TYPE_4__ reference; TYPE_1__ common; } ;
struct TYPE_7__ {union acpi_operand_object* object; } ;
struct TYPE_6__ {union acpi_operand_object* object; } ;

/* Variables and functions */
#define  ACPI_DESC_TYPE_NAMED 140 
#define  ACPI_DESC_TYPE_OPERAND 139 
#define  ACPI_DESC_TYPE_PARSER 138 
 int ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
#define  ACPI_REFCLASS_ARG 137 
#define  ACPI_REFCLASS_DEBUG 136 
#define  ACPI_REFCLASS_INDEX 135 
#define  ACPI_REFCLASS_LOCAL 134 
#define  ACPI_REFCLASS_NAME 133 
#define  ACPI_REFCLASS_REFOF 132 
#define  ACPI_REFCLASS_TABLE 131 
#define  ACPI_TYPE_BUFFER_FIELD 130 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_MAX ; 
#define  ACPI_TYPE_LOCAL_REFERENCE 129 
#define  ACPI_TYPE_PACKAGE 128 
 int /*<<< orphan*/  acpi_db_decode_internal_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_db_decode_node (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 int /*<<< orphan*/  acpi_ut_get_descriptor_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_reference_name (union acpi_operand_object*) ; 

void
acpi_db_display_internal_object(union acpi_operand_object *obj_desc,
				struct acpi_walk_state *walk_state)
{
	u8 type;

	acpi_os_printf("%p ", obj_desc);

	if (!obj_desc) {
		acpi_os_printf("<Null Object>\n");
		return;
	}

	/* Decode the object type */

	switch (ACPI_GET_DESCRIPTOR_TYPE(obj_desc)) {
	case ACPI_DESC_TYPE_PARSER:

		acpi_os_printf("<Parser> ");
		break;

	case ACPI_DESC_TYPE_NAMED:

		acpi_db_decode_node((struct acpi_namespace_node *)obj_desc);
		break;

	case ACPI_DESC_TYPE_OPERAND:

		type = obj_desc->common.type;
		if (type > ACPI_TYPE_LOCAL_MAX) {
			acpi_os_printf(" Type %X [Invalid Type]", (u32)type);
			return;
		}

		/* Decode the ACPI object type */

		switch (obj_desc->common.type) {
		case ACPI_TYPE_LOCAL_REFERENCE:

			acpi_os_printf("[%s] ",
				       acpi_ut_get_reference_name(obj_desc));

			/* Decode the reference */

			switch (obj_desc->reference.class) {
			case ACPI_REFCLASS_LOCAL:

				acpi_os_printf("%X ",
					       obj_desc->reference.value);
				if (walk_state) {
					obj_desc = walk_state->local_variables
					    [obj_desc->reference.value].object;
					acpi_os_printf("%p", obj_desc);
					acpi_db_decode_internal_object
					    (obj_desc);
				}
				break;

			case ACPI_REFCLASS_ARG:

				acpi_os_printf("%X ",
					       obj_desc->reference.value);
				if (walk_state) {
					obj_desc = walk_state->arguments
					    [obj_desc->reference.value].object;
					acpi_os_printf("%p", obj_desc);
					acpi_db_decode_internal_object
					    (obj_desc);
				}
				break;

			case ACPI_REFCLASS_INDEX:

				switch (obj_desc->reference.target_type) {
				case ACPI_TYPE_BUFFER_FIELD:

					acpi_os_printf("%p",
						       obj_desc->reference.
						       object);
					acpi_db_decode_internal_object
					    (obj_desc->reference.object);
					break;

				case ACPI_TYPE_PACKAGE:

					acpi_os_printf("%p",
						       obj_desc->reference.
						       where);
					if (!obj_desc->reference.where) {
						acpi_os_printf
						    (" Uninitialized WHERE pointer");
					} else {
						acpi_db_decode_internal_object(*
									       (obj_desc->
										reference.
										where));
					}
					break;

				default:

					acpi_os_printf
					    ("Unknown index target type");
					break;
				}
				break;

			case ACPI_REFCLASS_REFOF:

				if (!obj_desc->reference.object) {
					acpi_os_printf
					    ("Uninitialized reference subobject pointer");
					break;
				}

				/* Reference can be to a Node or an Operand object */

				switch (ACPI_GET_DESCRIPTOR_TYPE
					(obj_desc->reference.object)) {
				case ACPI_DESC_TYPE_NAMED:

					acpi_db_decode_node(obj_desc->reference.
							    object);
					break;

				case ACPI_DESC_TYPE_OPERAND:

					acpi_db_decode_internal_object
					    (obj_desc->reference.object);
					break;

				default:
					break;
				}
				break;

			case ACPI_REFCLASS_NAME:

				acpi_db_decode_node(obj_desc->reference.node);
				break;

			case ACPI_REFCLASS_DEBUG:
			case ACPI_REFCLASS_TABLE:

				acpi_os_printf("\n");
				break;

			default:	/* Unknown reference class */

				acpi_os_printf("%2.2X\n",
					       obj_desc->reference.class);
				break;
			}
			break;

		default:

			acpi_os_printf("<Obj>          ");
			acpi_db_decode_internal_object(obj_desc);
			break;
		}
		break;

	default:

		acpi_os_printf("<Not a valid ACPI Object Descriptor> [%s]",
			       acpi_ut_get_descriptor_name(obj_desc));
		break;
	}

	acpi_os_printf("\n");
}