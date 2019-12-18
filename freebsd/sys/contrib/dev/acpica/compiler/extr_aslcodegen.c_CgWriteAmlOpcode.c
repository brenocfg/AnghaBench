#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT32 ;
typedef  int UINT16 ;
struct TYPE_7__ {int Integer; int* String; } ;
struct TYPE_8__ {scalar_t__ ParseOpcode; int AmlOpcode; int AmlPkgLenBytes; int CompileFlags; int AmlLength; TYPE_1__ Value; int /*<<< orphan*/  AmlSubtreeLength; } ;
struct TYPE_9__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
#define  AML_BYTE_OP 137 
#define  AML_DWORD_OP 136 
 int AML_FIELD_ACCESS_OP ; 
 int AML_FIELD_CONNECTION_OP ; 
 int AML_FIELD_OFFSET_OP ; 
#define  AML_INT_ACCESSFIELD_OP 135 
#define  AML_INT_CONNECTION_OP 134 
#define  AML_INT_RESERVEDFIELD_OP 133 
#define  AML_PACKAGE_LENGTH 132 
#define  AML_QWORD_OP 131 
#define  AML_STRING_OP 130 
#define  AML_UNASSIGNED_OPCODE 129 
#define  AML_WORD_OP 128 
 int /*<<< orphan*/  ASL_FILE_STDERR ; 
 scalar_t__ AcpiGbl_CaptureComments ; 
 int /*<<< orphan*/  CgLocalWriteAmlData (TYPE_3__*,int*,int) ; 
 int /*<<< orphan*/  CgWriteAmlComment (TYPE_3__*) ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*) ; 
 int OP_AML_PACKAGE ; 
 scalar_t__ PARSEOP_DEFAULT_ARG ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
CgWriteAmlOpcode (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT8                   PkgLenFirstByte;
    UINT32                  i;
    union {
        UINT16                  Opcode;
        UINT8                   OpcodeBytes[2];
    } Aml;
    union {
        UINT32                  Len;
        UINT8                   LenBytes[4];
    } PkgLen;


    /* We expect some DEFAULT_ARGs, just ignore them */

    if (Op->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG)
    {
        return;
    }

    /*
     * Before printing the bytecode, generate comment byte codes
     * associated with this node.
     */
    if (AcpiGbl_CaptureComments)
    {
        CgWriteAmlComment(Op);
    }

    switch (Op->Asl.AmlOpcode)
    {
    case AML_UNASSIGNED_OPCODE:

        /* These opcodes should not get here */

        printf ("Found a node with an unassigned AML opcode\n");
        FlPrintFile (ASL_FILE_STDERR,
            "Found a node with an unassigned AML opcode\n");
        return;

    case AML_INT_RESERVEDFIELD_OP:

        /* Special opcodes for within a field definition */

        Aml.Opcode = AML_FIELD_OFFSET_OP;
        break;

    case AML_INT_ACCESSFIELD_OP:

        Aml.Opcode = AML_FIELD_ACCESS_OP;
        break;

    case AML_INT_CONNECTION_OP:

        Aml.Opcode = AML_FIELD_CONNECTION_OP;
        break;

    default:

        Aml.Opcode = Op->Asl.AmlOpcode;
        break;
    }


    switch (Aml.Opcode)
    {
    case AML_PACKAGE_LENGTH:

        /* Value is the length to be encoded (Used in field definitions) */

        PkgLen.Len = (UINT32) Op->Asl.Value.Integer;
        break;

    default:

        /* Check for two-byte opcode */

        if (Aml.Opcode > 0x00FF)
        {
            /* Write the high byte first */

            CgLocalWriteAmlData (Op, &Aml.OpcodeBytes[1], 1);
        }

        CgLocalWriteAmlData (Op, &Aml.OpcodeBytes[0], 1);

        /* Subtreelength doesn't include length of package length bytes */

        PkgLen.Len = Op->Asl.AmlSubtreeLength + Op->Asl.AmlPkgLenBytes;
        break;
    }

    /* Does this opcode have an associated "PackageLength" field? */

    if (Op->Asl.CompileFlags & OP_AML_PACKAGE)
    {
        if (Op->Asl.AmlPkgLenBytes == 1)
        {
            /* Simplest case -- no bytes to follow, just write the count */

            CgLocalWriteAmlData (Op, &PkgLen.LenBytes[0], 1);
        }
        else if (Op->Asl.AmlPkgLenBytes != 0)
        {
            /*
             * Encode the "bytes to follow" in the first byte, top two bits.
             * The low-order nybble of the length is in the bottom 4 bits
             */
            PkgLenFirstByte = (UINT8)
                (((UINT32) (Op->Asl.AmlPkgLenBytes - 1) << 6) |
                (PkgLen.LenBytes[0] & 0x0F));

            CgLocalWriteAmlData (Op, &PkgLenFirstByte, 1);

            /*
             * Shift the length over by the 4 bits we just stuffed
             * in the first byte
             */
            PkgLen.Len >>= 4;

            /*
             * Now we can write the remaining bytes -
             * either 1, 2, or 3 bytes
             */
            for (i = 0; i < (UINT32) (Op->Asl.AmlPkgLenBytes - 1); i++)
            {
                CgLocalWriteAmlData (Op, &PkgLen.LenBytes[i], 1);
            }
        }
    }

    switch (Aml.Opcode)
    {
    case AML_BYTE_OP:

        CgLocalWriteAmlData (Op, &Op->Asl.Value.Integer, 1);
        break;

    case AML_WORD_OP:

        CgLocalWriteAmlData (Op, &Op->Asl.Value.Integer, 2);
       break;

    case AML_DWORD_OP:

        CgLocalWriteAmlData (Op, &Op->Asl.Value.Integer, 4);
        break;

    case AML_QWORD_OP:

        CgLocalWriteAmlData (Op, &Op->Asl.Value.Integer, 8);
        break;

    case AML_STRING_OP:

        CgLocalWriteAmlData (Op, Op->Asl.Value.String, Op->Asl.AmlLength);
        break;

    default:

        /* All data opcodes must appear above */

        break;
    }
}