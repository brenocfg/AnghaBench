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
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_3__ {int Flags; int Opcode; } ;
typedef  TYPE_1__ ACPI_DMTABLE_INFO ;

/* Variables and functions */
#define  ACPI_DMT_BUF10 164 
#define  ACPI_DMT_BUF12 163 
#define  ACPI_DMT_BUF128 162 
#define  ACPI_DMT_BUF16 161 
#define  ACPI_DMT_BUF7 160 
#define  ACPI_DMT_BUFFER 159 
#define  ACPI_DMT_DEVICE_PATH 158 
#define  ACPI_DMT_FLAG0 157 
#define  ACPI_DMT_FLAG1 156 
#define  ACPI_DMT_FLAG2 155 
#define  ACPI_DMT_FLAG3 154 
#define  ACPI_DMT_FLAG4 153 
#define  ACPI_DMT_FLAG5 152 
#define  ACPI_DMT_FLAG6 151 
#define  ACPI_DMT_FLAG7 150 
#define  ACPI_DMT_FLAGS0 149 
#define  ACPI_DMT_FLAGS1 148 
#define  ACPI_DMT_FLAGS16_16 147 
#define  ACPI_DMT_FLAGS2 146 
#define  ACPI_DMT_FLAGS4 145 
#define  ACPI_DMT_FLAGS4_0 144 
#define  ACPI_DMT_FLAGS4_12 143 
#define  ACPI_DMT_FLAGS4_4 142 
#define  ACPI_DMT_FLAGS4_8 141 
#define  ACPI_DMT_GAS 140 
#define  ACPI_DMT_HESTNTFY 139 
#define  ACPI_DMT_IORTMEM 138 
#define  ACPI_DMT_LABEL 137 
#define  ACPI_DMT_NAME4 136 
#define  ACPI_DMT_NAME6 135 
#define  ACPI_DMT_NAME8 134 
#define  ACPI_DMT_PCI_PATH 133 
#define  ACPI_DMT_RAW_BUFFER 132 
#define  ACPI_DMT_SIG 131 
#define  ACPI_DMT_STRING 130 
#define  ACPI_DMT_UNICODE 129 
#define  ACPI_DMT_UUID 128 
 int /*<<< orphan*/  DT_FIELD_TYPE_BUFFER ; 
 int /*<<< orphan*/  DT_FIELD_TYPE_DEVICE_PATH ; 
 int /*<<< orphan*/  DT_FIELD_TYPE_FLAG ; 
 int /*<<< orphan*/  DT_FIELD_TYPE_FLAGS_INTEGER ; 
 int /*<<< orphan*/  DT_FIELD_TYPE_INLINE_SUBTABLE ; 
 int /*<<< orphan*/  DT_FIELD_TYPE_INTEGER ; 
 int /*<<< orphan*/  DT_FIELD_TYPE_LABEL ; 
 int /*<<< orphan*/  DT_FIELD_TYPE_STRING ; 
 int /*<<< orphan*/  DT_FIELD_TYPE_UNICODE ; 
 int /*<<< orphan*/  DT_FIELD_TYPE_UUID ; 
 int DT_FLAG ; 

UINT8
DtGetFieldType (
    ACPI_DMTABLE_INFO       *Info)
{
    UINT8                   Type;


    /* DT_FLAG means that this is the start of a block of flag bits */
    /* TBD - we can make these a separate opcode later */

    if (Info->Flags & DT_FLAG)
    {
        return (DT_FIELD_TYPE_FLAGS_INTEGER);
    }

    /* Type is based upon the opcode for this field in the info table */

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

        Type = DT_FIELD_TYPE_FLAG;
        break;

    case ACPI_DMT_NAME4:
    case ACPI_DMT_SIG:
    case ACPI_DMT_NAME6:
    case ACPI_DMT_NAME8:
    case ACPI_DMT_STRING:

        Type = DT_FIELD_TYPE_STRING;
        break;

    case ACPI_DMT_BUFFER:
    case ACPI_DMT_RAW_BUFFER:
    case ACPI_DMT_BUF7:
    case ACPI_DMT_BUF10:
    case ACPI_DMT_BUF12:
    case ACPI_DMT_BUF16:
    case ACPI_DMT_BUF128:
    case ACPI_DMT_PCI_PATH:

        Type = DT_FIELD_TYPE_BUFFER;
        break;

    case ACPI_DMT_GAS:
    case ACPI_DMT_HESTNTFY:
    case ACPI_DMT_IORTMEM:

        Type = DT_FIELD_TYPE_INLINE_SUBTABLE;
        break;

    case ACPI_DMT_UNICODE:

        Type = DT_FIELD_TYPE_UNICODE;
        break;

    case ACPI_DMT_UUID:

        Type = DT_FIELD_TYPE_UUID;
        break;

    case ACPI_DMT_DEVICE_PATH:

        Type = DT_FIELD_TYPE_DEVICE_PATH;
        break;

    case ACPI_DMT_LABEL:

        Type = DT_FIELD_TYPE_LABEL;
        break;

    default:

        Type = DT_FIELD_TYPE_INTEGER;
        break;
    }

    return (Type);
}