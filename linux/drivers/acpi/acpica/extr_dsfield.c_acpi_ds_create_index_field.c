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
struct TYPE_3__ {scalar_t__ integer; int /*<<< orphan*/  string; union acpi_parse_object* arg; } ;
struct TYPE_4__ {union acpi_parse_object* next; TYPE_1__ value; } ;
union acpi_parse_object {TYPE_2__ common; } ;
typedef  scalar_t__ u8 ;
struct acpi_walk_state {int /*<<< orphan*/  scope_info; } ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_create_field_info {struct acpi_namespace_node* region_node; int /*<<< orphan*/  field_type; scalar_t__ field_flags; int /*<<< orphan*/  data_register_node; int /*<<< orphan*/  register_node; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR_NAMESPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,union acpi_parse_object*) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int /*<<< orphan*/  ACPI_NS_SEARCH_PARENT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_INDEX_FIELD ; 
 int /*<<< orphan*/  acpi_ds_get_field_names (struct acpi_create_field_info*,struct acpi_walk_state*,union acpi_parse_object*) ; 
 int /*<<< orphan*/  acpi_ns_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_walk_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds_create_index_field ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_create_index_field(union acpi_parse_object *op,
			   struct acpi_namespace_node *region_node,
			   struct acpi_walk_state *walk_state)
{
	acpi_status status;
	union acpi_parse_object *arg;
	struct acpi_create_field_info info;

	ACPI_FUNCTION_TRACE_PTR(ds_create_index_field, op);

	/* First arg is the name of the Index register (must already exist) */

	arg = op->common.value.arg;
	status =
	    acpi_ns_lookup(walk_state->scope_info, arg->common.value.string,
			   ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEARCH_PARENT, walk_state,
			   &info.register_node);
	if (ACPI_FAILURE(status)) {
		ACPI_ERROR_NAMESPACE(walk_state->scope_info,
				     arg->common.value.string, status);
		return_ACPI_STATUS(status);
	}

	/* Second arg is the data register (must already exist) */

	arg = arg->common.next;
	status =
	    acpi_ns_lookup(walk_state->scope_info, arg->common.value.string,
			   ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEARCH_PARENT, walk_state,
			   &info.data_register_node);
	if (ACPI_FAILURE(status)) {
		ACPI_ERROR_NAMESPACE(walk_state->scope_info,
				     arg->common.value.string, status);
		return_ACPI_STATUS(status);
	}

	/* Next arg is the field flags */

	arg = arg->common.next;
	info.field_flags = (u8) arg->common.value.integer;

	/* Each remaining arg is a Named Field */

	info.field_type = ACPI_TYPE_LOCAL_INDEX_FIELD;
	info.region_node = region_node;

	status = acpi_ds_get_field_names(&info, walk_state, arg->common.next);
	return_ACPI_STATUS(status);
}