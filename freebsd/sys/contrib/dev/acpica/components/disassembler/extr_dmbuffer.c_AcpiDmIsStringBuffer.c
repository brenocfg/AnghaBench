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
typedef  int UINT8 ;
typedef  int UINT32 ;
struct TYPE_7__ {scalar_t__ Integer; TYPE_4__* Arg; } ;
struct TYPE_8__ {TYPE_2__ Value; TYPE_4__* Next; } ;
struct TYPE_6__ {int* Data; } ;
struct TYPE_9__ {TYPE_3__ Common; TYPE_1__ Named; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  isprint (int) ; 

BOOLEAN
AcpiDmIsStringBuffer (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   *ByteData;
    UINT32                  ByteCount;
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

    /* Last byte must be the null terminator */

    if ((!ByteCount)     ||
         (ByteCount < 2) ||
         (ByteData[ByteCount-1] != 0))
    {
        return (FALSE);
    }

    /*
     * Check for a possible standalone resource EndTag, ignore it
     * here. However, this sequence is also the string "Y", but
     * this seems rare enough to be acceptable.
     */
    if ((ByteCount == 2) && (ByteData[0] == 0x79))
    {
        return (FALSE);
    }

    /* Check all bytes for ASCII */

    for (i = 0; i < (ByteCount - 1); i++)
    {
        /*
         * TBD: allow some escapes (non-ascii chars).
         * they will be handled in the string output routine
         */

        /* Not a string if not printable ascii */

        if (!isprint (ByteData[i]))
        {
            return (FALSE);
        }
    }

    return (TRUE);
}