#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int Opcode; char* Name; } ;
typedef  int /*<<< orphan*/  DT_FIELD ;
typedef  int /*<<< orphan*/  ACPI_IORT_MEMORY_ACCESS ;
typedef  int /*<<< orphan*/  ACPI_HEST_NOTIFY ;
typedef  int /*<<< orphan*/  ACPI_GENERIC_ADDRESS ;
typedef  TYPE_1__ ACPI_DMTABLE_INFO ;

/* Variables and functions */
#define  ACPI_DMT_ACCWIDTH 197 
#define  ACPI_DMT_ASF 196 
#define  ACPI_DMT_BUF10 195 
#define  ACPI_DMT_BUF12 194 
#define  ACPI_DMT_BUF128 193 
#define  ACPI_DMT_BUF16 192 
#define  ACPI_DMT_BUF7 191 
#define  ACPI_DMT_BUFFER 190 
#define  ACPI_DMT_CHKSUM 189 
#define  ACPI_DMT_DMAR 188 
#define  ACPI_DMT_DMAR_SCOPE 187 
#define  ACPI_DMT_EINJACT 186 
#define  ACPI_DMT_EINJINST 185 
#define  ACPI_DMT_ERSTACT 184 
#define  ACPI_DMT_ERSTINST 183 
#define  ACPI_DMT_EXTRA_TEXT 182 
#define  ACPI_DMT_FADTPM 181 
#define  ACPI_DMT_FLAG0 180 
#define  ACPI_DMT_FLAG1 179 
#define  ACPI_DMT_FLAG2 178 
#define  ACPI_DMT_FLAG3 177 
#define  ACPI_DMT_FLAG4 176 
#define  ACPI_DMT_FLAG5 175 
#define  ACPI_DMT_FLAG6 174 
#define  ACPI_DMT_FLAG7 173 
#define  ACPI_DMT_FLAGS0 172 
#define  ACPI_DMT_FLAGS1 171 
#define  ACPI_DMT_FLAGS16_16 170 
#define  ACPI_DMT_FLAGS2 169 
#define  ACPI_DMT_FLAGS4 168 
#define  ACPI_DMT_FLAGS4_0 167 
#define  ACPI_DMT_FLAGS4_12 166 
#define  ACPI_DMT_FLAGS4_4 165 
#define  ACPI_DMT_FLAGS4_8 164 
#define  ACPI_DMT_GAS 163 
#define  ACPI_DMT_GTDT 162 
#define  ACPI_DMT_HEST 161 
#define  ACPI_DMT_HESTNTFY 160 
#define  ACPI_DMT_HESTNTYP 159 
#define  ACPI_DMT_HMAT 158 
#define  ACPI_DMT_IORTMEM 157 
#define  ACPI_DMT_IVRS 156 
#define  ACPI_DMT_LABEL 155 
#define  ACPI_DMT_LPIT 154 
#define  ACPI_DMT_MADT 153 
#define  ACPI_DMT_NAME4 152 
#define  ACPI_DMT_NAME6 151 
#define  ACPI_DMT_NAME8 150 
#define  ACPI_DMT_NFIT 149 
#define  ACPI_DMT_PCCT 148 
#define  ACPI_DMT_PCI_PATH 147 
#define  ACPI_DMT_PMTT 146 
#define  ACPI_DMT_PPTT 145 
#define  ACPI_DMT_RAW_BUFFER 144 
#define  ACPI_DMT_SDEV 143 
#define  ACPI_DMT_SIG 142 
#define  ACPI_DMT_SPACEID 141 
#define  ACPI_DMT_SRAT 140 
#define  ACPI_DMT_STRING 139 
#define  ACPI_DMT_TPM2 138 
#define  ACPI_DMT_UINT16 137 
#define  ACPI_DMT_UINT24 136 
#define  ACPI_DMT_UINT32 135 
#define  ACPI_DMT_UINT40 134 
#define  ACPI_DMT_UINT48 133 
#define  ACPI_DMT_UINT56 132 
#define  ACPI_DMT_UINT64 131 
#define  ACPI_DMT_UINT8 130 
#define  ACPI_DMT_UNICODE 129 
#define  ACPI_DMT_UUID 128 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 char* AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  DtFatal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int DtGetBufferLength (char*) ; 
 char* DtGetFieldValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

UINT32
DtGetFieldLength (
    DT_FIELD                *Field,
    ACPI_DMTABLE_INFO       *Info)
{
    UINT32                  ByteLength = 0;
    char                    *Value;


    /* Length is based upon the opcode for this field in the info table */

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
    case ACPI_DMT_FLAGS0:
    case ACPI_DMT_FLAGS1:
    case ACPI_DMT_FLAGS2:
    case ACPI_DMT_FLAGS4:
    case ACPI_DMT_FLAGS4_0:
    case ACPI_DMT_FLAGS4_4:
    case ACPI_DMT_FLAGS4_8:
    case ACPI_DMT_FLAGS4_12:
    case ACPI_DMT_FLAGS16_16:
    case ACPI_DMT_LABEL:
    case ACPI_DMT_EXTRA_TEXT:

        ByteLength = 0;
        break;

    case ACPI_DMT_UINT8:
    case ACPI_DMT_CHKSUM:
    case ACPI_DMT_SPACEID:
    case ACPI_DMT_ACCWIDTH:
    case ACPI_DMT_IVRS:
    case ACPI_DMT_GTDT:
    case ACPI_DMT_MADT:
    case ACPI_DMT_PCCT:
    case ACPI_DMT_PMTT:
    case ACPI_DMT_PPTT:
    case ACPI_DMT_SDEV:
    case ACPI_DMT_SRAT:
    case ACPI_DMT_ASF:
    case ACPI_DMT_HESTNTYP:
    case ACPI_DMT_FADTPM:
    case ACPI_DMT_EINJACT:
    case ACPI_DMT_EINJINST:
    case ACPI_DMT_ERSTACT:
    case ACPI_DMT_ERSTINST:
    case ACPI_DMT_DMAR_SCOPE:

        ByteLength = 1;
        break;

    case ACPI_DMT_UINT16:
    case ACPI_DMT_DMAR:
    case ACPI_DMT_HEST:
    case ACPI_DMT_HMAT:
    case ACPI_DMT_NFIT:
    case ACPI_DMT_PCI_PATH:

        ByteLength = 2;
        break;

    case ACPI_DMT_UINT24:

        ByteLength = 3;
        break;

    case ACPI_DMT_UINT32:
    case ACPI_DMT_NAME4:
    case ACPI_DMT_SIG:
    case ACPI_DMT_LPIT:
    case ACPI_DMT_TPM2:

        ByteLength = 4;
        break;

    case ACPI_DMT_UINT40:

        ByteLength = 5;
        break;

    case ACPI_DMT_UINT48:
    case ACPI_DMT_NAME6:

        ByteLength = 6;
        break;

    case ACPI_DMT_UINT56:
    case ACPI_DMT_BUF7:

        ByteLength = 7;
        break;

    case ACPI_DMT_UINT64:
    case ACPI_DMT_NAME8:

        ByteLength = 8;
        break;

    case ACPI_DMT_STRING:

        Value = DtGetFieldValue (Field);
        if (Value)
        {
            ByteLength = strlen (Value) + 1;
        }
        else
        {   /* At this point, this is a fatal error */

            sprintf (AslGbl_MsgBuffer, "Expected \"%s\"", Info->Name);
            DtFatal (ASL_MSG_COMPILER_INTERNAL, NULL, AslGbl_MsgBuffer);
            return (0);
        }
        break;

    case ACPI_DMT_GAS:

        ByteLength = sizeof (ACPI_GENERIC_ADDRESS);
        break;

    case ACPI_DMT_HESTNTFY:

        ByteLength = sizeof (ACPI_HEST_NOTIFY);
        break;

    case ACPI_DMT_IORTMEM:

        ByteLength = sizeof (ACPI_IORT_MEMORY_ACCESS);
        break;

    case ACPI_DMT_BUFFER:
    case ACPI_DMT_RAW_BUFFER:

        Value = DtGetFieldValue (Field);
        if (Value)
        {
            ByteLength = DtGetBufferLength (Value);
        }
        else
        {   /* At this point, this is a fatal error */

            sprintf (AslGbl_MsgBuffer, "Expected \"%s\"", Info->Name);
            DtFatal (ASL_MSG_COMPILER_INTERNAL, NULL, AslGbl_MsgBuffer);
            return (0);
        }
        break;

    case ACPI_DMT_BUF10:

        ByteLength = 10;
        break;

    case ACPI_DMT_BUF12:

        ByteLength = 12;
        break;

    case ACPI_DMT_BUF16:
    case ACPI_DMT_UUID:

        ByteLength = 16;
        break;

    case ACPI_DMT_BUF128:

        ByteLength = 128;
        break;

    case ACPI_DMT_UNICODE:

        Value = DtGetFieldValue (Field);

        /* TBD: error if Value is NULL? (as below?) */

        ByteLength = (strlen (Value) + 1) * sizeof(UINT16);
        break;

    default:

        DtFatal (ASL_MSG_COMPILER_INTERNAL, Field, "Invalid table opcode");
        return (0);
    }

    return (ByteLength);
}