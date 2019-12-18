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
typedef  int UINT32 ;
struct TYPE_5__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_6__ {int AmlOpcode; int /*<<< orphan*/  DisasmOpcode; TYPE_1__ Value; } ;
struct TYPE_7__ {TYPE_2__ Common; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DASM_EISAID ; 
 int /*<<< orphan*/  ACPI_DASM_HID_STRING ; 
 int /*<<< orphan*/  ACPI_IS_ASCII (int) ; 
#define  AML_DWORD_OP 130 
#define  AML_STRING_OP 129 
#define  AML_WORD_OP 128 
 int AcpiUtDwordByteSwap (int) ; 
 int /*<<< orphan*/  isalpha (int) ; 

__attribute__((used)) static void
AcpiDmGetHardwareIdType (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  BigEndianId;
    UINT32                  Prefix[3];
    UINT32                  i;


    switch (Op->Common.AmlOpcode)
    {
    case AML_STRING_OP:

        /* Mark this string as an _HID/_CID string */

        Op->Common.DisasmOpcode = ACPI_DASM_HID_STRING;
        break;

    case AML_WORD_OP:
    case AML_DWORD_OP:

        /* Determine if a Word/Dword is a valid encoded EISAID */

        /* Swap from little-endian to big-endian to simplify conversion */

        BigEndianId = AcpiUtDwordByteSwap ((UINT32) Op->Common.Value.Integer);

        /* Create the 3 leading ASCII letters */

        Prefix[0] = ((BigEndianId >> 26) & 0x1F) + 0x40;
        Prefix[1] = ((BigEndianId >> 21) & 0x1F) + 0x40;
        Prefix[2] = ((BigEndianId >> 16) & 0x1F) + 0x40;

        /* Verify that all 3 are ascii and alpha */

        for (i = 0; i < 3; i++)
        {
            if (!ACPI_IS_ASCII (Prefix[i]) ||
                !isalpha (Prefix[i]))
            {
                return;
            }
        }

        /* Mark this node as convertible to an EISA ID string */

        Op->Common.DisasmOpcode = ACPI_DASM_EISAID;
        break;

    default:
        break;
    }
}