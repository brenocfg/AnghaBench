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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int /*<<< orphan*/  Template; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_DMTABLE_DATA ;

/* Variables and functions */
 scalar_t__ ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  AE_ERROR ; 
 TYPE_1__* AcpiDmGetTableData (char*) ; 
 int /*<<< orphan*/  AcpiUtIsSpecialTable (char*) ; 
 int /*<<< orphan*/  DtCreateOneTemplate (char*,int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static ACPI_STATUS
DtCreateOneTemplateFile (
    char                    *Signature,
    UINT32                  TableCount)
{
    const ACPI_DMTABLE_DATA *TableData;
    ACPI_STATUS             Status;


    /*
     * Validate signature and get the template data:
     *  1) Signature must be 4 characters
     *  2) Signature must be a recognized ACPI table
     *  3) There must be a template associated with the signature
     */
    if (strlen (Signature) != ACPI_NAMESEG_SIZE)
    {
        fprintf (stderr,
            "%s: Invalid ACPI table signature "
            "(length must be 4 characters)\n", Signature);
        return (AE_ERROR);
    }

    /*
     * Some slack for the two strange tables whose name is different than
     * their signatures: MADT->APIC and FADT->FACP.
     */
    if (!strcmp (Signature, "MADT"))
    {
        Signature = "APIC";
    }
    else if (!strcmp (Signature, "FADT"))
    {
        Signature = "FACP";
    }

    /* TableData will point to the template */

    TableData = AcpiDmGetTableData (Signature);
    if (TableData)
    {
        if (!TableData->Template)
        {
            fprintf (stderr, "%4.4s: No template available\n", Signature);
            return (AE_ERROR);
        }
    }
    else if (!AcpiUtIsSpecialTable (Signature))
    {
        fprintf (stderr,
            "%4.4s: Unrecognized ACPI table signature\n", Signature);
        return (AE_ERROR);
    }

    Status = DtCreateOneTemplate (Signature, TableCount, TableData);
    return (Status);
}