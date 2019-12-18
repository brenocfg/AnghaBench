#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_28__ {int /*<<< orphan*/  FieldFlags; int /*<<< orphan*/  BaseByteOffset; int /*<<< orphan*/  StartFieldBitOffset; int /*<<< orphan*/  BitLength; } ;
struct TYPE_27__ {scalar_t__ Type; int Flags; } ;
struct TYPE_26__ {int /*<<< orphan*/  BitLength; scalar_t__ BaseByteOffset; TYPE_5__* RegionObj; } ;
struct TYPE_22__ {int /*<<< orphan*/  Value; } ;
struct TYPE_21__ {void* Pointer; } ;
struct TYPE_29__ {TYPE_8__ CommonField; TYPE_7__ Common; TYPE_6__ Field; TYPE_2__ Integer; TYPE_1__ Buffer; } ;
struct TYPE_24__ {scalar_t__ InternalPccBuffer; } ;
struct TYPE_23__ {scalar_t__ SpaceId; } ;
struct TYPE_25__ {TYPE_4__ Field; TYPE_3__ Region; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_9__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_GPIO ; 
 scalar_t__ ACPI_ADR_SPACE_GSBUS ; 
 scalar_t__ ACPI_ADR_SPACE_IPMI ; 
 scalar_t__ ACPI_ADR_SPACE_PLATFORM_COMM ; 
 scalar_t__ ACPI_ADR_SPACE_SMBUS ; 
 int /*<<< orphan*/  ACPI_DB_BFIELD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_9__*) ; 
 scalar_t__ ACPI_ROUND_BITS_UP_TO_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER_FIELD ; 
 scalar_t__ ACPI_TYPE_LOCAL_REGION_FIELD ; 
 int /*<<< orphan*/  AE_AML_NO_OPERAND ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiDsGetBufferFieldArguments (TYPE_9__*) ; 
 int /*<<< orphan*/  AcpiExAcquireGlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiExExtractFromField (TYPE_9__*,void*,scalar_t__) ; 
 int /*<<< orphan*/  AcpiExReadGpio (TYPE_9__*,void*) ; 
 int /*<<< orphan*/  AcpiExReadSerialBus (TYPE_9__*,TYPE_9__**) ; 
 int /*<<< orphan*/  AcpiExReleaseGlobalLock (int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiGbl_IntegerByteWidth ; 
 TYPE_9__* AcpiUtCreateBufferObject (scalar_t__) ; 
 TYPE_9__* AcpiUtCreateIntegerObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_9__*) ; 
 int /*<<< orphan*/  ExReadDataFromField ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExReadDataFromField (
    ACPI_WALK_STATE         *WalkState,
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_OPERAND_OBJECT     **RetBufferDesc)
{
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *BufferDesc;
    void                    *Buffer;
    UINT32                  BufferLength;


    ACPI_FUNCTION_TRACE_PTR (ExReadDataFromField, ObjDesc);


    /* Parameter validation */

    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }
    if (!RetBufferDesc)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    if (ObjDesc->Common.Type == ACPI_TYPE_BUFFER_FIELD)
    {
        /*
         * If the BufferField arguments have not been previously evaluated,
         * evaluate them now and save the results.
         */
        if (!(ObjDesc->Common.Flags & AOPOBJ_DATA_VALID))
        {
            Status = AcpiDsGetBufferFieldArguments (ObjDesc);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }
        }
    }
    else if ((ObjDesc->Common.Type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
        (ObjDesc->Field.RegionObj->Region.SpaceId == ACPI_ADR_SPACE_SMBUS ||
         ObjDesc->Field.RegionObj->Region.SpaceId == ACPI_ADR_SPACE_GSBUS ||
         ObjDesc->Field.RegionObj->Region.SpaceId == ACPI_ADR_SPACE_IPMI))
    {
        /* SMBus, GSBus, IPMI serial */

        Status = AcpiExReadSerialBus (ObjDesc, RetBufferDesc);
        return_ACPI_STATUS (Status);
    }

    /*
     * Allocate a buffer for the contents of the field.
     *
     * If the field is larger than the current integer width, create
     * a BUFFER to hold it. Otherwise, use an INTEGER. This allows
     * the use of arithmetic operators on the returned value if the
     * field size is equal or smaller than an Integer.
     *
     * Note: Field.length is in bits.
     */
    BufferLength = (ACPI_SIZE) ACPI_ROUND_BITS_UP_TO_BYTES (
        ObjDesc->Field.BitLength);

    if (BufferLength > AcpiGbl_IntegerByteWidth)
    {
        /* Field is too large for an Integer, create a Buffer instead */

        BufferDesc = AcpiUtCreateBufferObject (BufferLength);
        if (!BufferDesc)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }
        Buffer = BufferDesc->Buffer.Pointer;
    }
    else
    {
        /* Field will fit within an Integer (normal case) */

        BufferDesc = AcpiUtCreateIntegerObject ((UINT64) 0);
        if (!BufferDesc)
        {
            return_ACPI_STATUS (AE_NO_MEMORY);
        }

        BufferLength = AcpiGbl_IntegerByteWidth;
        Buffer = &BufferDesc->Integer.Value;
    }

    if ((ObjDesc->Common.Type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
        (ObjDesc->Field.RegionObj->Region.SpaceId == ACPI_ADR_SPACE_GPIO))
    {
        /* General Purpose I/O */

        Status = AcpiExReadGpio (ObjDesc, Buffer);
        goto Exit;
    }
    else if ((ObjDesc->Common.Type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
        (ObjDesc->Field.RegionObj->Region.SpaceId == ACPI_ADR_SPACE_PLATFORM_COMM))
    {
        /*
         * Reading from a PCC field unit does not require the handler because
         * it only requires reading from the InternalPccBuffer.
         */
        ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
            "PCC FieldRead bits %u\n", ObjDesc->Field.BitLength));

        memcpy (Buffer, ObjDesc->Field.RegionObj->Field.InternalPccBuffer +
        ObjDesc->Field.BaseByteOffset, (ACPI_SIZE) ACPI_ROUND_BITS_UP_TO_BYTES (
            ObjDesc->Field.BitLength));

        *RetBufferDesc = BufferDesc;
        return AE_OK;
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
        "FieldRead [TO]:   Obj %p, Type %X, Buf %p, ByteLen %X\n",
        ObjDesc, ObjDesc->Common.Type, Buffer, BufferLength));
    ACPI_DEBUG_PRINT ((ACPI_DB_BFIELD,
        "FieldRead [FROM]: BitLen %X, BitOff %X, ByteOff %X\n",
        ObjDesc->CommonField.BitLength,
        ObjDesc->CommonField.StartFieldBitOffset,
        ObjDesc->CommonField.BaseByteOffset));

    /* Lock entire transaction if requested */

    AcpiExAcquireGlobalLock (ObjDesc->CommonField.FieldFlags);

    /* Read from the field */

    Status = AcpiExExtractFromField (ObjDesc, Buffer, BufferLength);
    AcpiExReleaseGlobalLock (ObjDesc->CommonField.FieldFlags);


Exit:
    if (ACPI_FAILURE (Status))
    {
        AcpiUtRemoveReference (BufferDesc);
    }
    else
    {
        *RetBufferDesc = BufferDesc;
    }

    return_ACPI_STATUS (Status);
}