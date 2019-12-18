#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_9__ {int /*<<< orphan*/  Value; } ;
typedef  TYPE_1__ DT_FIELD ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
#define  DT_FIELD_TYPE_BUFFER 133 
#define  DT_FIELD_TYPE_DEVICE_PATH 132 
#define  DT_FIELD_TYPE_INTEGER 131 
#define  DT_FIELD_TYPE_STRING 130 
#define  DT_FIELD_TYPE_UNICODE 129 
#define  DT_FIELD_TYPE_UUID 128 
 int /*<<< orphan*/  DtCompileBuffer (int*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtCompileInteger (int*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DtCompileString (int*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtCompileUnicode (int*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtCompileUuid (int*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DtFatal (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 

void
DtCompileOneField (
    UINT8                   *Buffer,
    DT_FIELD                *Field,
    UINT32                  ByteLength,
    UINT8                   Type,
    UINT8                   Flags)
{
    ACPI_STATUS             Status;


    switch (Type)
    {
    case DT_FIELD_TYPE_INTEGER:

        DtCompileInteger (Buffer, Field, ByteLength, Flags);
        break;

    case DT_FIELD_TYPE_STRING:

        DtCompileString (Buffer, Field, ByteLength);
        break;

    case DT_FIELD_TYPE_UUID:

        Status = DtCompileUuid (Buffer, Field, ByteLength);
        if (ACPI_SUCCESS (Status))
        {
            break;
        }

        /* Fall through. */

    case DT_FIELD_TYPE_BUFFER:

        DtCompileBuffer (Buffer, Field->Value, Field, ByteLength);
        break;

    case DT_FIELD_TYPE_UNICODE:

        DtCompileUnicode (Buffer, Field, ByteLength);
        break;

    case DT_FIELD_TYPE_DEVICE_PATH:

        break;

    default:

        DtFatal (ASL_MSG_COMPILER_INTERNAL, Field, "Invalid field type");
        break;
    }
}