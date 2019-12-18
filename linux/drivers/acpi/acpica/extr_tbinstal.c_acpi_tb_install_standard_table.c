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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ascii; } ;
struct acpi_table_desc {int /*<<< orphan*/  pointer; TYPE_1__ signature; } ;
typedef  scalar_t__ acpi_status ;
typedef  int /*<<< orphan*/  acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INFO (char*) ; 
 int /*<<< orphan*/  ACPI_MTX_TABLES ; 
 int /*<<< orphan*/  ACPI_SIG_SSDT ; 
 int /*<<< orphan*/  ACPI_TABLE_EVENT_INSTALL ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_OK ; 
 scalar_t__ acpi_gbl_disable_ssdt_table_install ; 
 scalar_t__ acpi_tb_acquire_temp_table (struct acpi_table_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tb_install_table_with_override (struct acpi_table_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_tb_notify_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_tb_release_temp_table (struct acpi_table_desc*) ; 
 int /*<<< orphan*/  acpi_tb_uninstall_table (struct acpi_table_desc*) ; 
 scalar_t__ acpi_tb_verify_temp_table (struct acpi_table_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 int /*<<< orphan*/  tb_install_standard_table ; 

acpi_status
acpi_tb_install_standard_table(acpi_physical_address address,
			       u8 flags,
			       u8 reload, u8 override, u32 *table_index)
{
	u32 i;
	acpi_status status = AE_OK;
	struct acpi_table_desc new_table_desc;

	ACPI_FUNCTION_TRACE(tb_install_standard_table);

	/* Acquire a temporary table descriptor for validation */

	status = acpi_tb_acquire_temp_table(&new_table_desc, address, flags);
	if (ACPI_FAILURE(status)) {
		ACPI_ERROR((AE_INFO,
			    "Could not acquire table length at %8.8X%8.8X",
			    ACPI_FORMAT_UINT64(address)));
		return_ACPI_STATUS(status);
	}

	/*
	 * Optionally do not load any SSDTs from the RSDT/XSDT. This can
	 * be useful for debugging ACPI problems on some machines.
	 */
	if (!reload &&
	    acpi_gbl_disable_ssdt_table_install &&
	    ACPI_COMPARE_NAMESEG(&new_table_desc.signature, ACPI_SIG_SSDT)) {
		ACPI_INFO(("Ignoring installation of %4.4s at %8.8X%8.8X",
			   new_table_desc.signature.ascii,
			   ACPI_FORMAT_UINT64(address)));
		goto release_and_exit;
	}

	/* Acquire the table lock */

	(void)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);

	/* Validate and verify a table before installation */

	status = acpi_tb_verify_temp_table(&new_table_desc, NULL, &i);
	if (ACPI_FAILURE(status)) {
		if (status == AE_CTRL_TERMINATE) {
			/*
			 * Table was unloaded, allow it to be reloaded.
			 * As we are going to return AE_OK to the caller, we should
			 * take the responsibility of freeing the input descriptor.
			 * Refill the input descriptor to ensure
			 * acpi_tb_install_table_with_override() can be called again to
			 * indicate the re-installation.
			 */
			acpi_tb_uninstall_table(&new_table_desc);
			(void)acpi_ut_release_mutex(ACPI_MTX_TABLES);
			*table_index = i;
			return_ACPI_STATUS(AE_OK);
		}
		goto unlock_and_exit;
	}

	/* Add the table to the global root table list */

	acpi_tb_install_table_with_override(&new_table_desc, override,
					    table_index);

	/* Invoke table handler */

	(void)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	acpi_tb_notify_table(ACPI_TABLE_EVENT_INSTALL, new_table_desc.pointer);
	(void)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);

unlock_and_exit:

	/* Release the table lock */

	(void)acpi_ut_release_mutex(ACPI_MTX_TABLES);

release_and_exit:

	/* Release the temporary table descriptor */

	acpi_tb_release_temp_table(&new_table_desc);
	return_ACPI_STATUS(status);
}