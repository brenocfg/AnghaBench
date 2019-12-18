#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_4__ {int Length; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDmDisassemble (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiGbl_DmOpt_Listing ; 
 int /*<<< orphan*/  AcpiGbl_ParseOpRoot ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiUtDebugDumpBuffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdCreateTableHeader (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  DB_BYTE_DISPLAY ; 
 int /*<<< orphan*/  MpEmitMappingInfo () ; 

ACPI_STATUS
AdDisplayTables (
    char                    *Filename,
    ACPI_TABLE_HEADER       *Table)
{


    if (!AcpiGbl_ParseOpRoot)
    {
        return (AE_NOT_EXIST);
    }

    if (!AcpiGbl_DmOpt_Listing)
    {
        AdCreateTableHeader (Filename, Table);
    }

    AcpiDmDisassemble (NULL, AcpiGbl_ParseOpRoot, ACPI_UINT32_MAX);
    MpEmitMappingInfo ();

    if (AcpiGbl_DmOpt_Listing)
    {
        AcpiOsPrintf ("\n\nTable Header:\n");
        AcpiUtDebugDumpBuffer ((UINT8 *) Table, sizeof (ACPI_TABLE_HEADER),
            DB_BYTE_DISPLAY, ACPI_UINT32_MAX);

        AcpiOsPrintf ("Table Body (Length 0x%X)\n", Table->Length);
        AcpiUtDebugDumpBuffer (((UINT8 *) Table + sizeof (ACPI_TABLE_HEADER)),
            Table->Length, DB_BYTE_DISPLAY, ACPI_UINT32_MAX);
    }

    return (AE_OK);
}