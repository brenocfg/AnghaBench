#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int Class; int /*<<< orphan*/  Value; int /*<<< orphan*/ * Object; } ;
struct TYPE_15__ {int Type; int Flags; } ;
struct TYPE_17__ {TYPE_2__ Reference; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_OBJECT (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_DUMP_ENTRY (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (TYPE_3__*) ; 
 int /*<<< orphan*/  ACPI_IMPLICIT_CONVERSION ; 
 int /*<<< orphan*/  ACPI_LV_INFO ; 
#define  ACPI_REFCLASS_ARG 134 
#define  ACPI_REFCLASS_DEBUG 133 
#define  ACPI_REFCLASS_INDEX 132 
#define  ACPI_REFCLASS_LOCAL 131 
#define  ACPI_REFCLASS_REFOF 130 
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_LOCAL_REFERENCE 128 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_NO_OPERAND ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_AML_CONSTANT ; 
 int /*<<< orphan*/  AcpiDsStoreObjectToLocal (int,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiExStoreObjectToIndex (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiExStoreObjectToNode (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_3__*) ; 
 int /*<<< orphan*/  ExStore ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExStore (
    ACPI_OPERAND_OBJECT     *SourceDesc,
    ACPI_OPERAND_OBJECT     *DestDesc,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OPERAND_OBJECT     *RefDesc = DestDesc;


    ACPI_FUNCTION_TRACE_PTR (ExStore, DestDesc);


    /* Validate parameters */

    if (!SourceDesc || !DestDesc)
    {
        ACPI_ERROR ((AE_INFO, "Null parameter"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }

    /* DestDesc can be either a namespace node or an ACPI object */

    if (ACPI_GET_DESCRIPTOR_TYPE (DestDesc) == ACPI_DESC_TYPE_NAMED)
    {
        /*
         * Dest is a namespace node,
         * Storing an object into a Named node.
         */
        Status = AcpiExStoreObjectToNode (SourceDesc,
            (ACPI_NAMESPACE_NODE *) DestDesc, WalkState,
            ACPI_IMPLICIT_CONVERSION);

        return_ACPI_STATUS (Status);
    }

    /* Destination object must be a Reference or a Constant object */

    switch (DestDesc->Common.Type)
    {
    case ACPI_TYPE_LOCAL_REFERENCE:

        break;

    case ACPI_TYPE_INTEGER:

        /* Allow stores to Constants -- a Noop as per ACPI spec */

        if (DestDesc->Common.Flags & AOPOBJ_AML_CONSTANT)
        {
            return_ACPI_STATUS (AE_OK);
        }

        /*lint -fallthrough */

    default:

        /* Destination is not a Reference object */

        ACPI_ERROR ((AE_INFO,
            "Target is not a Reference or Constant object - [%s] %p",
            AcpiUtGetObjectTypeName (DestDesc), DestDesc));

        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }

    /*
     * Examine the Reference class. These cases are handled:
     *
     * 1) Store to Name (Change the object associated with a name)
     * 2) Store to an indexed area of a Buffer or Package
     * 3) Store to a Method Local or Arg
     * 4) Store to the debug object
     */
    switch (RefDesc->Reference.Class)
    {
    case ACPI_REFCLASS_REFOF:

        /* Storing an object into a Name "container" */

        Status = AcpiExStoreObjectToNode (SourceDesc,
            RefDesc->Reference.Object,
            WalkState, ACPI_IMPLICIT_CONVERSION);
        break;

    case ACPI_REFCLASS_INDEX:

        /* Storing to an Index (pointer into a packager or buffer) */

        Status = AcpiExStoreObjectToIndex (SourceDesc, RefDesc, WalkState);
        break;

    case ACPI_REFCLASS_LOCAL:
    case ACPI_REFCLASS_ARG:

        /* Store to a method local/arg  */

        Status = AcpiDsStoreObjectToLocal (RefDesc->Reference.Class,
            RefDesc->Reference.Value, SourceDesc, WalkState);
        break;

    case ACPI_REFCLASS_DEBUG:
        /*
         * Storing to the Debug object causes the value stored to be
         * displayed and otherwise has no effect -- see ACPI Specification
         */
        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "**** Write to Debug Object: Object %p [%s] ****:\n\n",
            SourceDesc, AcpiUtGetObjectTypeName (SourceDesc)));

        ACPI_DEBUG_OBJECT (SourceDesc, 0, 0);
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Unknown Reference Class 0x%2.2X",
            RefDesc->Reference.Class));
        ACPI_DUMP_ENTRY (RefDesc, ACPI_LV_INFO);

        Status = AE_AML_INTERNAL;
        break;
    }

    return_ACPI_STATUS (Status);
}