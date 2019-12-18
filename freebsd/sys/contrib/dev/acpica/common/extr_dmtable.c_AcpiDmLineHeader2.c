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
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*,char*,...) ; 
 scalar_t__ AslGbl_DoTemplates ; 
 int /*<<< orphan*/  AslGbl_VerboseTemplates ; 

void
AcpiDmLineHeader2 (
    UINT32                  Offset,
    UINT32                  ByteLength,
    char                    *Name,
    UINT32                  Value)
{

    if (AslGbl_DoTemplates && !AslGbl_VerboseTemplates) /* Terse template */
    {
        if (ByteLength)
        {
            AcpiOsPrintf ("[%.4d] %30s %3d : ",
                ByteLength, Name, Value);
        }
        else
        {
            AcpiOsPrintf ("%36s % 3d : ",
                Name, Value);
        }
    }
    else /* Normal disassembler or verbose template */
    {
        if (ByteLength)
        {
            AcpiOsPrintf ("[%3.3Xh %4.4d %3d] %24s %3d : ",
                Offset, Offset, ByteLength, Name, Value);
        }
        else
        {
            AcpiOsPrintf ("[%3.3Xh %4.4d   ] %24s %3d : ",
                Offset, Offset, Name, Value);
        }
    }
}