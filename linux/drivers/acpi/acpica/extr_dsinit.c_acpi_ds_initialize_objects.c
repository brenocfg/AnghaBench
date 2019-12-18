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
struct acpi_table_header {int /*<<< orphan*/  oem_table_id; int /*<<< orphan*/  signature; } ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_init_walk_info {int /*<<< orphan*/  op_region_count; int /*<<< orphan*/  method_count; int /*<<< orphan*/  serialized_method_count; int /*<<< orphan*/  non_serial_method_count; int /*<<< orphan*/  serial_method_count; int /*<<< orphan*/  device_count; int /*<<< orphan*/  object_count; int /*<<< orphan*/  table_index; int /*<<< orphan*/  owner_id; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_owner_id ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NS_WALK_NO_UNLOCK ; 
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ds_init_one_object ; 
 int /*<<< orphan*/  acpi_get_table_by_index (int /*<<< orphan*/ ,struct acpi_table_header**) ; 
 int /*<<< orphan*/  acpi_ns_walk_namespace (int /*<<< orphan*/ ,struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_init_walk_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_tb_get_owner_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds_initialize_objects ; 
 int /*<<< orphan*/  memset (struct acpi_init_walk_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ds_initialize_objects(u32 table_index,
			   struct acpi_namespace_node *start_node)
{
	acpi_status status;
	struct acpi_init_walk_info info;
	struct acpi_table_header *table;
	acpi_owner_id owner_id;

	ACPI_FUNCTION_TRACE(ds_initialize_objects);

	status = acpi_tb_get_owner_id(table_index, &owner_id);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "**** Starting initialization of namespace objects ****\n"));

	/* Set all init info to zero */

	memset(&info, 0, sizeof(struct acpi_init_walk_info));

	info.owner_id = owner_id;
	info.table_index = table_index;

	/* Walk entire namespace from the supplied root */

	/*
	 * We don't use acpi_walk_namespace since we do not want to acquire
	 * the namespace reader lock.
	 */
	status =
	    acpi_ns_walk_namespace(ACPI_TYPE_ANY, start_node, ACPI_UINT32_MAX,
				   ACPI_NS_WALK_NO_UNLOCK,
				   acpi_ds_init_one_object, NULL, &info, NULL);
	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "During WalkNamespace"));
	}

	status = acpi_get_table_by_index(table_index, &table);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* DSDT is always the first AML table */

	if (ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_DSDT)) {
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
				      "\nACPI table initialization:\n"));
	}

	/* Summary of objects initialized */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
			      "Table [%4.4s: %-8.8s] (id %.2X) - %4u Objects with %3u Devices, "
			      "%3u Regions, %4u Methods (%u/%u/%u Serial/Non/Cvt)\n",
			      table->signature, table->oem_table_id, owner_id,
			      info.object_count, info.device_count,
			      info.op_region_count, info.method_count,
			      info.serial_method_count,
			      info.non_serial_method_count,
			      info.serialized_method_count));

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "%u Methods, %u Regions\n",
			  info.method_count, info.op_region_count));

	return_ACPI_STATUS(AE_OK);
}