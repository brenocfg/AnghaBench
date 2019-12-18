#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
typedef  int UINT32 ;
struct TYPE_8__ {int Integer; scalar_t__ String; } ;
struct TYPE_9__ {int /*<<< orphan*/  ParseOpcode; int /*<<< orphan*/  CompileFlags; TYPE_1__ Value; } ;
struct TYPE_10__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_EISAID ; 
 int AcpiUtAsciiCharToHex (char) ; 
 int AcpiUtDwordByteSwap (int) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  OP_COMPILE_TIME_CONST ; 
 int /*<<< orphan*/  OpcSetOptimalIntegerSize (TYPE_3__*) ; 
 int /*<<< orphan*/  PARSEOP_INTEGER ; 
 int /*<<< orphan*/  UtSetParseOpName (TYPE_3__*) ; 
 int /*<<< orphan*/  isupper (int) ; 
 int /*<<< orphan*/  isxdigit (int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
OpcDoEisaId (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  EisaId = 0;
    UINT32                  BigEndianId;
    char                    *InString;
    ACPI_STATUS             Status = AE_OK;
    UINT32                  i;


    InString = (char *) Op->Asl.Value.String;

    /*
     * The EISAID string must be exactly 7 characters and of the form
     * "UUUXXXX" -- 3 uppercase letters and 4 hex digits (e.g., "PNP0001")
     */
    if (strlen (InString) != 7)
    {
        Status = AE_BAD_PARAMETER;
    }
    else
    {
        /* Check all 7 characters for correct format */

        for (i = 0; i < 7; i++)
        {
            /* First 3 characters must be uppercase letters */

            if (i < 3)
            {
                if (!isupper ((int) InString[i]))
                {
                    Status = AE_BAD_PARAMETER;
                }
            }

            /* Last 4 characters must be hex digits */

            else if (!isxdigit ((int) InString[i]))
            {
                Status = AE_BAD_PARAMETER;
            }
        }
    }

    if (ACPI_FAILURE (Status))
    {
        AslError (ASL_ERROR, ASL_MSG_INVALID_EISAID, Op, Op->Asl.Value.String);
    }
    else
    {
        /* Create ID big-endian first (bits are contiguous) */

        BigEndianId =
            (UINT32) ((UINT8) (InString[0] - 0x40)) << 26 |
            (UINT32) ((UINT8) (InString[1] - 0x40)) << 21 |
            (UINT32) ((UINT8) (InString[2] - 0x40)) << 16 |

            (AcpiUtAsciiCharToHex (InString[3])) << 12 |
            (AcpiUtAsciiCharToHex (InString[4])) << 8  |
            (AcpiUtAsciiCharToHex (InString[5])) << 4  |
             AcpiUtAsciiCharToHex (InString[6]);

        /* Swap to little-endian to get final ID (see function header) */

        EisaId = AcpiUtDwordByteSwap (BigEndianId);
    }

    /*
     * Morph the Op into an integer, regardless of whether there
     * was an error in the EISAID string
     */
    Op->Asl.Value.Integer = EisaId;

    Op->Asl.CompileFlags &= ~OP_COMPILE_TIME_CONST;
    Op->Asl.ParseOpcode = PARSEOP_INTEGER;
    (void) OpcSetOptimalIntegerSize (Op);

    /* Op is now an integer */

    UtSetParseOpName (Op);
}