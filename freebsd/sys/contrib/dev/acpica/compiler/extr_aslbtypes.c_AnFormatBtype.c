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
typedef  int UINT32 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int ACPI_TYPE_EXTERNAL_MAX ; 
 char* AcpiUtGetTypeName (int) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

void
AnFormatBtype (
    char                    *Buffer,
    UINT32                  Btype)
{
    UINT32                  Type;
    BOOLEAN                 First = TRUE;


    *Buffer = 0;
    if (Btype == 0)
    {
        strcat (Buffer, "NoReturnValue");
        return;
    }

    for (Type = 1; Type <= ACPI_TYPE_EXTERNAL_MAX; Type++)
    {
        if (Btype & 0x00000001)
        {
            if (!First)
            {
                strcat (Buffer, "|");
            }

            First = FALSE;
            strcat (Buffer, AcpiUtGetTypeName (Type));
        }
        Btype >>= 1;
    }

    if (Btype & 0x00000001)
    {
        if (!First)
        {
            strcat (Buffer, "|");
        }

        First = FALSE;
        strcat (Buffer, "Reference");
    }

    Btype >>= 1;
    if (Btype & 0x00000001)
    {
        if (!First)
        {
            strcat (Buffer, "|");
        }

        strcat (Buffer, "Resource");
    }
}