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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  DT_FIELD ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_BUFFER_ELEMENT ; 
 int /*<<< orphan*/  ASL_MSG_BUFFER_LIST ; 
 int /*<<< orphan*/  AcpiUtAsciiToHexByte (char*,int /*<<< orphan*/ *) ; 
 char* AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  DtError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 char* DtNormalizeBuffer (char*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

UINT32
DtCompileBuffer (
    UINT8                   *Buffer,
    char                    *StringValue,
    DT_FIELD                *Field,
    UINT32                  ByteLength)
{
    char                    *Substring;
    ACPI_STATUS             Status;
    UINT32                  Count;
    UINT32                  i;


    /* Allow several different types of value separators */

    StringValue = DtNormalizeBuffer (StringValue, &Count);
    Substring = StringValue;
    if (Count != ByteLength)
    {
        sprintf(AslGbl_MsgBuffer,
            "Found %u values, must match expected count: %u",
            Count, ByteLength);
        DtError (ASL_ERROR, ASL_MSG_BUFFER_LIST, Field, AslGbl_MsgBuffer);
        goto Exit;
    }

    /* Each element of StringValue is now three chars (2 hex + 1 space) */

    for (i = 0; i < Count; i++, Substring += 3)
    {
        /* Check for byte value too long */

        if (*(&Substring[2]) &&
           (*(&Substring[2]) != ' '))
        {
            DtError (ASL_ERROR, ASL_MSG_BUFFER_ELEMENT, Field, Substring);
            goto Exit;
        }

        /* Convert two ASCII characters to one hex byte */

        Status = AcpiUtAsciiToHexByte (Substring, &Buffer[i]);
        if (ACPI_FAILURE (Status))
        {
            DtError (ASL_ERROR, ASL_MSG_BUFFER_ELEMENT, Field, Substring);
            goto Exit;
        }
    }

Exit:
    ACPI_FREE (StringValue);
    return (ByteLength - Count);
}