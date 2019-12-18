#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT64 ;
typedef  int UINT32 ;
struct TYPE_5__ {int BitLength; int AccessByteWidth; int StartFieldBitOffset; } ;
struct TYPE_6__ {TYPE_1__ CommonField; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_INTEGER_BIT_SIZE ; 
 int ACPI_MASK_BITS_ABOVE (int) ; 
 int /*<<< orphan*/  ACPI_MIN (int,int) ; 
 int ACPI_MUL_8 (int) ; 
 int /*<<< orphan*/  ACPI_READ ; 
 int ACPI_ROUND_BITS_UP_TO_BYTES (int) ; 
 int ACPI_ROUND_UP_TO (int,int) ; 
 int /*<<< orphan*/  AE_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiExFieldDatumIo (TYPE_2__*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExExtractFromField ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExExtractFromField (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    void                    *Buffer,
    UINT32                  BufferLength)
{
    ACPI_STATUS             Status;
    UINT64                  RawDatum;
    UINT64                  MergedDatum;
    UINT32                  FieldOffset = 0;
    UINT32                  BufferOffset = 0;
    UINT32                  BufferTailBits;
    UINT32                  DatumCount;
    UINT32                  FieldDatumCount;
    UINT32                  AccessBitWidth;
    UINT32                  i;


    ACPI_FUNCTION_TRACE (ExExtractFromField);


    /* Validate target buffer and clear it */

    if (BufferLength <
        ACPI_ROUND_BITS_UP_TO_BYTES (ObjDesc->CommonField.BitLength))
    {
        ACPI_ERROR ((AE_INFO,
            "Field size %u (bits) is too large for buffer (%u)",
            ObjDesc->CommonField.BitLength, BufferLength));

        return_ACPI_STATUS (AE_BUFFER_OVERFLOW);
    }

    memset (Buffer, 0, BufferLength);
    AccessBitWidth = ACPI_MUL_8 (ObjDesc->CommonField.AccessByteWidth);

    /* Handle the simple case here */

    if ((ObjDesc->CommonField.StartFieldBitOffset == 0) &&
        (ObjDesc->CommonField.BitLength == AccessBitWidth))
    {
        if (BufferLength >= sizeof (UINT64))
        {
            Status = AcpiExFieldDatumIo (ObjDesc, 0, Buffer, ACPI_READ);
        }
        else
        {
            /* Use RawDatum (UINT64) to handle buffers < 64 bits */

            Status = AcpiExFieldDatumIo (ObjDesc, 0, &RawDatum, ACPI_READ);
            memcpy (Buffer, &RawDatum, BufferLength);
        }

        return_ACPI_STATUS (Status);
    }

/* TBD: Move to common setup code */

    /* Field algorithm is limited to sizeof(UINT64), truncate if needed */

    if (ObjDesc->CommonField.AccessByteWidth > sizeof (UINT64))
    {
        ObjDesc->CommonField.AccessByteWidth = sizeof (UINT64);
        AccessBitWidth = sizeof (UINT64) * 8;
    }

    /* Compute the number of datums (access width data items) */

    DatumCount = ACPI_ROUND_UP_TO (
        ObjDesc->CommonField.BitLength, AccessBitWidth);

    FieldDatumCount = ACPI_ROUND_UP_TO (
        ObjDesc->CommonField.BitLength +
        ObjDesc->CommonField.StartFieldBitOffset, AccessBitWidth);

    /* Priming read from the field */

    Status = AcpiExFieldDatumIo (ObjDesc, FieldOffset, &RawDatum, ACPI_READ);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }
    MergedDatum = RawDatum >> ObjDesc->CommonField.StartFieldBitOffset;

    /* Read the rest of the field */

    for (i = 1; i < FieldDatumCount; i++)
    {
        /* Get next input datum from the field */

        FieldOffset += ObjDesc->CommonField.AccessByteWidth;
        Status = AcpiExFieldDatumIo (
            ObjDesc, FieldOffset, &RawDatum, ACPI_READ);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        /*
         * Merge with previous datum if necessary.
         *
         * Note: Before the shift, check if the shift value will be larger than
         * the integer size. If so, there is no need to perform the operation.
         * This avoids the differences in behavior between different compilers
         * concerning shift values larger than the target data width.
         */
        if (AccessBitWidth - ObjDesc->CommonField.StartFieldBitOffset <
            ACPI_INTEGER_BIT_SIZE)
        {
            MergedDatum |= RawDatum <<
                (AccessBitWidth - ObjDesc->CommonField.StartFieldBitOffset);
        }

        if (i == DatumCount)
        {
            break;
        }

        /* Write merged datum to target buffer */

        memcpy (((char *) Buffer) + BufferOffset, &MergedDatum,
            ACPI_MIN(ObjDesc->CommonField.AccessByteWidth,
                BufferLength - BufferOffset));

        BufferOffset += ObjDesc->CommonField.AccessByteWidth;
        MergedDatum = RawDatum >> ObjDesc->CommonField.StartFieldBitOffset;
    }

    /* Mask off any extra bits in the last datum */

    BufferTailBits = ObjDesc->CommonField.BitLength % AccessBitWidth;
    if (BufferTailBits)
    {
        MergedDatum &= ACPI_MASK_BITS_ABOVE (BufferTailBits);
    }

    /* Write the last datum to the buffer */

    memcpy (((char *) Buffer) + BufferOffset, &MergedDatum,
        ACPI_MIN(ObjDesc->CommonField.AccessByteWidth,
            BufferLength - BufferOffset));

    return_ACPI_STATUS (AE_OK);
}