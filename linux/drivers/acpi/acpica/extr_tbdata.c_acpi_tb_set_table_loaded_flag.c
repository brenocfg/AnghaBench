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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct TYPE_4__ {size_t current_table_count; TYPE_1__* tables; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_MTX_TABLES ; 
 int /*<<< orphan*/  ACPI_TABLE_IS_LOADED ; 
 TYPE_2__ acpi_gbl_root_table_list ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 

void acpi_tb_set_table_loaded_flag(u32 table_index, u8 is_loaded)
{

	(void)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	if (table_index < acpi_gbl_root_table_list.current_table_count) {
		if (is_loaded) {
			acpi_gbl_root_table_list.tables[table_index].flags |=
			    ACPI_TABLE_IS_LOADED;
		} else {
			acpi_gbl_root_table_list.tables[table_index].flags &=
			    ~ACPI_TABLE_IS_LOADED;
		}
	}

	(void)acpi_ut_release_mutex(ACPI_MTX_TABLES);
}