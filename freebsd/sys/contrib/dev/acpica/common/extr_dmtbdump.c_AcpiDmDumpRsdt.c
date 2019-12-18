#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_6__ {size_t* TableOffsetEntry; } ;
struct TYPE_5__ {int Length; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 TYPE_3__* ACPI_CAST_PTR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ACPI_TABLE_RSDT ; 
 int /*<<< orphan*/  AcpiDmLineHeader2 (size_t,int,char*,size_t) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,size_t) ; 

void
AcpiDmDumpRsdt (
    ACPI_TABLE_HEADER       *Table)
{
    UINT32                  *Array;
    UINT32                  Entries;
    UINT32                  Offset;
    UINT32                  i;


    /* Point to start of table pointer array */

    Array = ACPI_CAST_PTR (ACPI_TABLE_RSDT, Table)->TableOffsetEntry;
    Offset = sizeof (ACPI_TABLE_HEADER);

    /* RSDT uses 32-bit pointers */

    Entries = (Table->Length - sizeof (ACPI_TABLE_HEADER)) / sizeof (UINT32);

    for (i = 0; i < Entries; i++)
    {
        AcpiDmLineHeader2 (Offset, sizeof (UINT32), "ACPI Table Address", i);
        AcpiOsPrintf ("%8.8X\n", Array[i]);
        Offset += sizeof (UINT32);
    }
}