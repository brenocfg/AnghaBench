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
typedef  scalar_t__ UINT32 ;
struct TYPE_7__ {scalar_t__ Integer; TYPE_4__* Arg; } ;
struct TYPE_8__ {int /*<<< orphan*/  DisasmFlags; TYPE_2__ Value; TYPE_4__* Next; } ;
struct TYPE_6__ {int* Data; } ;
struct TYPE_9__ {TYPE_3__ Common; TYPE_1__ Named; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_PARSEOP_IGNORE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UUID_BUFFER_LENGTH ; 

BOOLEAN
AcpiDmIsUuidBuffer (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   *ByteData;
    UINT32                  ByteCount;
    ACPI_PARSE_OBJECT       *SizeOp;
    ACPI_PARSE_OBJECT       *NextOp;


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

    /* Byte count must be exactly 16 */

    if (ByteCount != UUID_BUFFER_LENGTH)
    {
        return (FALSE);
    }

    /* Check for valid "M" and "N" values (see function header above) */

    if (((ByteData[7] & 0xF0) == 0x00) || /* M={1,2,3,4,5} */
        ((ByteData[7] & 0xF0) > 0x50)  ||
        ((ByteData[8] & 0xF0) < 0x80)  || /* N={8,9,A,B} */
        ((ByteData[8] & 0xF0) > 0xB0))
    {
        return (FALSE);
    }

    /* Ignore the Size argument in the disassembly of this buffer op */

    SizeOp->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;
    return (TRUE);
}