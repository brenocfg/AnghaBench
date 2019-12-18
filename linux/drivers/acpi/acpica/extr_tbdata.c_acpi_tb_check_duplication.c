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
typedef  size_t u32 ;
struct acpi_table_desc {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {size_t current_table_count; TYPE_1__* tables; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_TABLE_IS_LOADED ; 
 int ACPI_TABLE_IS_VERIFIED ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_2__ acpi_gbl_root_table_list ; 
 int /*<<< orphan*/  acpi_tb_compare_tables (struct acpi_table_desc*,size_t) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_check_duplication ; 

__attribute__((used)) static acpi_status
acpi_tb_check_duplication(struct acpi_table_desc *table_desc, u32 *table_index)
{
	u32 i;

	ACPI_FUNCTION_TRACE(tb_check_duplication);

	/* Check if table is already registered */

	for (i = 0; i < acpi_gbl_root_table_list.current_table_count; ++i) {

		/* Do not compare with unverified tables */

		if (!
		    (acpi_gbl_root_table_list.tables[i].
		     flags & ACPI_TABLE_IS_VERIFIED)) {
			continue;
		}

		/*
		 * Check for a table match on the entire table length,
		 * not just the header.
		 */
		if (!acpi_tb_compare_tables(table_desc, i)) {
			continue;
		}

		/*
		 * Note: the current mechanism does not unregister a table if it is
		 * dynamically unloaded. The related namespace entries are deleted,
		 * but the table remains in the root table list.
		 *
		 * The assumption here is that the number of different tables that
		 * will be loaded is actually small, and there is minimal overhead
		 * in just keeping the table in case it is needed again.
		 *
		 * If this assumption changes in the future (perhaps on large
		 * machines with many table load/unload operations), tables will
		 * need to be unregistered when they are unloaded, and slots in the
		 * root table list should be reused when empty.
		 */
		if (acpi_gbl_root_table_list.tables[i].flags &
		    ACPI_TABLE_IS_LOADED) {

			/* Table is still loaded, this is an error */

			return_ACPI_STATUS(AE_ALREADY_EXISTS);
		} else {
			*table_index = i;
			return_ACPI_STATUS(AE_CTRL_TERMINATE);
		}
	}

	/* Indicate no duplication to the caller */

	return_ACPI_STATUS(AE_OK);
}