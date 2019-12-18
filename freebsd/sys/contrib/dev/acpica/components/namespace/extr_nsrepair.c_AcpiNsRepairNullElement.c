#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int UINT32 ;
struct TYPE_16__ {int /*<<< orphan*/  ReturnFlags; int /*<<< orphan*/  FullPathname; TYPE_3__* ParentPackage; } ;
struct TYPE_12__ {int /*<<< orphan*/  ReferenceCount; } ;
struct TYPE_15__ {TYPE_1__ Common; } ;
struct TYPE_13__ {int /*<<< orphan*/  ReferenceCount; } ;
struct TYPE_14__ {TYPE_2__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_5__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_OBJECT_REPAIRED ; 
 int ACPI_RTYPE_BUFFER ; 
 int ACPI_RTYPE_INTEGER ; 
 int ACPI_RTYPE_STRING ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_4__* AcpiUtCreateBufferObject (int /*<<< orphan*/ ) ; 
 TYPE_4__* AcpiUtCreateIntegerObject (int /*<<< orphan*/ ) ; 
 TYPE_4__* AcpiUtCreateStringObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_4__*) ; 
 int /*<<< orphan*/  NsRepairNullElement ; 

ACPI_STATUS
AcpiNsRepairNullElement (
    ACPI_EVALUATE_INFO      *Info,
    UINT32                  ExpectedBtypes,
    UINT32                  PackageIndex,
    ACPI_OPERAND_OBJECT     **ReturnObjectPtr)
{
    ACPI_OPERAND_OBJECT     *ReturnObject = *ReturnObjectPtr;
    ACPI_OPERAND_OBJECT     *NewObject;


    ACPI_FUNCTION_NAME (NsRepairNullElement);


    /* No repair needed if return object is non-NULL */

    if (ReturnObject)
    {
        return (AE_OK);
    }

    /*
     * Attempt to repair a NULL element of a Package object. This applies to
     * predefined names that return a fixed-length package and each element
     * is required. It does not apply to variable-length packages where NULL
     * elements are allowed, especially at the end of the package.
     */
    if (ExpectedBtypes & ACPI_RTYPE_INTEGER)
    {
        /* Need an Integer - create a zero-value integer */

        NewObject = AcpiUtCreateIntegerObject ((UINT64) 0);
    }
    else if (ExpectedBtypes & ACPI_RTYPE_STRING)
    {
        /* Need a String - create a NULL string */

        NewObject = AcpiUtCreateStringObject (0);
    }
    else if (ExpectedBtypes & ACPI_RTYPE_BUFFER)
    {
        /* Need a Buffer - create a zero-length buffer */

        NewObject = AcpiUtCreateBufferObject (0);
    }
    else
    {
        /* Error for all other expected types */

        return (AE_AML_OPERAND_TYPE);
    }

    if (!NewObject)
    {
        return (AE_NO_MEMORY);
    }

    /* Set the reference count according to the parent Package object */

    NewObject->Common.ReferenceCount =
        Info->ParentPackage->Common.ReferenceCount;

    ACPI_DEBUG_PRINT ((ACPI_DB_REPAIR,
        "%s: Converted NULL package element to expected %s at index %u\n",
        Info->FullPathname, AcpiUtGetObjectTypeName (NewObject),
        PackageIndex));

    *ReturnObjectPtr = NewObject;
    Info->ReturnFlags |= ACPI_OBJECT_REPAIRED;
    return (AE_OK);
}