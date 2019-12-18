#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * aml_start; } ;
union acpi_operand_object {TYPE_1__ method; } ;
typedef  scalar_t__ u8 ;
struct acpi_walk_state {int dummy; } ;
struct acpi_namespace_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TRACE_AML_METHOD ; 
 scalar_t__ ACPI_TRACE_LAYER_ALL ; 
 scalar_t__ ACPI_TRACE_LEVEL_ALL ; 
 int /*<<< orphan*/  ACPI_TRACE_POINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ acpi_dbg_layer ; 
 scalar_t__ acpi_dbg_level ; 
 scalar_t__ acpi_ex_interpreter_trace_enabled (char*) ; 
 scalar_t__ acpi_gbl_original_dbg_layer ; 
 scalar_t__ acpi_gbl_original_dbg_level ; 
 scalar_t__ acpi_gbl_trace_dbg_layer ; 
 scalar_t__ acpi_gbl_trace_dbg_level ; 
 union acpi_operand_object* acpi_gbl_trace_method_object ; 
 char* acpi_ns_get_normalized_pathname (struct acpi_namespace_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_start_trace_method ; 

void
acpi_ex_start_trace_method(struct acpi_namespace_node *method_node,
			   union acpi_operand_object *obj_desc,
			   struct acpi_walk_state *walk_state)
{
	char *pathname = NULL;
	u8 enabled = FALSE;

	ACPI_FUNCTION_NAME(ex_start_trace_method);

	if (method_node) {
		pathname = acpi_ns_get_normalized_pathname(method_node, TRUE);
	}

	enabled = acpi_ex_interpreter_trace_enabled(pathname);
	if (enabled && !acpi_gbl_trace_method_object) {
		acpi_gbl_trace_method_object = obj_desc;
		acpi_gbl_original_dbg_level = acpi_dbg_level;
		acpi_gbl_original_dbg_layer = acpi_dbg_layer;
		acpi_dbg_level = ACPI_TRACE_LEVEL_ALL;
		acpi_dbg_layer = ACPI_TRACE_LAYER_ALL;

		if (acpi_gbl_trace_dbg_level) {
			acpi_dbg_level = acpi_gbl_trace_dbg_level;
		}

		if (acpi_gbl_trace_dbg_layer) {
			acpi_dbg_layer = acpi_gbl_trace_dbg_layer;
		}
	}

	if (enabled) {
		ACPI_TRACE_POINT(ACPI_TRACE_AML_METHOD, TRUE,
				 obj_desc ? obj_desc->method.aml_start : NULL,
				 pathname);
	}

	if (pathname) {
		ACPI_FREE(pathname);
	}
}