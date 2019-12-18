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
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*,...) ; 
 scalar_t__ AslGbl_DoTemplates ; 
 int /*<<< orphan*/  AslGbl_VerboseTemplates ; 

void
AcpiDmLineHeader (
    UINT32                  Offset,
    UINT32                  ByteLength,
    char                    *Name)
{

    /* Allow a null name for fields that span multiple lines (large buffers) */

    if (!Name)
    {
        Name = "";
    }

    if (AslGbl_DoTemplates && !AslGbl_VerboseTemplates) /* Terse template */
    {
        if (ByteLength)
        {
            AcpiOsPrintf ("[%.4d] %34s : ", ByteLength, Name);
        }
        else
        {
            if (*Name)
            {
                AcpiOsPrintf ("%41s : ", Name);
            }
            else
            {
                AcpiOsPrintf ("%41s   ", Name);
            }
        }
    }
    else /* Normal disassembler or verbose template */
    {
        if (ByteLength)
        {
            AcpiOsPrintf ("[%3.3Xh %4.4d% 4d] %28s : ",
                Offset, Offset, ByteLength, Name);
        }
        else
        {
            if (*Name)
            {
                AcpiOsPrintf ("%44s : ", Name);
            }
            else
            {
                AcpiOsPrintf ("%44s   ", Name);
            }
        }
    }
}