#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_21__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_16__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_35__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Data; } ;
struct TYPE_34__ {int /*<<< orphan*/  AmlLength; int /*<<< orphan*/  AmlStart; } ;
struct TYPE_33__ {int Flags; TYPE_11__* NextObject; } ;
struct TYPE_32__ {TYPE_16__* BankObj; TYPE_16__* RegionObj; int /*<<< orphan*/  BaseByteOffset; int /*<<< orphan*/  StartFieldBitOffset; int /*<<< orphan*/  Value; } ;
struct TYPE_31__ {int /*<<< orphan*/  AccessByteWidth; TYPE_16__* RegionObj; int /*<<< orphan*/  BaseByteOffset; int /*<<< orphan*/  StartFieldBitOffset; int /*<<< orphan*/  PinNumberIndex; int /*<<< orphan*/  ResourceLength; int /*<<< orphan*/  ResourceBuffer; int /*<<< orphan*/  AccessLength; } ;
struct TYPE_30__ {int BitLength; int /*<<< orphan*/  AccessByteWidth; int /*<<< orphan*/  Node; } ;
struct TYPE_29__ {int /*<<< orphan*/  SpaceId; } ;
struct TYPE_28__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Pointer; } ;
struct TYPE_27__ {TYPE_9__ Named; } ;
struct TYPE_26__ {TYPE_11__* Object; } ;
struct TYPE_25__ {TYPE_3__ Region; } ;
struct TYPE_24__ {int FieldType; int /*<<< orphan*/  FieldNode; int /*<<< orphan*/  FieldBitPosition; int /*<<< orphan*/  DataRegisterNode; int /*<<< orphan*/  RegisterNode; int /*<<< orphan*/  RegionNode; int /*<<< orphan*/  BankValue; int /*<<< orphan*/  PinNumberIndex; int /*<<< orphan*/  ResourceLength; int /*<<< orphan*/  ResourceBuffer; TYPE_1__* ConnectionNode; int /*<<< orphan*/  AccessLength; int /*<<< orphan*/  FieldBitLength; int /*<<< orphan*/  Attribute; int /*<<< orphan*/  FieldFlags; } ;
struct TYPE_22__ {TYPE_16__* DataObj; TYPE_16__* IndexObj; scalar_t__ Value; int /*<<< orphan*/  BaseByteOffset; int /*<<< orphan*/  StartFieldBitOffset; int /*<<< orphan*/  AccessByteWidth; } ;
struct TYPE_23__ {TYPE_10__ IndexField; TYPE_5__ Field; TYPE_8__ Extra; TYPE_7__ Common; TYPE_6__ BankField; TYPE_4__ CommonField; TYPE_2__ Buffer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_11__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_12__ ACPI_CREATE_FIELD_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_EC ; 
 TYPE_21__* ACPI_CAST_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DB_BFIELD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DIV_8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PARSE_OBJECT ; 
 scalar_t__ ACPI_ROUND_BITS_UP_TO_BYTES (int) ; 
 int /*<<< orphan*/  ACPI_ROUND_DOWN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ACPI_TYPE_LOCAL_BANK_FIELD 130 
#define  ACPI_TYPE_LOCAL_INDEX_FIELD 129 
#define  ACPI_TYPE_LOCAL_REGION_FIELD 128 
 scalar_t__ ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_NO_OPERAND ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiDsGetBufferArguments (TYPE_11__*) ; 
 int /*<<< orphan*/  AcpiExPrepCommonFieldObject (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiNsAttachObject (int /*<<< orphan*/ ,TYPE_11__*,scalar_t__) ; 
 void* AcpiNsGetAttachedObject (int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiNsGetType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtAddReference (TYPE_16__*) ; 
 TYPE_11__* AcpiUtCreateInternalObject (int) ; 
 int /*<<< orphan*/  AcpiUtDeleteObjectDesc (TYPE_11__*) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetTypeName (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_11__*) ; 
 int /*<<< orphan*/  ExPrepFieldValue ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExPrepFieldValue (
    ACPI_CREATE_FIELD_INFO  *Info)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_OPERAND_OBJECT     *SecondDesc = NULL;
    ACPI_STATUS             Status;
    UINT32                  AccessByteWidth;
    UINT32                  Type;


    ACPI_FUNCTION_TRACE (ExPrepFieldValue);


    /* Parameter validation */

    if (Info->FieldType != ACPI_TYPE_LOCAL_INDEX_FIELD)
    {
        if (!Info->RegionNode)
        {
            ACPI_ERROR ((AE_INFO, "Null RegionNode"));
            return_ACPI_STATUS (AE_AML_NO_OPERAND);
        }

        Type = AcpiNsGetType (Info->RegionNode);
        if (Type != ACPI_TYPE_REGION)
        {
            ACPI_ERROR ((AE_INFO, "Needed Region, found type 0x%X (%s)",
                Type, AcpiUtGetTypeName (Type)));

            return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
        }
    }

    /* Allocate a new field object */

    ObjDesc = AcpiUtCreateInternalObject (Info->FieldType);
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Initialize areas of the object that are common to all fields */

    ObjDesc->CommonField.Node = Info->FieldNode;
    Status = AcpiExPrepCommonFieldObject (ObjDesc,
        Info->FieldFlags, Info->Attribute,
        Info->FieldBitPosition, Info->FieldBitLength);
    if (ACPI_FAILURE (Status))
    {
        AcpiUtDeleteObjectDesc (ObjDesc);
        return_ACPI_STATUS (Status);
    }

    /* Initialize areas of the object that are specific to the field type */

    switch (Info->FieldType)
    {
    case ACPI_TYPE_LOCAL_REGION_FIELD:

        ObjDesc->Field.RegionObj = AcpiNsGetAttachedObject (Info->RegionNode);

        /* Fields specific to GenericSerialBus fields */

        ObjDesc->Field.AccessLength = Info->AccessLength;

        if (Info->ConnectionNode)
        {
            SecondDesc = Info->ConnectionNode->Object;
            if (!(SecondDesc->Common.Flags & AOPOBJ_DATA_VALID))
            {
                Status = AcpiDsGetBufferArguments (SecondDesc);
                if (ACPI_FAILURE (Status))
                {
                    AcpiUtDeleteObjectDesc (ObjDesc);
                    return_ACPI_STATUS (Status);
                }
            }

            ObjDesc->Field.ResourceBuffer =
                SecondDesc->Buffer.Pointer;
            ObjDesc->Field.ResourceLength =
                (UINT16) SecondDesc->Buffer.Length;
        }
        else if (Info->ResourceBuffer)
        {
            ObjDesc->Field.ResourceBuffer = Info->ResourceBuffer;
            ObjDesc->Field.ResourceLength = Info->ResourceLength;
        }

        ObjDesc->Field.PinNumberIndex = Info->PinNumberIndex;

        /* Allow full data read from EC address space */

        if ((ObjDesc->Field.RegionObj->Region.SpaceId == ACPI_ADR_SPACE_EC) &&
            (ObjDesc->CommonField.BitLength > 8))
        {
            AccessByteWidth = ACPI_ROUND_BITS_UP_TO_BYTES (
                ObjDesc->CommonField.BitLength);

            /* Maximum byte width supported is 255 */

            if (AccessByteWidth < 256)
            {
                ObjDesc->CommonField.AccessByteWidth =
                    (UINT8) AccessByteWidth;
            }
        }

        /* An additional reference for the container */

        AcpiUtAddReference (ObjDesc->Field.RegionObj);

        ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
            "RegionField: BitOff %X, Off %X, Gran %X, Region %p\n",
            ObjDesc->Field.StartFieldBitOffset,
            ObjDesc->Field.BaseByteOffset,
            ObjDesc->Field.AccessByteWidth,
            ObjDesc->Field.RegionObj));
        break;

    case ACPI_TYPE_LOCAL_BANK_FIELD:

        ObjDesc->BankField.Value = Info->BankValue;
        ObjDesc->BankField.RegionObj =
            AcpiNsGetAttachedObject (Info->RegionNode);
        ObjDesc->BankField.BankObj =
            AcpiNsGetAttachedObject (Info->RegisterNode);

        /* An additional reference for the attached objects */

        AcpiUtAddReference (ObjDesc->BankField.RegionObj);
        AcpiUtAddReference (ObjDesc->BankField.BankObj);

        ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
            "Bank Field: BitOff %X, Off %X, Gran %X, Region %p, BankReg %p\n",
            ObjDesc->BankField.StartFieldBitOffset,
            ObjDesc->BankField.BaseByteOffset,
            ObjDesc->Field.AccessByteWidth,
            ObjDesc->BankField.RegionObj,
            ObjDesc->BankField.BankObj));

        /*
         * Remember location in AML stream of the field unit
         * opcode and operands -- since the BankValue
         * operands must be evaluated.
         */
        SecondDesc = ObjDesc->Common.NextObject;
        SecondDesc->Extra.AmlStart = ACPI_CAST_PTR (ACPI_PARSE_OBJECT,
            Info->DataRegisterNode)->Named.Data;
        SecondDesc->Extra.AmlLength = ACPI_CAST_PTR (ACPI_PARSE_OBJECT,
            Info->DataRegisterNode)->Named.Length;

        break;

    case ACPI_TYPE_LOCAL_INDEX_FIELD:

        /* Get the Index and Data registers */

        ObjDesc->IndexField.IndexObj =
            AcpiNsGetAttachedObject (Info->RegisterNode);
        ObjDesc->IndexField.DataObj =
            AcpiNsGetAttachedObject (Info->DataRegisterNode);

        if (!ObjDesc->IndexField.DataObj || !ObjDesc->IndexField.IndexObj)
        {
            ACPI_ERROR ((AE_INFO, "Null Index Object during field prep"));
            AcpiUtDeleteObjectDesc (ObjDesc);
            return_ACPI_STATUS (AE_AML_INTERNAL);
        }

        /* An additional reference for the attached objects */

        AcpiUtAddReference (ObjDesc->IndexField.DataObj);
        AcpiUtAddReference (ObjDesc->IndexField.IndexObj);

        /*
         * April 2006: Changed to match MS behavior
         *
         * The value written to the Index register is the byte offset of the
         * target field in units of the granularity of the IndexField
         *
         * Previously, the value was calculated as an index in terms of the
         * width of the Data register, as below:
         *
         *      ObjDesc->IndexField.Value = (UINT32)
         *          (Info->FieldBitPosition / ACPI_MUL_8 (
         *              ObjDesc->Field.AccessByteWidth));
         *
         * February 2006: Tried value as a byte offset:
         *      ObjDesc->IndexField.Value = (UINT32)
         *          ACPI_DIV_8 (Info->FieldBitPosition);
         */
        ObjDesc->IndexField.Value = (UINT32) ACPI_ROUND_DOWN (
            ACPI_DIV_8 (Info->FieldBitPosition),
            ObjDesc->IndexField.AccessByteWidth);

        ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
            "IndexField: BitOff %X, Off %X, Value %X, "
            "Gran %X, Index %p, Data %p\n",
            ObjDesc->IndexField.StartFieldBitOffset,
            ObjDesc->IndexField.BaseByteOffset,
            ObjDesc->IndexField.Value,
            ObjDesc->Field.AccessByteWidth,
            ObjDesc->IndexField.IndexObj,
            ObjDesc->IndexField.DataObj));
        break;

    default:

        /* No other types should get here */

        break;
    }

    /*
     * Store the constructed descriptor (ObjDesc) into the parent Node,
     * preserving the current type of that NamedObj.
     */
    Status = AcpiNsAttachObject (
        Info->FieldNode, ObjDesc, AcpiNsGetType (Info->FieldNode));

    ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
        "Set NamedObj %p [%4.4s], ObjDesc %p\n",
        Info->FieldNode, AcpiUtGetNodeName (Info->FieldNode), ObjDesc));

    /* Remove local reference to the object */

    AcpiUtRemoveReference (ObjDesc);
    return_ACPI_STATUS (Status);
}