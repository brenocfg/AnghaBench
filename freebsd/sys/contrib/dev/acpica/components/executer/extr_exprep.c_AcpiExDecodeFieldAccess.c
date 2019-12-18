#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT32 ;
struct TYPE_6__ {scalar_t__ Type; } ;
struct TYPE_5__ {int /*<<< orphan*/  BitLength; int /*<<< orphan*/  StartFieldBitOffset; } ;
struct TYPE_7__ {TYPE_2__ Common; TYPE_1__ CommonField; } ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER_FIELD ; 
 int /*<<< orphan*/  AE_INFO ; 
#define  AML_FIELD_ACCESS_ANY 133 
#define  AML_FIELD_ACCESS_BUFFER 132 
#define  AML_FIELD_ACCESS_BYTE 131 
#define  AML_FIELD_ACCESS_DWORD 130 
#define  AML_FIELD_ACCESS_QWORD 129 
 int AML_FIELD_ACCESS_TYPE_MASK ; 
#define  AML_FIELD_ACCESS_WORD 128 
 int AcpiExGenerateAccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExDecodeFieldAccess ; 
 int /*<<< orphan*/  return_UINT32 (int) ; 

__attribute__((used)) static UINT32
AcpiExDecodeFieldAccess (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT8                   FieldFlags,
    UINT32                  *ReturnByteAlignment)
{
    UINT32                  Access;
    UINT32                  ByteAlignment;
    UINT32                  BitLength;


    ACPI_FUNCTION_TRACE (ExDecodeFieldAccess);


    Access = (FieldFlags & AML_FIELD_ACCESS_TYPE_MASK);

    switch (Access)
    {
    case AML_FIELD_ACCESS_ANY:

#ifdef ACPI_UNDER_DEVELOPMENT
        ByteAlignment =
            AcpiExGenerateAccess (ObjDesc->CommonField.StartFieldBitOffset,
                ObjDesc->CommonField.BitLength,
                0xFFFFFFFF /* Temp until we pass RegionLength as parameter */);
        BitLength = ByteAlignment * 8;
#endif

        ByteAlignment = 1;
        BitLength = 8;
        break;

    case AML_FIELD_ACCESS_BYTE:
    case AML_FIELD_ACCESS_BUFFER:   /* ACPI 2.0 (SMBus Buffer) */

        ByteAlignment = 1;
        BitLength     = 8;
        break;

    case AML_FIELD_ACCESS_WORD:

        ByteAlignment = 2;
        BitLength     = 16;
        break;

    case AML_FIELD_ACCESS_DWORD:

        ByteAlignment = 4;
        BitLength     = 32;
        break;

    case AML_FIELD_ACCESS_QWORD:    /* ACPI 2.0 */

        ByteAlignment = 8;
        BitLength     = 64;
        break;

    default:

        /* Invalid field access type */

        ACPI_ERROR ((AE_INFO,
            "Unknown field access type 0x%X",
            Access));

        return_UINT32 (0);
    }

    if (ObjDesc->Common.Type == ACPI_TYPE_BUFFER_FIELD)
    {
        /*
         * BufferField access can be on any byte boundary, so the
         * ByteAlignment is always 1 byte -- regardless of any ByteAlignment
         * implied by the field access type.
         */
        ByteAlignment = 1;
    }

    *ReturnByteAlignment = ByteAlignment;
    return_UINT32 (BitLength);
}