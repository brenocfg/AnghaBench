#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_16__ {TYPE_3__* Op; } ;
struct TYPE_15__ {int Flags; scalar_t__ Class; } ;
struct TYPE_12__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_13__ {scalar_t__ AmlOpcode; scalar_t__ ParseOpcode; TYPE_3__* Next; TYPE_3__* Child; TYPE_1__ Value; TYPE_5__* Node; TYPE_3__* Parent; int /*<<< orphan*/ * ExternalName; } ;
struct TYPE_14__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  TYPE_4__ ACPI_OPCODE_INFO ;
typedef  TYPE_5__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_GPIO ; 
 int /*<<< orphan*/  ACPI_ADR_SPACE_GSBUS ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AML_CLASS_EXECUTE ; 
 int AML_CREATE ; 
 scalar_t__ AML_DIVIDE_OP ; 
 int AML_HAS_RETVAL ; 
 int AML_HAS_TARGET ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_CONNECTION_INVALID ; 
 int /*<<< orphan*/  ASL_MSG_CONNECTION_MISSING ; 
 int /*<<< orphan*/  ASL_MSG_RESULT_NOT_USED ; 
 int /*<<< orphan*/  ASL_MSG_TIMEOUT ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 TYPE_4__* AcpiPsGetOpcodeInfo (scalar_t__) ; 
 int /*<<< orphan*/  AnAnalyzeStoreOperator (TYPE_3__*) ; 
 int /*<<< orphan*/  AnIsResultUsed (TYPE_3__*) ; 
 int /*<<< orphan*/  AnValidateCreateBufferField (TYPE_3__*) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AslGbl_DoTypechecking ; 
#define  PARSEOP_ACQUIRE 133 
#define  PARSEOP_CONNECTION 132 
#define  PARSEOP_FIELD 131 
 int PARSEOP_INTEGER ; 
#define  PARSEOP_LOADTABLE 130 
 int const PARSEOP_NAMESEG ; 
#define  PARSEOP_STORE 129 
#define  PARSEOP_WAIT 128 
 int PARSEOP_WORDCONST ; 
 scalar_t__ PARSEOP_ZERO ; 

ACPI_STATUS
AnOtherSemanticAnalysisWalkBegin (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_PARSE_OBJECT       *ArgOp;
    ACPI_PARSE_OBJECT       *PrevArgOp = NULL;
    const ACPI_OPCODE_INFO  *OpInfo;
    ACPI_NAMESPACE_NODE     *Node;


    OpInfo = AcpiPsGetOpcodeInfo (Op->Asl.AmlOpcode);


    if (OpInfo->Flags & AML_CREATE)
    {
        /* This group contains all of the Create Buffer Field operators */

        AnValidateCreateBufferField (Op);
        return (AE_OK);
    }

    /*
     * Determine if an execution class operator actually does something by
     * checking if it has a target and/or the function return value is used.
     * (Target is optional, so a standalone statement can actually do nothing.)
     */
    if ((OpInfo->Class == AML_CLASS_EXECUTE) &&
        (OpInfo->Flags & AML_HAS_RETVAL) &&
        (!AnIsResultUsed (Op)))
    {
        if (OpInfo->Flags & AML_HAS_TARGET)
        {
            /*
             * Find the target node, it is always the last child. If the target
             * is not specified in the ASL, a default node of type Zero was
             * created by the parser.
             */
            ArgOp = Op->Asl.Child;
            while (ArgOp->Asl.Next)
            {
                PrevArgOp = ArgOp;
                ArgOp = ArgOp->Asl.Next;
            }

            /* Divide() is the only weird case, it has two targets */

            if (Op->Asl.AmlOpcode == AML_DIVIDE_OP)
            {
                if ((ArgOp->Asl.ParseOpcode == PARSEOP_ZERO) &&
                    (PrevArgOp) &&
                    (PrevArgOp->Asl.ParseOpcode == PARSEOP_ZERO))
                {
                    AslError (ASL_ERROR, ASL_MSG_RESULT_NOT_USED,
                        Op, Op->Asl.ExternalName);
                }
            }

            else if (ArgOp->Asl.ParseOpcode == PARSEOP_ZERO)
            {
                AslError (ASL_ERROR, ASL_MSG_RESULT_NOT_USED,
                    Op, Op->Asl.ExternalName);
            }
        }
        else
        {
            /*
             * Has no target and the result is not used. Only a couple opcodes
             * can have this combination.
             */
            switch (Op->Asl.ParseOpcode)
            {
            case PARSEOP_ACQUIRE:
            case PARSEOP_WAIT:
            case PARSEOP_LOADTABLE:

                break;

            default:

                AslError (ASL_ERROR, ASL_MSG_RESULT_NOT_USED,
                    Op, Op->Asl.ExternalName);
                break;
            }
        }
    }

    /*
     * Semantic checks for individual ASL operators
     */

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_STORE:

        if (AslGbl_DoTypechecking)
        {
            AnAnalyzeStoreOperator (Op);
        }
        break;


    case PARSEOP_ACQUIRE:
    case PARSEOP_WAIT:
        /*
         * Emit a warning if the timeout parameter for these operators is not
         * ACPI_WAIT_FOREVER, and the result value from the operator is not
         * checked, meaning that a timeout could happen, but the code
         * would not know about it.
         */

        /* First child is the namepath, 2nd child is timeout */

        ArgOp = Op->Asl.Child;
        ArgOp = ArgOp->Asl.Next;

        /*
         * Check for the WAIT_FOREVER case - defined by the ACPI spec to be
         * 0xFFFF or greater
         */
        if (((ArgOp->Asl.ParseOpcode == PARSEOP_WORDCONST) ||
             (ArgOp->Asl.ParseOpcode == PARSEOP_INTEGER))  &&
             (ArgOp->Asl.Value.Integer >= (UINT64) ACPI_WAIT_FOREVER))
        {
            break;
        }

        /*
         * The operation could timeout. If the return value is not used
         * (indicates timeout occurred), issue a warning
         */
        if (!AnIsResultUsed (Op))
        {
            AslError (ASL_WARNING, ASL_MSG_TIMEOUT, ArgOp,
                Op->Asl.ExternalName);
        }
        break;

    case PARSEOP_CONNECTION:
        /*
         * Ensure that the referenced operation region has the correct SPACE_ID.
         * From the grammar/parser, we know the parent is a FIELD definition.
         */
        ArgOp = Op->Asl.Parent;     /* Field definition */
        ArgOp = ArgOp->Asl.Child;   /* First child is the OpRegion Name */
        Node = ArgOp->Asl.Node;     /* OpRegion namespace node */
        if (!Node)
        {
            break;
        }

        ArgOp = Node->Op;           /* OpRegion definition */
        ArgOp = ArgOp->Asl.Child;   /* First child is the OpRegion Name */
        ArgOp = ArgOp->Asl.Next;    /* Next peer is the SPACE_ID (what we want) */

        /*
         * The Connection() operator is only valid for the following operation
         * region SpaceIds: GeneralPurposeIo and GenericSerialBus.
         */
        if ((ArgOp->Asl.Value.Integer != ACPI_ADR_SPACE_GPIO) &&
            (ArgOp->Asl.Value.Integer != ACPI_ADR_SPACE_GSBUS))
        {
            AslError (ASL_ERROR, ASL_MSG_CONNECTION_INVALID, Op, NULL);
        }
        break;

    case PARSEOP_FIELD:
        /*
         * Ensure that fields for GeneralPurposeIo and GenericSerialBus
         * contain at least one Connection() operator
         */
        ArgOp = Op->Asl.Child;      /* 1st child is the OpRegion Name */
        Node = ArgOp->Asl.Node;     /* OpRegion namespace node */
        if (!Node)
        {
            break;
        }

        ArgOp = Node->Op;           /* OpRegion definition */
        ArgOp = ArgOp->Asl.Child;   /* First child is the OpRegion Name */
        ArgOp = ArgOp->Asl.Next;    /* Next peer is the SPACE_ID (what we want) */

        /* We are only interested in GeneralPurposeIo and GenericSerialBus */

        if ((ArgOp->Asl.Value.Integer != ACPI_ADR_SPACE_GPIO) &&
            (ArgOp->Asl.Value.Integer != ACPI_ADR_SPACE_GSBUS))
        {
            break;
        }

        ArgOp = Op->Asl.Child;      /* 1st child is the OpRegion Name */
        ArgOp = ArgOp->Asl.Next;    /* AccessType */
        ArgOp = ArgOp->Asl.Next;    /* LockRule */
        ArgOp = ArgOp->Asl.Next;    /* UpdateRule */
        ArgOp = ArgOp->Asl.Next;    /* Start of FieldUnitList */

        /* Walk the FieldUnitList */

        while (ArgOp)
        {
            if (ArgOp->Asl.ParseOpcode == PARSEOP_CONNECTION)
            {
                break;
            }
            else if (ArgOp->Asl.ParseOpcode == PARSEOP_NAMESEG)
            {
                AslError (ASL_ERROR, ASL_MSG_CONNECTION_MISSING, ArgOp, NULL);
                break;
            }

            ArgOp = ArgOp->Asl.Next;
        }
        break;

    default:

        break;
    }

    return (AE_OK);
}