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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_db_display_statistics (char*) ; 
 int /*<<< orphan*/ * acpi_gbl_comment_addr_cache ; 
 scalar_t__ acpi_gbl_display_final_mem_stats ; 
 int /*<<< orphan*/ * acpi_gbl_file_cache ; 
 int /*<<< orphan*/ * acpi_gbl_global_list ; 
 int /*<<< orphan*/ * acpi_gbl_namespace_cache ; 
 int /*<<< orphan*/ * acpi_gbl_ns_node_list ; 
 int /*<<< orphan*/ * acpi_gbl_operand_cache ; 
 int /*<<< orphan*/ * acpi_gbl_ps_node_cache ; 
 int /*<<< orphan*/ * acpi_gbl_ps_node_ext_cache ; 
 int /*<<< orphan*/ * acpi_gbl_reg_comment_cache ; 
 int /*<<< orphan*/ * acpi_gbl_state_cache ; 
 int /*<<< orphan*/  acpi_os_delete_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_dump_allocations (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

acpi_status acpi_ut_delete_caches(void)
{
#ifdef ACPI_DBG_TRACK_ALLOCATIONS
	char buffer[7];

	if (acpi_gbl_display_final_mem_stats) {
		strcpy(buffer, "MEMORY");
		(void)acpi_db_display_statistics(buffer);
	}
#endif

	(void)acpi_os_delete_cache(acpi_gbl_namespace_cache);
	acpi_gbl_namespace_cache = NULL;

	(void)acpi_os_delete_cache(acpi_gbl_state_cache);
	acpi_gbl_state_cache = NULL;

	(void)acpi_os_delete_cache(acpi_gbl_operand_cache);
	acpi_gbl_operand_cache = NULL;

	(void)acpi_os_delete_cache(acpi_gbl_ps_node_cache);
	acpi_gbl_ps_node_cache = NULL;

	(void)acpi_os_delete_cache(acpi_gbl_ps_node_ext_cache);
	acpi_gbl_ps_node_ext_cache = NULL;

#ifdef ACPI_ASL_COMPILER
	(void)acpi_os_delete_cache(acpi_gbl_reg_comment_cache);
	acpi_gbl_reg_comment_cache = NULL;

	(void)acpi_os_delete_cache(acpi_gbl_comment_addr_cache);
	acpi_gbl_comment_addr_cache = NULL;

	(void)acpi_os_delete_cache(acpi_gbl_file_cache);
	acpi_gbl_file_cache = NULL;
#endif

#ifdef ACPI_DBG_TRACK_ALLOCATIONS

	/* Debug only - display leftover memory allocation, if any */

	acpi_ut_dump_allocations(ACPI_UINT32_MAX, NULL);

	/* Free memory lists */

	acpi_os_free(acpi_gbl_global_list);
	acpi_gbl_global_list = NULL;

	acpi_os_free(acpi_gbl_ns_node_list);
	acpi_gbl_ns_node_list = NULL;
#endif

	return (AE_OK);
}