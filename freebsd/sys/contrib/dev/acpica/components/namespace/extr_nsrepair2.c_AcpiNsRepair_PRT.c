#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_10__ {int /*<<< orphan*/  NodeFlags; int /*<<< orphan*/  FullPathname; int /*<<< orphan*/  ReturnFlags; } ;
struct TYPE_8__ {scalar_t__ Type; } ;
struct TYPE_7__ {scalar_t__ Count; TYPE_3__** Elements; } ;
struct TYPE_9__ {TYPE_2__ Common; TYPE_1__ Package; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_4__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_OBJECT_REPAIRED ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 

__attribute__((used)) static ACPI_STATUS
AcpiNsRepair_PRT (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_OPERAND_OBJECT     **ReturnObjectPtr)
{
    ACPI_OPERAND_OBJECT     *PackageObject = *ReturnObjectPtr;
    ACPI_OPERAND_OBJECT     **TopObjectList;
    ACPI_OPERAND_OBJECT     **SubObjectList;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_OPERAND_OBJECT     *SubPackage;
    UINT32                  ElementCount;
    UINT32                  Index;


    /* Each element in the _PRT package is a subpackage */

    TopObjectList = PackageObject->Package.Elements;
    ElementCount = PackageObject->Package.Count;

    /* Examine each subpackage */

    for (Index = 0; Index < ElementCount; Index++, TopObjectList++)
    {
        SubPackage = *TopObjectList;
        SubObjectList = SubPackage->Package.Elements;

        /* Check for minimum required element count */

        if (SubPackage->Package.Count < 4)
        {
            continue;
        }

        /*
         * If the BIOS has erroneously reversed the _PRT SourceName (index 2)
         * and the SourceIndex (index 3), fix it. _PRT is important enough to
         * workaround this BIOS error. This also provides compatibility with
         * other ACPI implementations.
         */
        ObjDesc = SubObjectList[3];
        if (!ObjDesc || (ObjDesc->Common.Type != ACPI_TYPE_INTEGER))
        {
            SubObjectList[3] = SubObjectList[2];
            SubObjectList[2] = ObjDesc;
            Info->ReturnFlags |= ACPI_OBJECT_REPAIRED;

            ACPI_WARN_PREDEFINED ((AE_INFO,
                Info->FullPathname, Info->NodeFlags,
                "PRT[%X]: Fixed reversed SourceName and SourceIndex",
                Index));
        }
    }

    return (AE_OK);
}