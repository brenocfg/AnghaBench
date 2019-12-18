#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_3__ {char* Signature; char* Description; } ;
typedef  TYPE_1__ AH_TABLE ;

/* Variables and functions */
 int ACPI_CA_VERSION ; 
 TYPE_1__* AcpiGbl_SupportedTables ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
UtDisplaySupportedTables (
    void)
{
    const AH_TABLE          *TableData;
    UINT32                  i;


    printf ("\nACPI tables supported by iASL version %8.8X:\n"
        "  (Compiler, Disassembler, Template Generator)\n\n",
        ACPI_CA_VERSION);

    /* All ACPI tables with the common table header */

    printf ("\n  Supported ACPI tables:\n");
    for (TableData = AcpiGbl_SupportedTables, i = 1;
         TableData->Signature; TableData++, i++)
    {
        printf ("%8u) %s    %s\n", i,
            TableData->Signature, TableData->Description);
    }
}