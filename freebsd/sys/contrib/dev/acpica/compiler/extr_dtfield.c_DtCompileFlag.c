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
typedef  int UINT8 ;
typedef  int UINT64 ;
typedef  int UINT32 ;
struct TYPE_8__ {int Opcode; } ;
struct TYPE_7__ {int /*<<< orphan*/  Value; } ;
typedef  TYPE_1__ DT_FIELD ;
typedef  TYPE_2__ ACPI_DMTABLE_INFO ;

/* Variables and functions */
#define  ACPI_DMT_FLAG0 144 
#define  ACPI_DMT_FLAG1 143 
#define  ACPI_DMT_FLAG2 142 
#define  ACPI_DMT_FLAG3 141 
#define  ACPI_DMT_FLAG4 140 
#define  ACPI_DMT_FLAG5 139 
#define  ACPI_DMT_FLAG6 138 
#define  ACPI_DMT_FLAG7 137 
#define  ACPI_DMT_FLAGS0 136 
#define  ACPI_DMT_FLAGS1 135 
#define  ACPI_DMT_FLAGS16_16 134 
#define  ACPI_DMT_FLAGS2 133 
#define  ACPI_DMT_FLAGS4 132 
#define  ACPI_DMT_FLAGS4_0 131 
#define  ACPI_DMT_FLAGS4_12 130 
#define  ACPI_DMT_FLAGS4_4 129 
#define  ACPI_DMT_FLAGS4_8 128 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 int /*<<< orphan*/  ASL_MSG_FLAG_VALUE ; 
 int AcpiUtImplicitStrtoul64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  DtError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtFatal (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

void
DtCompileFlag (
    UINT8                   *Buffer,
    DT_FIELD                *Field,
    ACPI_DMTABLE_INFO       *Info)
{
    UINT64                  Value = 0;
    UINT32                  BitLength = 1;
    UINT8                   BitPosition = 0;


    Value = AcpiUtImplicitStrtoul64 (Field->Value);

    switch (Info->Opcode)
    {
    case ACPI_DMT_FLAG0:
    case ACPI_DMT_FLAG1:
    case ACPI_DMT_FLAG2:
    case ACPI_DMT_FLAG3:
    case ACPI_DMT_FLAG4:
    case ACPI_DMT_FLAG5:
    case ACPI_DMT_FLAG6:
    case ACPI_DMT_FLAG7:

        BitPosition = Info->Opcode;
        BitLength = 1;
        break;

    case ACPI_DMT_FLAGS0:

        BitPosition = 0;
        BitLength = 2;
        break;


    case ACPI_DMT_FLAGS1:

        BitPosition = 1;
        BitLength = 2;
        break;


    case ACPI_DMT_FLAGS2:

        BitPosition = 2;
        BitLength = 2;
        break;

    case ACPI_DMT_FLAGS4:

        BitPosition = 4;
        BitLength = 2;
        break;

    case ACPI_DMT_FLAGS4_0:

        BitPosition = 0;
        BitLength = 4;
        break;

    case ACPI_DMT_FLAGS4_4:

        BitPosition = 4;
        BitLength = 4;
        break;

    case ACPI_DMT_FLAGS4_8:

        BitPosition = 8;
        BitLength = 4;
        break;

    case ACPI_DMT_FLAGS4_12:

        BitPosition = 12;
        BitLength = 4;
        break;

    case ACPI_DMT_FLAGS16_16:

        BitPosition = 16;
        BitLength = 16;
        break;

    default:

        DtFatal (ASL_MSG_COMPILER_INTERNAL, Field, "Invalid flag opcode");
        break;
    }

    /* Check range of the input flag value */

    if (Value >= ((UINT64) 1 << BitLength))
    {
        sprintf (AslGbl_MsgBuffer, "Maximum %u bit", BitLength);
        DtError (ASL_ERROR, ASL_MSG_FLAG_VALUE, Field, AslGbl_MsgBuffer);
        Value = 0;
    }

    *Buffer |= (UINT8) (Value << BitPosition);
}