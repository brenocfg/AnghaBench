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
struct acpi_init_walk_info {int /*<<< orphan*/  op_region_count; int /*<<< orphan*/  method_count; int /*<<< orphan*/  object_count; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_init_one_object ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_init_walk_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct acpi_init_walk_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_initialize_objects ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ns_initialize_objects(void)
{
	acpi_status status;
	struct acpi_init_walk_info info;

	ACPI_FUNCTION_TRACE(ns_initialize_objects);

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "[Init] Completing Initialization of ACPI Objects\n"));
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "**** Starting initialization of namespace objects ****\n"));
	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
			      "Final data object initialization: "));

	/* Clear the info block */

	memset(&info, 0, sizeof(struct acpi_init_walk_info));

	/* Walk entire namespace from the supplied root */

	/*
	 * TBD: will become ACPI_TYPE_PACKAGE as this type object
	 * is now the only one that supports deferred initialization
	 * (forward references).
	 */
	status = acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				     ACPI_UINT32_MAX, acpi_ns_init_one_object,
				     NULL, &info, NULL);
	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "During WalkNamespace"));
	}

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
			      "Namespace contains %u (0x%X) objects\n",
			      info.object_count, info.object_count));

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "%u Control Methods found\n%u Op Regions found\n",
			  info.method_count, info.op_region_count));

	return_ACPI_STATUS(AE_OK);
}