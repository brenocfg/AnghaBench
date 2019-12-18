#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
typedef  int UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_7__ {scalar_t__ Integer; TYPE_4__* Arg; } ;
struct TYPE_8__ {int /*<<< orphan*/  DisasmFlags; TYPE_2__ Value; TYPE_4__* Next; } ;
struct TYPE_6__ {scalar_t__* Data; } ;
struct TYPE_9__ {TYPE_3__ Common; TYPE_1__ Named; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  size_t ACPI_SIZE ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int ACPI_DIV_2 (int) ; 
 int /*<<< orphan*/  ACPI_PARSEOP_IGNORE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  isprint (scalar_t__) ; 

BOOLEAN
AcpiDmIsUnicodeBuffer (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   *ByteData;
    UINT32                  ByteCount;
    UINT32                  WordCount;
    ACPI_PARSE_OBJECT       *SizeOp;
    ACPI_PARSE_OBJECT       *NextOp;
    UINT32                  i;


    /* Buffer size is the buffer argument */

    SizeOp = Op->Common.Value.Arg;

    /* Next, the initializer byte list to examine */

    NextOp = SizeOp->Common.Next;
    if (!NextOp)
    {
        return (FALSE);
    }

    /* Extract the byte list info */

    ByteData = NextOp->Named.Data;
    ByteCount = (UINT32) NextOp->Common.Value.Integer;
    WordCount = ACPI_DIV_2 (ByteCount);

    /*
     * Unicode string must have an even number of bytes and last
     * word must be zero
     */
    if ((!ByteCount)     ||
         (ByteCount < 4) ||
         (ByteCount & 1) ||
        ((UINT16 *) (void *) ByteData)[WordCount - 1] != 0)
    {
        return (FALSE);
    }

    /*
     * For each word, 1st byte must be printable ascii, and the
     * 2nd byte must be zero. This does not allow for escape
     * sequences, but it is the most secure way to detect a
     * unicode string.
     */
    for (i = 0; i < (ByteCount - 2); i += 2)
    {
        if ((ByteData[i] == 0) ||
            !(isprint (ByteData[i])) ||
            (ByteData[(ACPI_SIZE) i + 1] != 0))
        {
            return (FALSE);
        }
    }

    /* Ignore the Size argument in the disassembly of this buffer op */

    SizeOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
    return (TRUE);
}