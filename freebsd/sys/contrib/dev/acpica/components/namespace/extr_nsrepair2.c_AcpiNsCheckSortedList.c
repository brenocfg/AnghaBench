#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_13__ {int /*<<< orphan*/  FullPathname; int /*<<< orphan*/  ReturnFlags; } ;
struct TYPE_11__ {scalar_t__ Value; } ;
struct TYPE_10__ {scalar_t__ Count; TYPE_4__** Elements; } ;
struct TYPE_9__ {scalar_t__ Type; } ;
struct TYPE_12__ {TYPE_3__ Integer; TYPE_2__ Package; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_5__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_OBJECT_REPAIRED ; 
 int /*<<< orphan*/  ACPI_SORT_ASCENDING ; 
 int /*<<< orphan*/  ACPI_SORT_DESCENDING ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_AML_PACKAGE_LIMIT ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsSortList (TYPE_4__**,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NsCheckSortedList ; 

__attribute__((used)) static ACPI_STATUS
AcpiNsCheckSortedList (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_OPERAND_OBJECT     *ReturnObject,
    UINT32                  StartIndex,
    UINT32                  ExpectedCount,
    UINT32                  SortIndex,
    UINT8                   SortDirection,
    char                    *SortKeyName)
{
    UINT32                  OuterElementCount;
    ACPI_OPERAND_OBJECT     **OuterElements;
    ACPI_OPERAND_OBJECT     **Elements;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    UINT32                  i;
    UINT32                  PreviousValue;


    ACPI_FUNCTION_NAME (NsCheckSortedList);


    /* The top-level object must be a package */

    if (ReturnObject->Common.Type != ACPI_TYPE_PACKAGE)
    {
        return (AE_AML_OPERAND_TYPE);
    }

    /*
     * NOTE: assumes list of subpackages contains no NULL elements.
     * Any NULL elements should have been removed by earlier call
     * to AcpiNsRemoveNullElements.
     */
    OuterElementCount = ReturnObject->Package.Count;
    if (!OuterElementCount || StartIndex >= OuterElementCount)
    {
        return (AE_AML_PACKAGE_LIMIT);
    }

    OuterElements = &ReturnObject->Package.Elements[StartIndex];
    OuterElementCount -= StartIndex;

    PreviousValue = 0;
    if (SortDirection == ACPI_SORT_DESCENDING)
    {
        PreviousValue = ACPI_UINT32_MAX;
    }

    /* Examine each subpackage */

    for (i = 0; i < OuterElementCount; i++)
    {
        /* Each element of the top-level package must also be a package */

        if ((*OuterElements)->Common.Type != ACPI_TYPE_PACKAGE)
        {
            return (AE_AML_OPERAND_TYPE);
        }

        /* Each subpackage must have the minimum length */

        if ((*OuterElements)->Package.Count < ExpectedCount)
        {
            return (AE_AML_PACKAGE_LIMIT);
        }

        Elements = (*OuterElements)->Package.Elements;
        ObjDesc = Elements[SortIndex];

        if (ObjDesc->Common.Type != ACPI_TYPE_INTEGER)
        {
            return (AE_AML_OPERAND_TYPE);
        }

        /*
         * The list must be sorted in the specified order. If we detect a
         * discrepancy, sort the entire list.
         */
        if (((SortDirection == ACPI_SORT_ASCENDING) &&
                (ObjDesc->Integer.Value < PreviousValue)) ||
            ((SortDirection == ACPI_SORT_DESCENDING) &&
                (ObjDesc->Integer.Value > PreviousValue)))
        {
            AcpiNsSortList (&ReturnObject->Package.Elements[StartIndex],
                OuterElementCount, SortIndex, SortDirection);

            Info->ReturnFlags |= ACPI_OBJECT_REPAIRED;

            ACPI_DEBUG_PRINT ((ACPI_DB_REPAIR,
                "%s: Repaired unsorted list - now sorted by %s\n",
                Info->FullPathname, SortKeyName));
            return (AE_OK);
        }

        PreviousValue = (UINT32) ObjDesc->Integer.Value;
        OuterElements++;
    }

    return (AE_OK);
}