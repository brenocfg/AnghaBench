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
typedef  size_t UINT32 ;
struct TYPE_4__ {size_t CurrentTableCount; TYPE_1__* Tables; } ;
struct TYPE_3__ {int Flags; } ;
typedef  int /*<<< orphan*/  ACPI_TABLE_DESC ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_TABLE_IS_LOADED ; 
 int ACPI_TABLE_IS_VERIFIED ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_2__ AcpiGbl_RootTableList ; 
 int /*<<< orphan*/  AcpiTbCompareTables (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  TbCheckDuplication ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiTbCheckDuplication (
    ACPI_TABLE_DESC         *TableDesc,
    UINT32                  *TableIndex)
{
    UINT32                  i;


    ACPI_FUNCTION_TRACE (TbCheckDuplication);


    /* Check if table is already registered */

    for (i = 0; i < AcpiGbl_RootTableList.CurrentTableCount; ++i)
    {
        /* Do not compare with unverified tables */

        if (!(AcpiGbl_RootTableList.Tables[i].Flags & ACPI_TABLE_IS_VERIFIED))
        {
            continue;
        }

        /*
         * Check for a table match on the entire table length,
         * not just the header.
         */
        if (!AcpiTbCompareTables (TableDesc, i))
        {
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
        if (AcpiGbl_RootTableList.Tables[i].Flags &
            ACPI_TABLE_IS_LOADED)
        {
            /* Table is still loaded, this is an error */

            return_ACPI_STATUS (AE_ALREADY_EXISTS);
        }
        else
        {
            *TableIndex = i;
            return_ACPI_STATUS (AE_CTRL_TERMINATE);
        }
    }

    /* Indicate no duplication to the caller */

    return_ACPI_STATUS (AE_OK);
}