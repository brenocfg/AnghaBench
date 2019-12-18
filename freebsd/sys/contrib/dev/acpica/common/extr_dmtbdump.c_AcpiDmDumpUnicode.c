#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UINT8 ;
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmDumpBuffer (void*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  isprint (scalar_t__) ; 

void
AcpiDmDumpUnicode (
    void                    *Table,
    UINT32                  BufferOffset,
    UINT32                  ByteLength)
{
    UINT8                   *Buffer;
    UINT32                  Length;
    UINT32                  i;


    Buffer = ((UINT8 *) Table) + BufferOffset;
    Length = ByteLength - 2; /* Last two bytes are the null terminator */

    /* Ensure all low bytes are entirely printable ASCII */

    for (i = 0; i < Length; i += 2)
    {
        if (!isprint (Buffer[i]))
        {
            goto DumpRawBuffer;
        }
    }

    /* Ensure all high bytes are zero */

    for (i = 1; i < Length; i += 2)
    {
        if (Buffer[i])
        {
            goto DumpRawBuffer;
        }
    }

    /* Dump the buffer as a normal string */

    AcpiOsPrintf ("\"");
    for (i = 0; i < Length; i += 2)
    {
        AcpiOsPrintf ("%c", Buffer[i]);
    }

    AcpiOsPrintf ("\"\n");
    return;

DumpRawBuffer:
    AcpiDmDumpBuffer (Table, BufferOffset, ByteLength,
        BufferOffset, NULL);
    AcpiOsPrintf ("\n");
}