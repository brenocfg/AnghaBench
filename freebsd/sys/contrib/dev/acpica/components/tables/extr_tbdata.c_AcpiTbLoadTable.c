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
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OWNER_ID ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TABLE_EVENT_LOAD ; 
 int /*<<< orphan*/  AcpiEvUpdateGpes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGetTableByIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiNsLoadTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbGetOwnerId (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbNotifyTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TbLoadTable ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiTbLoadTable (
    UINT32                  TableIndex,
    ACPI_NAMESPACE_NODE     *ParentNode)
{
    ACPI_TABLE_HEADER       *Table;
    ACPI_STATUS             Status;
    ACPI_OWNER_ID           OwnerId;


    ACPI_FUNCTION_TRACE (TbLoadTable);


    /*
     * Note: Now table is "INSTALLED", it must be validated before
     * using.
     */
    Status = AcpiGetTableByIndex (TableIndex, &Table);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    Status = AcpiNsLoadTable (TableIndex, ParentNode);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /*
     * Update GPEs for any new _Lxx/_Exx methods. Ignore errors. The host is
     * responsible for discovering any new wake GPEs by running _PRW methods
     * that may have been loaded by this table.
     */
    Status = AcpiTbGetOwnerId (TableIndex, &OwnerId);
    if (ACPI_SUCCESS (Status))
    {
        AcpiEvUpdateGpes (OwnerId);
    }

    /* Invoke table handler */

    AcpiTbNotifyTable (ACPI_TABLE_EVENT_LOAD, Table);
    return_ACPI_STATUS (Status);
}