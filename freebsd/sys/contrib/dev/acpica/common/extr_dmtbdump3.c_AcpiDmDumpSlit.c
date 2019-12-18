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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_7__ {scalar_t__ Entry; scalar_t__ LocalityCount; } ;
struct TYPE_6__ {scalar_t__ Length; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 TYPE_4__* ACPI_CAST_PTR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TABLE_SLIT ; 
 int /*<<< orphan*/  AcpiDmDumpTable (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmLineHeader (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDmLineHeader2 (scalar_t__,scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  AcpiDmTableInfoSlit ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/ * Entry ; 

void
AcpiDmDumpSlit (
    ACPI_TABLE_HEADER       *Table)
{
    ACPI_STATUS             Status;
    UINT32                  Offset;
    UINT8                   *Row;
    UINT32                  Localities;
    UINT32                  i;
    UINT32                  j;


    /* Main table */

    Status = AcpiDmDumpTable (Table->Length, 0, Table, 0, AcpiDmTableInfoSlit);
    if (ACPI_FAILURE (Status))
    {
        return;
    }

    /* Display the Locality NxN Matrix */

    Localities = (UINT32) ACPI_CAST_PTR (ACPI_TABLE_SLIT, Table)->LocalityCount;
    Offset = ACPI_OFFSET (ACPI_TABLE_SLIT, Entry[0]);
    Row = (UINT8 *) ACPI_CAST_PTR (ACPI_TABLE_SLIT, Table)->Entry;

    for (i = 0; i < Localities; i++)
    {
        /* Display one row of the matrix */

        AcpiDmLineHeader2 (Offset, Localities, "Locality", i);
        for  (j = 0; j < Localities; j++)
        {
            /* Check for beyond EOT */

            if (Offset >= Table->Length)
            {
                AcpiOsPrintf (
                    "\n**** Not enough room in table for all localities\n");
                return;
            }

            AcpiOsPrintf ("%2.2X", Row[j]);
            Offset++;

            /* Display up to 16 bytes per output row */

            if ((j+1) < Localities)
            {
                AcpiOsPrintf (" ");

                if (j && (((j+1) % 16) == 0))
                {
                    AcpiOsPrintf ("\\\n"); /* With line continuation char */
                    AcpiDmLineHeader (Offset, 0, NULL);
                }
            }
        }

        /* Point to next row */

        AcpiOsPrintf ("\n");
        Row += Localities;
    }
}