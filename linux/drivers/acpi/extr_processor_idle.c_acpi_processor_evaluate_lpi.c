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
struct TYPE_8__ {int /*<<< orphan*/  pointer; } ;
struct TYPE_7__ {int value; } ;
struct TYPE_6__ {scalar_t__ pointer; } ;
struct TYPE_5__ {int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_4__ string; TYPE_3__ integer; TYPE_2__ buffer; TYPE_1__ package; } ;
struct acpi_power_register {scalar_t__ space_id; int address; } ;
struct acpi_lpi_states_array {int size; struct acpi_lpi_state* entries; } ;
struct acpi_lpi_state {int address; int index; int min_residency; int wake_latency; int flags; int arch_flags; int res_cnt_freq; int enable_parent_state; int /*<<< orphan*/  desc; int /*<<< orphan*/  entry_method; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_FIXED_HARDWARE ; 
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_IO ; 
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_CSTATE_FFH ; 
 int /*<<< orphan*/  ACPI_CSTATE_INTEGER ; 
 int /*<<< orphan*/  ACPI_CSTATE_SYSTEMIO ; 
 int /*<<< orphan*/  ACPI_CX_DESC_LEN ; 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int ENODATA ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,int) ; 
 struct acpi_lpi_state* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 scalar_t__ obj_get_integer (union acpi_object*,int*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_processor_evaluate_lpi(acpi_handle handle,
				       struct acpi_lpi_states_array *info)
{
	acpi_status status;
	int ret = 0;
	int pkg_count, state_idx = 1, loop;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *lpi_data;
	struct acpi_lpi_state *lpi_state;

	status = acpi_evaluate_object(handle, "_LPI", NULL, &buffer);
	if (ACPI_FAILURE(status)) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO, "No _LPI, giving up\n"));
		return -ENODEV;
	}

	lpi_data = buffer.pointer;

	/* There must be at least 4 elements = 3 elements + 1 package */
	if (!lpi_data || lpi_data->type != ACPI_TYPE_PACKAGE ||
	    lpi_data->package.count < 4) {
		pr_debug("not enough elements in _LPI\n");
		ret = -ENODATA;
		goto end;
	}

	pkg_count = lpi_data->package.elements[2].integer.value;

	/* Validate number of power states. */
	if (pkg_count < 1 || pkg_count != lpi_data->package.count - 3) {
		pr_debug("count given by _LPI is not valid\n");
		ret = -ENODATA;
		goto end;
	}

	lpi_state = kcalloc(pkg_count, sizeof(*lpi_state), GFP_KERNEL);
	if (!lpi_state) {
		ret = -ENOMEM;
		goto end;
	}

	info->size = pkg_count;
	info->entries = lpi_state;

	/* LPI States start at index 3 */
	for (loop = 3; state_idx <= pkg_count; loop++, state_idx++, lpi_state++) {
		union acpi_object *element, *pkg_elem, *obj;

		element = &lpi_data->package.elements[loop];
		if (element->type != ACPI_TYPE_PACKAGE || element->package.count < 7)
			continue;

		pkg_elem = element->package.elements;

		obj = pkg_elem + 6;
		if (obj->type == ACPI_TYPE_BUFFER) {
			struct acpi_power_register *reg;

			reg = (struct acpi_power_register *)obj->buffer.pointer;
			if (reg->space_id != ACPI_ADR_SPACE_SYSTEM_IO &&
			    reg->space_id != ACPI_ADR_SPACE_FIXED_HARDWARE)
				continue;

			lpi_state->address = reg->address;
			lpi_state->entry_method =
				reg->space_id == ACPI_ADR_SPACE_FIXED_HARDWARE ?
				ACPI_CSTATE_FFH : ACPI_CSTATE_SYSTEMIO;
		} else if (obj->type == ACPI_TYPE_INTEGER) {
			lpi_state->entry_method = ACPI_CSTATE_INTEGER;
			lpi_state->address = obj->integer.value;
		} else {
			continue;
		}

		/* elements[7,8] skipped for now i.e. Residency/Usage counter*/

		obj = pkg_elem + 9;
		if (obj->type == ACPI_TYPE_STRING)
			strlcpy(lpi_state->desc, obj->string.pointer,
				ACPI_CX_DESC_LEN);

		lpi_state->index = state_idx;
		if (obj_get_integer(pkg_elem + 0, &lpi_state->min_residency)) {
			pr_debug("No min. residency found, assuming 10 us\n");
			lpi_state->min_residency = 10;
		}

		if (obj_get_integer(pkg_elem + 1, &lpi_state->wake_latency)) {
			pr_debug("No wakeup residency found, assuming 10 us\n");
			lpi_state->wake_latency = 10;
		}

		if (obj_get_integer(pkg_elem + 2, &lpi_state->flags))
			lpi_state->flags = 0;

		if (obj_get_integer(pkg_elem + 3, &lpi_state->arch_flags))
			lpi_state->arch_flags = 0;

		if (obj_get_integer(pkg_elem + 4, &lpi_state->res_cnt_freq))
			lpi_state->res_cnt_freq = 1;

		if (obj_get_integer(pkg_elem + 5, &lpi_state->enable_parent_state))
			lpi_state->enable_parent_state = 0;
	}

	acpi_handle_debug(handle, "Found %d power states\n", state_idx);
end:
	kfree(buffer.pointer);
	return ret;
}