#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ integer; int /*<<< orphan*/  name; union acpi_parse_object* arg; } ;
struct TYPE_7__ {union acpi_parse_object* next; TYPE_1__ value; } ;
union acpi_parse_object {TYPE_2__ common; } ;
typedef  scalar_t__ u8 ;
struct acpi_walk_state {int /*<<< orphan*/  scope_info; } ;
struct acpi_namespace_node {TYPE_5__* object; } ;
struct acpi_create_field_info {struct acpi_namespace_node* region_node; int /*<<< orphan*/  field_type; scalar_t__ attribute; scalar_t__ field_flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_9__ {scalar_t__ space_id; int /*<<< orphan*/  length; } ;
struct TYPE_8__ {int /*<<< orphan*/  internal_pcc_buffer; } ;
struct TYPE_10__ {TYPE_4__ region; TYPE_3__ field; } ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_PLATFORM_COMM ; 
 int /*<<< orphan*/  ACPI_ALLOCATE_ZEROED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int /*<<< orphan*/  ACPI_NS_SEARCH_PARENT ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REGION_FIELD ; 
 int /*<<< orphan*/  ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  acpi_ds_create_external_region (int /*<<< orphan*/ ,union acpi_parse_object*,int /*<<< orphan*/ ,struct acpi_walk_state*,struct acpi_namespace_node**) ; 
 int /*<<< orphan*/  acpi_ds_get_field_names (struct acpi_create_field_info*,struct acpi_walk_state*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ns_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_walk_state*,struct acpi_namespace_node**) ; 
 int /*<<< orphan*/  ds_create_field ; 
 int /*<<< orphan*/  memset (struct acpi_create_field_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_create_field(union acpi_parse_object *op,
		     struct acpi_namespace_node *region_node,
		     struct acpi_walk_state *walk_state)
{
	acpi_status status;
	union acpi_parse_object *arg;
	struct acpi_create_field_info info;

	ACPI_FUNCTION_TRACE_PTR(ds_create_field, op);

	/* First arg is the name of the parent op_region (must already exist) */

	arg = op->common.value.arg;

	if (!region_node) {
		status =
		    acpi_ns_lookup(walk_state->scope_info,
				   arg->common.value.name, ACPI_TYPE_REGION,
				   ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT,
				   walk_state, &region_node);
#ifdef ACPI_ASL_COMPILER
		status = acpi_ds_create_external_region(status, arg,
							arg->common.value.name,
							walk_state,
							&region_node);
#endif
		if (ACPI_FAILURE(status)) {
			ACPI_ERROR_NAMESPACE(walk_state->scope_info,
					     arg->common.value.name, status);
			return_ACPI_STATUS(status);
		}
	}

	memset(&info, 0, sizeof(struct acpi_create_field_info));

	/* Second arg is the field flags */

	arg = arg->common.next;
	info.field_flags = (u8) arg->common.value.integer;
	info.attribute = 0;

	/* Each remaining arg is a Named Field */

	info.field_type = ACPI_TYPE_LOCAL_REGION_FIELD;
	info.region_node = region_node;

	status = acpi_ds_get_field_names(&info, walk_state, arg->common.next);
	if (info.region_node->object->region.space_id ==
	    ACPI_ADR_SPACE_PLATFORM_COMM
	    && !(region_node->object->field.internal_pcc_buffer =
		 ACPI_ALLOCATE_ZEROED(info.region_node->object->region.
				      length))) {
		return_ACPI_STATUS(AE_NO_MEMORY);
	}
	return_ACPI_STATUS(status);
}