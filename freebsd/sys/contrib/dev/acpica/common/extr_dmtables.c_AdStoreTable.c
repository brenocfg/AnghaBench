#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_TABLE_DESC ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PTR_TO_PHYSADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL ; 
 int /*<<< orphan*/  AcpiTbGetNextTableDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiTbInitTableDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbValidateTable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ACPI_STATUS
AdStoreTable (
    ACPI_TABLE_HEADER       *Table,
    UINT32                  *TableIndex)
{
    ACPI_STATUS             Status;
    ACPI_TABLE_DESC         *TableDesc;


    Status = AcpiTbGetNextTableDescriptor (TableIndex, &TableDesc);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* Initialize added table */

    AcpiTbInitTableDescriptor (TableDesc, ACPI_PTR_TO_PHYSADDR (Table),
        ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL, Table);
    Status = AcpiTbValidateTable (TableDesc);
    return (Status);
}