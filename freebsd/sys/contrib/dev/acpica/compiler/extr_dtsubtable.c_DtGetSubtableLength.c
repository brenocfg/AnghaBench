#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_8__ {char* Name; int Opcode; } ;
struct TYPE_7__ {struct TYPE_7__* Next; } ;
typedef  TYPE_1__ DT_FIELD ;
typedef  TYPE_2__ ACPI_DMTABLE_INFO ;

/* Variables and functions */
 int ACPI_DMT_EXTRA_TEXT ; 
#define  ACPI_DMT_GAS 130 
#define  ACPI_DMT_HESTNTFY 129 
#define  ACPI_DMT_IORTMEM 128 
 int /*<<< orphan*/  ASL_EOF ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  DtFatal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DtGetFieldLength (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

UINT32
DtGetSubtableLength (
    DT_FIELD                *Field,
    ACPI_DMTABLE_INFO       *Info)
{
    UINT32                  ByteLength = 0;
    UINT8                   Step;
    UINT8                   i;


    /* Walk entire Info table; Null name terminates */

    for (; Info->Name; Info++)
    {
        if (Info->Opcode == ACPI_DMT_EXTRA_TEXT)
        {
            continue;
        }

        if (!Field)
        {
            goto Error;
        }

        ByteLength += DtGetFieldLength (Field, Info);

        switch (Info->Opcode)
        {
        case ACPI_DMT_GAS:

            Step = 5;
            break;

        case ACPI_DMT_HESTNTFY:

            Step = 9;
            break;

        case ACPI_DMT_IORTMEM:

            Step = 10;
            break;

        default:

            Step = 1;
            break;
        }

        for (i = 0; i < Step; i++)
        {
            if (!Field)
            {
                goto Error;
            }

            Field = Field->Next;
        }
    }

    return (ByteLength);

Error:
    if (!Field)
    {
        sprintf (AslGbl_MsgBuffer, "Found NULL field - Field name \"%s\" needed",
            Info->Name);
        DtFatal (ASL_MSG_COMPILER_INTERNAL, NULL, AslGbl_MsgBuffer);
    }

    return (ASL_EOF);
}