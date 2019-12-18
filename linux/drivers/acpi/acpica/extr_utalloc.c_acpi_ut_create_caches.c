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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
typedef  union acpi_generic_state {int dummy; } acpi_generic_state ;
struct acpi_parse_obj_named {int dummy; } ;
struct acpi_parse_obj_common {int dummy; } ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_file_node {int dummy; } ;
struct acpi_comment_node {int dummy; } ;
struct acpi_comment_addr_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MAX_COMMENT_CACHE_DEPTH ; 
 int /*<<< orphan*/  ACPI_MAX_EXTPARSE_CACHE_DEPTH ; 
 int /*<<< orphan*/  ACPI_MAX_NAMESPACE_CACHE_DEPTH ; 
 int /*<<< orphan*/  ACPI_MAX_OBJECT_CACHE_DEPTH ; 
 int /*<<< orphan*/  ACPI_MAX_PARSE_CACHE_DEPTH ; 
 int /*<<< orphan*/  ACPI_MAX_STATE_CACHE_DEPTH ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_gbl_comment_addr_cache ; 
 int /*<<< orphan*/  acpi_gbl_file_cache ; 
 int /*<<< orphan*/  acpi_gbl_global_list ; 
 int /*<<< orphan*/  acpi_gbl_namespace_cache ; 
 int /*<<< orphan*/  acpi_gbl_ns_node_list ; 
 int /*<<< orphan*/  acpi_gbl_operand_cache ; 
 int /*<<< orphan*/  acpi_gbl_ps_node_cache ; 
 int /*<<< orphan*/  acpi_gbl_ps_node_ext_cache ; 
 int /*<<< orphan*/  acpi_gbl_reg_comment_cache ; 
 int /*<<< orphan*/  acpi_gbl_state_cache ; 
 int /*<<< orphan*/  acpi_os_create_cache (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_create_list (char*,int,int /*<<< orphan*/ *) ; 

acpi_status acpi_ut_create_caches(void)
{
	acpi_status status;

	/* Object Caches, for frequently used objects */

	status =
	    acpi_os_create_cache("Acpi-Namespace",
				 sizeof(struct acpi_namespace_node),
				 ACPI_MAX_NAMESPACE_CACHE_DEPTH,
				 &acpi_gbl_namespace_cache);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	status =
	    acpi_os_create_cache("Acpi-State", sizeof(union acpi_generic_state),
				 ACPI_MAX_STATE_CACHE_DEPTH,
				 &acpi_gbl_state_cache);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	status =
	    acpi_os_create_cache("Acpi-Parse",
				 sizeof(struct acpi_parse_obj_common),
				 ACPI_MAX_PARSE_CACHE_DEPTH,
				 &acpi_gbl_ps_node_cache);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	status =
	    acpi_os_create_cache("Acpi-ParseExt",
				 sizeof(struct acpi_parse_obj_named),
				 ACPI_MAX_EXTPARSE_CACHE_DEPTH,
				 &acpi_gbl_ps_node_ext_cache);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	status =
	    acpi_os_create_cache("Acpi-Operand",
				 sizeof(union acpi_operand_object),
				 ACPI_MAX_OBJECT_CACHE_DEPTH,
				 &acpi_gbl_operand_cache);
	if (ACPI_FAILURE(status)) {
		return (status);
	}
#ifdef ACPI_ASL_COMPILER
	/*
	 * For use with the ASL-/ASL+ option. This cache keeps track of regular
	 * 0xA9 0x01 comments.
	 */
	status =
	    acpi_os_create_cache("Acpi-Comment",
				 sizeof(struct acpi_comment_node),
				 ACPI_MAX_COMMENT_CACHE_DEPTH,
				 &acpi_gbl_reg_comment_cache);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/*
	 * This cache keeps track of the starting addresses of where the comments
	 * lie. This helps prevent duplication of comments.
	 */
	status =
	    acpi_os_create_cache("Acpi-Comment-Addr",
				 sizeof(struct acpi_comment_addr_node),
				 ACPI_MAX_COMMENT_CACHE_DEPTH,
				 &acpi_gbl_comment_addr_cache);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/*
	 * This cache will be used for nodes that represent files.
	 */
	status =
	    acpi_os_create_cache("Acpi-File", sizeof(struct acpi_file_node),
				 ACPI_MAX_COMMENT_CACHE_DEPTH,
				 &acpi_gbl_file_cache);
	if (ACPI_FAILURE(status)) {
		return (status);
	}
#endif

#ifdef ACPI_DBG_TRACK_ALLOCATIONS

	/* Memory allocation lists */

	status = acpi_ut_create_list("Acpi-Global", 0, &acpi_gbl_global_list);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	status =
	    acpi_ut_create_list("Acpi-Namespace",
				sizeof(struct acpi_namespace_node),
				&acpi_gbl_ns_node_list);
	if (ACPI_FAILURE(status)) {
		return (status);
	}
#endif

	return (AE_OK);
}