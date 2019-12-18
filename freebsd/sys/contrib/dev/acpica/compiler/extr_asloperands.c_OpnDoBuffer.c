#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_10__ {scalar_t__ Integer; int /*<<< orphan*/  String; } ;
struct TYPE_11__ {scalar_t__ ParseOpcode; int AmlLength; TYPE_1__ Value; int /*<<< orphan*/  AmlOpcode; TYPE_3__* Next; TYPE_3__* Child; } ;
struct TYPE_12__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_DWORD_OP ; 
 int /*<<< orphan*/  AML_RAW_DATA_BUFFER ; 
 int /*<<< orphan*/  AML_RAW_DATA_BYTE ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 TYPE_3__* ASL_GET_PEER_NODE (TYPE_3__*) ; 
 int /*<<< orphan*/  ASL_MSG_BUFFER_LENGTH ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_OPERAND ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  OpcSetOptimalIntegerSize (TYPE_3__*) ; 
#define  PARSEOP_BYTECONST 134 
#define  PARSEOP_DEFAULT_ARG 133 
#define  PARSEOP_DWORDCONST 132 
#define  PARSEOP_INTEGER 131 
#define  PARSEOP_RAW_DATA 130 
#define  PARSEOP_STRING_LITERAL 129 
#define  PARSEOP_WORDCONST 128 
 char* UtGetOpName (int) ; 
 int /*<<< orphan*/  UtSetParseOpName (TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
OpnDoBuffer (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *InitializerOp;
    ACPI_PARSE_OBJECT       *BufferLengthOp;

    /* Optional arguments for this opcode with defaults */

    UINT32                  BufferLength = 0;


    /* Opcode and package length first */
    /* Buffer Length is next, followed by the initializer list */

    BufferLengthOp = Op->Asl.Child;
    InitializerOp = BufferLengthOp->Asl.Next;

    /*
     * If the BufferLength is not an INTEGER or was not specified in the ASL
     * (DEFAULT_ARG), it is a TermArg that is
     * evaluated at run-time, and we are therefore finished.
     */
    if ((BufferLengthOp->Asl.ParseOpcode != PARSEOP_INTEGER) &&
        (BufferLengthOp->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG))
    {
        return;
    }

    /*
     * We want to count the number of items in the initializer list, because if
     * it is larger than the buffer length, we will define the buffer size
     * to be the size of the initializer list (as per the ACPI Specification)
     */
    switch (InitializerOp->Asl.ParseOpcode)
    {
    case PARSEOP_INTEGER:
    case PARSEOP_BYTECONST:
    case PARSEOP_WORDCONST:
    case PARSEOP_DWORDCONST:

        /* The peer list contains the byte list (if any...) */

        while (InitializerOp)
        {
            /* For buffers, this is a list of raw bytes */

            InitializerOp->Asl.AmlOpcode = AML_RAW_DATA_BYTE;
            InitializerOp->Asl.AmlLength = 1;
            InitializerOp->Asl.ParseOpcode = PARSEOP_RAW_DATA;

            BufferLength++;
            InitializerOp = ASL_GET_PEER_NODE (InitializerOp);
        }
        break;

    case PARSEOP_STRING_LITERAL:

        /*
         * Only one initializer, the string. Buffer must be big enough to hold
         * the string plus the null termination byte
         */
        BufferLength = strlen (InitializerOp->Asl.Value.String) + 1;

        InitializerOp->Asl.AmlOpcode = AML_RAW_DATA_BUFFER;
        InitializerOp->Asl.AmlLength = BufferLength;
        InitializerOp->Asl.ParseOpcode = PARSEOP_RAW_DATA;
        break;

    case PARSEOP_RAW_DATA:

        /* Buffer nodes are already initialized (e.g. Unicode operator) */
        return;

    case PARSEOP_DEFAULT_ARG:
        break;

    default:

        AslError (ASL_ERROR, ASL_MSG_INVALID_OPERAND, InitializerOp,
            "Unknown buffer initializer opcode");
        printf ("Unknown buffer initializer opcode [%s]\n",
            UtGetOpName (InitializerOp->Asl.ParseOpcode));
        return;
    }

    /* Check if initializer list is longer than the buffer length */

    if (BufferLengthOp->Asl.Value.Integer > BufferLength)
    {
        BufferLength = (UINT32) BufferLengthOp->Asl.Value.Integer;
    }

    if (!BufferLength)
    {
        /* No length AND no items -- issue notice */

        AslError (ASL_REMARK, ASL_MSG_BUFFER_LENGTH, BufferLengthOp, NULL);

        /* But go ahead and put the buffer length of zero into the AML */
    }

    /*
     * Just set the buffer size node to be the buffer length, regardless
     * of whether it was previously an integer or a default_arg placeholder
     */
    BufferLengthOp->Asl.ParseOpcode = PARSEOP_INTEGER;
    BufferLengthOp->Asl.AmlOpcode = AML_DWORD_OP;
    BufferLengthOp->Asl.Value.Integer = BufferLength;

    (void) OpcSetOptimalIntegerSize (BufferLengthOp);
    UtSetParseOpName (BufferLengthOp);

    /* Remaining nodes are handled via the tree walk */
}