#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_10__ {scalar_t__ Type; } ;
struct TYPE_7__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_8__ {int CompileFlags; int AmlOpcode; scalar_t__ FinalAmlLength; int /*<<< orphan*/  ParseOpName; TYPE_3__* Child; TYPE_1__ Value; TYPE_3__* Next; int /*<<< orphan*/  Extra; TYPE_4__* Node; } ;
struct TYPE_9__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  TYPE_4__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  ACPI_TO_INTEGER (void*) ; 
 scalar_t__ ACPI_TYPE_LOCAL_RESOURCE ; 
 int /*<<< orphan*/  AE_OK ; 
 int const AML_BUFFER_OP ; 
#define  AML_BYTE_OP 143 
#define  AML_DEVICE_OP 142 
#define  AML_DWORD_OP 141 
#define  AML_METHOD_OP 140 
#define  AML_NAME_OP 139 
#define  AML_ONES_OP 138 
#define  AML_ONE_OP 137 
#define  AML_PACKAGE_OP 136 
#define  AML_PROCESSOR_OP 135 
#define  AML_QWORD_OP 134 
#define  AML_REGION_OP 133 
#define  AML_SCOPE_OP 132 
#define  AML_THERMAL_ZONE_OP 131 
#define  AML_VARIABLE_PACKAGE_OP 130 
#define  AML_WORD_OP 129 
#define  AML_ZERO_OP 128 
 scalar_t__ AslGbl_CurrentAmlOffset ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  FlPrintFile (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsEmitOffsetTableEntry (scalar_t__,TYPE_4__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int OP_IS_RESOURCE_DATA ; 
 int OP_IS_RESOURCE_DESC ; 

ACPI_STATUS
LsAmlOffsetWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    UINT32                  FileId = (UINT32) ACPI_TO_INTEGER (Context);
    ACPI_NAMESPACE_NODE     *Node;
    UINT32                  Length;
    UINT32                  NamepathOffset;
    UINT32                  DataOffset;
    ACPI_PARSE_OBJECT       *NextOp;


    /* Ignore actual data blocks for resource descriptors */

    if (Op->Asl.CompileFlags & OP_IS_RESOURCE_DATA)
    {
        return (AE_OK); /* Do NOT update the global AML offset */
    }

    /* We are only interested in named objects (have a namespace node) */

    Node = Op->Asl.Node;
    if (!Node)
    {
        AslGbl_CurrentAmlOffset += Op->Asl.FinalAmlLength;
        return (AE_OK);
    }

    /* Named resource descriptor (has a descriptor tag) */

    if ((Node->Type == ACPI_TYPE_LOCAL_RESOURCE) &&
        (Op->Asl.CompileFlags & OP_IS_RESOURCE_DESC))
    {
        LsEmitOffsetTableEntry (FileId, Node, 0, AslGbl_CurrentAmlOffset,
            Op->Asl.ParseOpName, 0, Op->Asl.Extra, AML_BUFFER_OP);

        AslGbl_CurrentAmlOffset += Op->Asl.FinalAmlLength;
        return (AE_OK);
    }

    switch (Op->Asl.AmlOpcode)
    {
    case AML_NAME_OP:

        /* Named object -- Name (NameString, DataRefObject) */

        if (!Op->Asl.Child)
        {
            FlPrintFile (FileId, "%s NO CHILD!\n", AslGbl_MsgBuffer);
            return (AE_OK);
        }

        Length = Op->Asl.FinalAmlLength;

        /* Get to the NameSeg/NamePath Op (and length of the name) */

        Op = Op->Asl.Child;

        /* Get offset of last nameseg and the actual data */

        NamepathOffset = AslGbl_CurrentAmlOffset + Length +
            (Op->Asl.FinalAmlLength - ACPI_NAMESEG_SIZE);

        DataOffset = AslGbl_CurrentAmlOffset + Length +
            Op->Asl.FinalAmlLength;

        /* Get actual value associated with the name */

        Op = Op->Asl.Next;
        switch (Op->Asl.AmlOpcode)
        {
        case AML_BYTE_OP:
        case AML_WORD_OP:
        case AML_DWORD_OP:
        case AML_QWORD_OP:

            /* The +1 is to handle the integer size prefix (opcode) */

            LsEmitOffsetTableEntry (FileId, Node, NamepathOffset, (DataOffset + 1),
                Op->Asl.ParseOpName, Op->Asl.Value.Integer,
                (UINT8) Op->Asl.AmlOpcode, AML_NAME_OP);
            break;

        case AML_ONE_OP:
        case AML_ONES_OP:
        case AML_ZERO_OP:

            /* For these, offset will point to the opcode */

            LsEmitOffsetTableEntry (FileId, Node, NamepathOffset, DataOffset,
                Op->Asl.ParseOpName, Op->Asl.Value.Integer,
                (UINT8) Op->Asl.AmlOpcode, AML_NAME_OP);
            break;

        case AML_PACKAGE_OP:
        case AML_VARIABLE_PACKAGE_OP:

            /* Get the package element count */

            NextOp = Op->Asl.Child;

            LsEmitOffsetTableEntry (FileId, Node, NamepathOffset, DataOffset,
                Op->Asl.ParseOpName, NextOp->Asl.Value.Integer,
                (UINT8) Op->Asl.AmlOpcode, AML_NAME_OP);
            break;

         default:
             break;
        }

        AslGbl_CurrentAmlOffset += Length;
        return (AE_OK);

    case AML_REGION_OP:

        /* OperationRegion (NameString, RegionSpace, RegionOffset, RegionLength) */

        Length = Op->Asl.FinalAmlLength;

        /* Get the name/namepath node */

        NextOp = Op->Asl.Child;

        /* Get offset of last nameseg and the actual data */

        NamepathOffset = AslGbl_CurrentAmlOffset + Length +
            (NextOp->Asl.FinalAmlLength - ACPI_NAMESEG_SIZE);

        DataOffset = AslGbl_CurrentAmlOffset + Length +
            (NextOp->Asl.FinalAmlLength + 1);

        /* Get the SpaceId node, then the Offset (address) node */

        NextOp = NextOp->Asl.Next;
        NextOp = NextOp->Asl.Next;

        switch (NextOp->Asl.AmlOpcode)
        {
        /*
         * We are only interested in integer constants that can be changed
         * at boot time. Note, the One/Ones/Zero opcodes are considered
         * non-changeable, so we ignore them here.
         */
        case AML_BYTE_OP:
        case AML_WORD_OP:
        case AML_DWORD_OP:
        case AML_QWORD_OP:

            LsEmitOffsetTableEntry (FileId, Node, NamepathOffset, (DataOffset + 1),
                Op->Asl.ParseOpName, NextOp->Asl.Value.Integer,
                (UINT8) NextOp->Asl.AmlOpcode, AML_REGION_OP);

            AslGbl_CurrentAmlOffset += Length;
            return (AE_OK);

        default:
            break;
        }
        break;

    case AML_METHOD_OP:

        /* Method (Namepath, ...) */

        Length = Op->Asl.FinalAmlLength;

        /* Get the NameSeg/NamePath Op */

        NextOp = Op->Asl.Child;

        /* Get offset of last nameseg and the actual data (flags byte) */

        NamepathOffset = AslGbl_CurrentAmlOffset + Length +
            (NextOp->Asl.FinalAmlLength - ACPI_NAMESEG_SIZE);

        DataOffset = AslGbl_CurrentAmlOffset + Length +
            NextOp->Asl.FinalAmlLength;

        /* Get the flags byte Op */

        NextOp = NextOp->Asl.Next;

        LsEmitOffsetTableEntry (FileId, Node, NamepathOffset, DataOffset,
            Op->Asl.ParseOpName, NextOp->Asl.Value.Integer,
            (UINT8) Op->Asl.AmlOpcode, AML_METHOD_OP);
        break;

    case AML_PROCESSOR_OP:

        /* Processor (Namepath, ProcessorId, Address, Length) */

        Length = Op->Asl.FinalAmlLength;
        NextOp = Op->Asl.Child;     /* Get Namepath */

        /* Get offset of last nameseg and the actual data (PBlock address) */

        NamepathOffset = AslGbl_CurrentAmlOffset + Length +
            (NextOp->Asl.FinalAmlLength - ACPI_NAMESEG_SIZE);

        DataOffset = AslGbl_CurrentAmlOffset + Length +
            (NextOp->Asl.FinalAmlLength + 1);

        NextOp = NextOp->Asl.Next;  /* Get ProcessorID (BYTE) */
        NextOp = NextOp->Asl.Next;  /* Get Address (DWORD) */

        LsEmitOffsetTableEntry (FileId, Node, NamepathOffset, DataOffset,
            Op->Asl.ParseOpName, NextOp->Asl.Value.Integer,
            (UINT8) AML_DWORD_OP, AML_PROCESSOR_OP);
        break;

    case AML_DEVICE_OP:
    case AML_SCOPE_OP:
    case AML_THERMAL_ZONE_OP:

        /* Device/Scope/ThermalZone (Namepath) */

        Length = Op->Asl.FinalAmlLength;
        NextOp = Op->Asl.Child;     /* Get Namepath */

        /* Get offset of last nameseg */

        NamepathOffset = AslGbl_CurrentAmlOffset + Length +
            (NextOp->Asl.FinalAmlLength - ACPI_NAMESEG_SIZE);

        LsEmitOffsetTableEntry (FileId, Node, NamepathOffset, 0,
            Op->Asl.ParseOpName, 0, (UINT8) 0, Op->Asl.AmlOpcode);
        break;

    default:
        break;
    }

    AslGbl_CurrentAmlOffset += Op->Asl.FinalAmlLength;
    return (AE_OK);
}