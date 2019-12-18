#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_7__ {size_t CurrentTableCount; TYPE_2__* Tables; } ;
struct TYPE_5__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_6__ {int Flags; TYPE_1__ Signature; scalar_t__ Pointer; int /*<<< orphan*/  Address; int /*<<< orphan*/  OwnerId; } ;
typedef  TYPE_2__ ACPI_TABLE_DESC ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INFO (char*) ; 
 int ACPI_TABLE_IS_LOADED ; 
#define  ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL 130 
#define  ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL 129 
#define  ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL 128 
 int ACPI_TABLE_ORIGIN_MASK ; 
 TYPE_4__ AcpiGbl_RootTableList ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiTbPrintTableHeader (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AcpiTbValidateTable (TYPE_2__*) ; 

void
AcpiDbDisplayTableInfo (
    char                    *TableArg)
{
    UINT32                  i;
    ACPI_TABLE_DESC         *TableDesc;
    ACPI_STATUS             Status;


    /* Header */

    AcpiOsPrintf ("Idx ID    Status Type                    "
        "TableHeader (Sig, Address, Length, Misc)\n");

    /* Walk the entire root table list */

    for (i = 0; i < AcpiGbl_RootTableList.CurrentTableCount; i++)
    {
        TableDesc = &AcpiGbl_RootTableList.Tables[i];

        /* Index and Table ID */

        AcpiOsPrintf ("%3u %.2u ", i, TableDesc->OwnerId);

        /* Decode the table flags */

        if (!(TableDesc->Flags & ACPI_TABLE_IS_LOADED))
        {
            AcpiOsPrintf ("NotLoaded ");
        }
        else
        {
            AcpiOsPrintf ("   Loaded ");
        }

        switch (TableDesc->Flags & ACPI_TABLE_ORIGIN_MASK)
        {
        case ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL:

            AcpiOsPrintf ("External/virtual  ");
            break;

        case ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL:

            AcpiOsPrintf ("Internal/physical ");
            break;

        case ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL:

            AcpiOsPrintf ("Internal/virtual  ");
            break;

        default:

            AcpiOsPrintf ("INVALID TYPE      ");
            break;
        }

        /* Make sure that the table is mapped */

        Status = AcpiTbValidateTable (TableDesc);
        if (ACPI_FAILURE (Status))
        {
            return;
        }

        /* Dump the table header */

        if (TableDesc->Pointer)
        {
            AcpiTbPrintTableHeader (TableDesc->Address, TableDesc->Pointer);
        }
        else
        {
            /* If the pointer is null, the table has been unloaded */

            ACPI_INFO (("%4.4s - Table has been unloaded",
                TableDesc->Signature.Ascii));
        }
    }
}