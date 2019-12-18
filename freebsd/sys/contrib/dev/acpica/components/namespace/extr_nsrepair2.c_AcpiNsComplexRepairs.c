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
struct TYPE_3__ {int /*<<< orphan*/  (* RepairFunction ) (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;} ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_REPAIR_INFO ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  int /*<<< orphan*/  ACPI_EVALUATE_INFO ;

/* Variables and functions */
 TYPE_1__* AcpiNsMatchComplexRepair (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

ACPI_STATUS
AcpiNsComplexRepairs (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_STATUS             ValidateStatus,
    ACPI_OPERAND_OBJECT     **ReturnObjectPtr)
{
    const ACPI_REPAIR_INFO  *Predefined;
    ACPI_STATUS             Status;


    /* Check if this name is in the list of repairable names */

    Predefined = AcpiNsMatchComplexRepair (Node);
    if (!Predefined)
    {
        return (ValidateStatus);
    }

    Status = Predefined->RepairFunction (Info, ReturnObjectPtr);
    return (Status);
}