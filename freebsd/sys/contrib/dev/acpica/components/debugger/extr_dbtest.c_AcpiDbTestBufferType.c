#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT32 ;
struct TYPE_6__ {int Length; int* Pointer; } ;
struct TYPE_7__ {TYPE_1__ Buffer; int /*<<< orphan*/  Type; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_DEBUG_LENGTH_FORMAT ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (int*) ; 
 int ACPI_MASK_BITS_ABOVE (int) ; 
 int ACPI_ROUND_BITS_UP_TO_BYTES (int) ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDbReadFromObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  AcpiDbWriteToObject (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  BUFFER_FILL_VALUE ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbTestBufferType (
    ACPI_NAMESPACE_NODE     *Node,
    UINT32                  BitLength)
{
    ACPI_OBJECT             *Temp1 = NULL;
    ACPI_OBJECT             *Temp2 = NULL;
    ACPI_OBJECT             *Temp3 = NULL;
    UINT8                   *Buffer;
    ACPI_OBJECT             WriteValue;
    ACPI_STATUS             Status;
    UINT32                  ByteLength;
    UINT32                  i;
    UINT8                   ExtraBits;


    ByteLength = ACPI_ROUND_BITS_UP_TO_BYTES (BitLength);
    if (ByteLength == 0)
    {
        AcpiOsPrintf (" Ignoring zero length buffer");
        return (AE_OK);
    }

    /* Allocate a local buffer */

    Buffer = ACPI_ALLOCATE_ZEROED (ByteLength);
    if (!Buffer)
    {
        return (AE_NO_MEMORY);
    }

    /* Read the original value */

    Status = AcpiDbReadFromObject (Node, ACPI_TYPE_BUFFER, &Temp1);
    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    /* Emit a few bytes of the buffer */

    AcpiOsPrintf (ACPI_DEBUG_LENGTH_FORMAT, BitLength, Temp1->Buffer.Length);
    for (i = 0; ((i < 8) && (i < ByteLength)); i++)
    {
        AcpiOsPrintf (" %2.2X", Temp1->Buffer.Pointer[i]);
    }
    AcpiOsPrintf ("...  ");

    /*
     * Write a new value.
     *
     * Handle possible extra bits at the end of the buffer. Can
     * happen for FieldUnits larger than an integer, but the bit
     * count is not an integral number of bytes. Zero out the
     * unused bits.
     */
    memset (Buffer, BUFFER_FILL_VALUE, ByteLength);
    ExtraBits = BitLength % 8;
    if (ExtraBits)
    {
        Buffer [ByteLength - 1] = ACPI_MASK_BITS_ABOVE (ExtraBits);
    }

    WriteValue.Type = ACPI_TYPE_BUFFER;
    WriteValue.Buffer.Length = ByteLength;
    WriteValue.Buffer.Pointer = Buffer;

    Status = AcpiDbWriteToObject (Node, &WriteValue);
    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    /* Ensure that we can read back the new value */

    Status = AcpiDbReadFromObject (Node, ACPI_TYPE_BUFFER, &Temp2);
    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    if (memcmp (Temp2->Buffer.Pointer, Buffer, ByteLength))
    {
        AcpiOsPrintf (" MISMATCH 2: New buffer value");
    }

    /* Write back the original value */

    WriteValue.Buffer.Length = ByteLength;
    WriteValue.Buffer.Pointer = Temp1->Buffer.Pointer;

    Status = AcpiDbWriteToObject (Node, &WriteValue);
    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    /* Ensure that we can read back the original value */

    Status = AcpiDbReadFromObject (Node, ACPI_TYPE_BUFFER, &Temp3);
    if (ACPI_FAILURE (Status))
    {
        goto Exit;
    }

    if (memcmp (Temp1->Buffer.Pointer,
            Temp3->Buffer.Pointer, ByteLength))
    {
        AcpiOsPrintf (" MISMATCH 3: While restoring original buffer");
    }

Exit:
    ACPI_FREE (Buffer);
    if (Temp1) {AcpiOsFree (Temp1);}
    if (Temp2) {AcpiOsFree (Temp2);}
    if (Temp3) {AcpiOsFree (Temp3);}
    return (Status);
}