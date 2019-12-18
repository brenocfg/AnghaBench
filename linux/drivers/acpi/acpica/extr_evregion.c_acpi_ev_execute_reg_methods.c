#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct acpi_reg_walk_info {scalar_t__ space_id; scalar_t__ reg_run_count; int /*<<< orphan*/  function; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  scalar_t__ acpi_adr_space_type ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_DATA_TABLE ; 
 scalar_t__ ACPI_ADR_SPACE_EC ; 
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_IO ; 
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  ACPI_DB_NAMES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NS_WALK_UNLOCK ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  acpi_ev_orphan_ec_reg_method (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ev_reg_run ; 
 int /*<<< orphan*/  acpi_ns_walk_namespace (int /*<<< orphan*/ ,struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_reg_walk_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_get_region_name (scalar_t__) ; 
 int /*<<< orphan*/  ev_execute_reg_methods ; 
 int /*<<< orphan*/  return_VOID ; 

void
acpi_ev_execute_reg_methods(struct acpi_namespace_node *node,
			    acpi_adr_space_type space_id, u32 function)
{
	struct acpi_reg_walk_info info;

	ACPI_FUNCTION_TRACE(ev_execute_reg_methods);

	/*
	 * These address spaces do not need a call to _REG, since the ACPI
	 * specification defines them as: "must always be accessible". Since
	 * they never change state (never become unavailable), no need to ever
	 * call _REG on them. Also, a data_table is not a "real" address space,
	 * so do not call _REG. September 2018.
	 */
	if ((space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) ||
	    (space_id == ACPI_ADR_SPACE_SYSTEM_IO) ||
	    (space_id == ACPI_ADR_SPACE_DATA_TABLE)) {
		return_VOID;
	}

	info.space_id = space_id;
	info.function = function;
	info.reg_run_count = 0;

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_NAMES,
			      "    Running _REG methods for SpaceId %s\n",
			      acpi_ut_get_region_name(info.space_id)));

	/*
	 * Run all _REG methods for all Operation Regions for this space ID. This
	 * is a separate walk in order to handle any interdependencies between
	 * regions and _REG methods. (i.e. handlers must be installed for all
	 * regions of this Space ID before we can run any _REG methods)
	 */
	(void)acpi_ns_walk_namespace(ACPI_TYPE_ANY, node, ACPI_UINT32_MAX,
				     ACPI_NS_WALK_UNLOCK, acpi_ev_reg_run, NULL,
				     &info, NULL);

	/* Special case for EC: handle "orphan" _REG methods with no region */

	if (space_id == ACPI_ADR_SPACE_EC) {
		acpi_ev_orphan_ec_reg_method(node);
	}

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_NAMES,
			      "    Executed %u _REG methods for SpaceId %s\n",
			      info.reg_run_count,
			      acpi_ut_get_region_name(info.space_id)));

	return_VOID;
}