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
struct TYPE_3__ {int /*<<< orphan*/  ascii; } ;
struct acpi_table_desc {int flags; TYPE_1__ signature; scalar_t__ pointer; int /*<<< orphan*/  address; int /*<<< orphan*/  owner_id; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {size_t current_table_count; struct acpi_table_desc* tables; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INFO (char*) ; 
 int ACPI_TABLE_IS_LOADED ; 
#define  ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL 130 
#define  ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL 129 
#define  ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL 128 
 int ACPI_TABLE_ORIGIN_MASK ; 
 TYPE_2__ acpi_gbl_root_table_list ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 int /*<<< orphan*/  acpi_tb_print_table_header (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  acpi_tb_validate_table (struct acpi_table_desc*) ; 

void acpi_db_display_table_info(char *table_arg)
{
	u32 i;
	struct acpi_table_desc *table_desc;
	acpi_status status;

	/* Header */

	acpi_os_printf("Idx ID  Status Type                    "
		       "TableHeader (Sig, Address, Length, Misc)\n");

	/* Walk the entire root table list */

	for (i = 0; i < acpi_gbl_root_table_list.current_table_count; i++) {
		table_desc = &acpi_gbl_root_table_list.tables[i];

		/* Index and Table ID */

		acpi_os_printf("%3u %.2u ", i, table_desc->owner_id);

		/* Decode the table flags */

		if (!(table_desc->flags & ACPI_TABLE_IS_LOADED)) {
			acpi_os_printf("NotLoaded ");
		} else {
			acpi_os_printf(" Loaded ");
		}

		switch (table_desc->flags & ACPI_TABLE_ORIGIN_MASK) {
		case ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL:

			acpi_os_printf("External/virtual ");
			break;

		case ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL:

			acpi_os_printf("Internal/physical ");
			break;

		case ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL:

			acpi_os_printf("Internal/virtual ");
			break;

		default:

			acpi_os_printf("INVALID TYPE    ");
			break;
		}

		/* Make sure that the table is mapped */

		status = acpi_tb_validate_table(table_desc);
		if (ACPI_FAILURE(status)) {
			return;
		}

		/* Dump the table header */

		if (table_desc->pointer) {
			acpi_tb_print_table_header(table_desc->address,
						   table_desc->pointer);
		} else {
			/* If the pointer is null, the table has been unloaded */

			ACPI_INFO(("%4.4s - Table has been unloaded",
				   table_desc->signature.ascii));
		}
	}
}