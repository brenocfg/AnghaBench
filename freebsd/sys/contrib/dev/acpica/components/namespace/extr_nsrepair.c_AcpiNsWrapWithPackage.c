#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int ReturnFlags; int /*<<< orphan*/  FullPathname; } ;
struct TYPE_9__ {TYPE_2__** Elements; } ;
struct TYPE_10__ {TYPE_1__ Package; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_3__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int ACPI_OBJECT_REPAIRED ; 
 int ACPI_OBJECT_WRAPPED ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_2__* AcpiUtCreatePackageObject (int) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_2__*) ; 
 int /*<<< orphan*/  NsWrapWithPackage ; 

ACPI_STATUS
AcpiNsWrapWithPackage (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_OPERAND_OBJECT     *OriginalObject,
    ACPI_OPERAND_OBJECT     **ObjDescPtr)
{
    ACPI_OPERAND_OBJECT     *PkgObjDesc;


    ACPI_FUNCTION_NAME (NsWrapWithPackage);


    /*
     * Create the new outer package and populate it. The new
     * package will have a single element, the lone sub-object.
     */
    PkgObjDesc = AcpiUtCreatePackageObject (1);
    if (!PkgObjDesc)
    {
        return (AE_NO_MEMORY);
    }

    PkgObjDesc->Package.Elements[0] = OriginalObject;

    ACPI_DEBUG_PRINT ((ACPI_DB_REPAIR,
        "%s: Wrapped %s with expected Package object\n",
        Info->FullPathname, AcpiUtGetObjectTypeName (OriginalObject)));

    /* Return the new object in the object pointer */

    *ObjDescPtr = PkgObjDesc;
    Info->ReturnFlags |= ACPI_OBJECT_REPAIRED | ACPI_OBJECT_WRAPPED;
    return (AE_OK);
}