#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
struct TYPE_16__ {int TargetType; size_t Value; TYPE_5__* Object; TYPE_5__** Where; int /*<<< orphan*/  Class; } ;
struct TYPE_15__ {int /*<<< orphan*/ * Pointer; } ;
struct TYPE_14__ {int /*<<< orphan*/  Value; } ;
struct TYPE_13__ {int Type; int ReferenceCount; } ;
struct TYPE_17__ {TYPE_4__ Reference; TYPE_3__ Buffer; TYPE_2__ Integer; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REFCLASS_TABLE ; 
#define  ACPI_TYPE_BUFFER 132 
#define  ACPI_TYPE_BUFFER_FIELD 131 
#define  ACPI_TYPE_INTEGER 130 
 int ACPI_TYPE_LOCAL_REFERENCE ; 
#define  ACPI_TYPE_PACKAGE 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_AML_TARGET_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiUtAddReference (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtCopyIobjectToIobject (TYPE_5__*,TYPE_5__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_5__*) ; 
 int /*<<< orphan*/  ExStoreObjectToIndex ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiExStoreObjectToIndex (
    ACPI_OPERAND_OBJECT     *SourceDesc,
    ACPI_OPERAND_OBJECT     *IndexDesc,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_OPERAND_OBJECT     *NewDesc;
    UINT8                   Value = 0;
    UINT32                  i;


    ACPI_FUNCTION_TRACE (ExStoreObjectToIndex);


    /*
     * Destination must be a reference pointer, and
     * must point to either a buffer or a package
     */
    switch (IndexDesc->Reference.TargetType)
    {
    case ACPI_TYPE_PACKAGE:
        /*
         * Storing to a package element. Copy the object and replace
         * any existing object with the new object. No implicit
         * conversion is performed.
         *
         * The object at *(IndexDesc->Reference.Where) is the
         * element within the package that is to be modified.
         * The parent package object is at IndexDesc->Reference.Object
         */
        ObjDesc = *(IndexDesc->Reference.Where);

        if (SourceDesc->Common.Type == ACPI_TYPE_LOCAL_REFERENCE &&
            SourceDesc->Reference.Class == ACPI_REFCLASS_TABLE)
        {
            /* This is a DDBHandle, just add a reference to it */

            AcpiUtAddReference (SourceDesc);
            NewDesc = SourceDesc;
        }
        else
        {
            /* Normal object, copy it */

            Status = AcpiUtCopyIobjectToIobject (
                SourceDesc, &NewDesc, WalkState);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }
        }

        if (ObjDesc)
        {
            /* Decrement reference count by the ref count of the parent package */

            for (i = 0;
                 i < ((ACPI_OPERAND_OBJECT *)
                        IndexDesc->Reference.Object)->Common.ReferenceCount;
                 i++)
            {
                AcpiUtRemoveReference (ObjDesc);
            }
        }

        *(IndexDesc->Reference.Where) = NewDesc;

        /* Increment ref count by the ref count of the parent package-1 */

        for (i = 1;
             i < ((ACPI_OPERAND_OBJECT *)
                    IndexDesc->Reference.Object)->Common.ReferenceCount;
             i++)
        {
            AcpiUtAddReference (NewDesc);
        }

        break;

    case ACPI_TYPE_BUFFER_FIELD:
        /*
         * Store into a Buffer or String (not actually a real BufferField)
         * at a location defined by an Index.
         *
         * The first 8-bit element of the source object is written to the
         * 8-bit Buffer location defined by the Index destination object,
         * according to the ACPI 2.0 specification.
         */

        /*
         * Make sure the target is a Buffer or String. An error should
         * not happen here, since the ReferenceObject was constructed
         * by the INDEX_OP code.
         */
        ObjDesc = IndexDesc->Reference.Object;
        if ((ObjDesc->Common.Type != ACPI_TYPE_BUFFER) &&
            (ObjDesc->Common.Type != ACPI_TYPE_STRING))
        {
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }

        /*
         * The assignment of the individual elements will be slightly
         * different for each source type.
         */
        switch (SourceDesc->Common.Type)
        {
        case ACPI_TYPE_INTEGER:

            /* Use the least-significant byte of the integer */

            Value = (UINT8) (SourceDesc->Integer.Value);
            break;

        case ACPI_TYPE_BUFFER:
        case ACPI_TYPE_STRING:

            /* Note: Takes advantage of common string/buffer fields */

            Value = SourceDesc->Buffer.Pointer[0];
            break;

        default:

            /* All other types are invalid */

            ACPI_ERROR ((AE_INFO,
                "Source must be type [Integer/Buffer/String], found [%s]",
                AcpiUtGetObjectTypeName (SourceDesc)));
            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }

        /* Store the source value into the target buffer byte */

        ObjDesc->Buffer.Pointer[IndexDesc->Reference.Value] = Value;
        break;

    default:
        ACPI_ERROR ((AE_INFO,
            "Target is not of type [Package/BufferField]"));
        Status = AE_AML_TARGET_TYPE;
        break;
    }

    return_ACPI_STATUS (Status);
}