#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_12__ {int /*<<< orphan*/  NodeFlags; int /*<<< orphan*/  FullPathname; } ;
struct TYPE_10__ {scalar_t__ Value; } ;
struct TYPE_9__ {scalar_t__ Count; TYPE_3__** Elements; } ;
struct TYPE_11__ {TYPE_2__ Integer; TYPE_1__ Package; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_4__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SORT_DESCENDING ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsCheckSortedList (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ACPI_STATUS
AcpiNsRepair_PSS (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_OPERAND_OBJECT     **ReturnObjectPtr)
{
    ACPI_OPERAND_OBJECT     *ReturnObject = *ReturnObjectPtr;
    ACPI_OPERAND_OBJECT     **OuterElements;
    UINT32                  OuterElementCount;
    ACPI_OPERAND_OBJECT     **Elements;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    UINT32                  PreviousValue;
    ACPI_STATUS             Status;
    UINT32                  i;


    /*
     * Entries (subpackages) in the _PSS Package must be sorted by power
     * dissipation, in descending order. If it appears that the list is
     * incorrectly sorted, sort it. We sort by CpuFrequency, since this
     * should be proportional to the power.
     */
    Status = AcpiNsCheckSortedList (Info, ReturnObject, 0, 6, 0,
        ACPI_SORT_DESCENDING, "CpuFrequency");
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /*
     * We now know the list is correctly sorted by CPU frequency. Check if
     * the power dissipation values are proportional.
     */
    PreviousValue = ACPI_UINT32_MAX;
    OuterElements = ReturnObject->Package.Elements;
    OuterElementCount = ReturnObject->Package.Count;

    for (i = 0; i < OuterElementCount; i++)
    {
        Elements = (*OuterElements)->Package.Elements;
        ObjDesc = Elements[1]; /* Index1 = PowerDissipation */

        if ((UINT32) ObjDesc->Integer.Value > PreviousValue)
        {
            ACPI_WARN_PREDEFINED ((AE_INFO,
                Info->FullPathname, Info->NodeFlags,
                "SubPackage[%u,%u] - suspicious power dissipation values",
                i-1, i));
        }

        PreviousValue = (UINT32) ObjDesc->Integer.Value;
        OuterElements++;
    }

    return (AE_OK);
}