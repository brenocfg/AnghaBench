#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  void* UINT32 ;
struct TYPE_31__ {int /*<<< orphan*/ * PkgEnd; int /*<<< orphan*/ * Aml; } ;
struct TYPE_26__ {void* Length; int /*<<< orphan*/ * Data; } ;
struct TYPE_25__ {int AmlOpcode; TYPE_2__* Parent; int /*<<< orphan*/  AmlOpName; } ;
struct TYPE_30__ {TYPE_4__ Named; TYPE_3__ Common; } ;
struct TYPE_29__ {TYPE_9__ ParserState; TYPE_6__* ControlState; int /*<<< orphan*/  ArgCount; int /*<<< orphan*/  PassNumber; int /*<<< orphan*/  ArgTypes; int /*<<< orphan*/ * Aml; } ;
struct TYPE_27__ {int /*<<< orphan*/ * PackageEnd; } ;
struct TYPE_28__ {TYPE_5__ Control; } ;
struct TYPE_23__ {int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_24__ {TYPE_1__ Common; } ;
typedef  TYPE_7__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_8__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS2 ; 
 int /*<<< orphan*/  ACPI_POSSIBLE_METHOD_CALL ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_BUFFER_OP 138 
#define  AML_BYTE_OP 137 
#define  AML_DWORD_OP 136 
#define  AML_INT_NAMEPATH_OP 135 
#define  AML_METHOD_OP 134 
 int /*<<< orphan*/  AML_NAME_OP ; 
#define  AML_PACKAGE_OP 133 
#define  AML_QWORD_OP 132 
#define  AML_STRING_OP 131 
#define  AML_VARIABLE_PACKAGE_OP 130 
#define  AML_WHILE_OP 129 
#define  AML_WORD_OP 128 
 int /*<<< orphan*/  ASL_CV_CAPTURE_COMMENTS (TYPE_7__*) ; 
 int /*<<< orphan*/  AcpiPsAppendArg (TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiPsGetNextArg (TYPE_7__*,TYPE_9__*,int /*<<< orphan*/ ,TYPE_8__**) ; 
 int /*<<< orphan*/  AcpiPsGetNextNamepath (TYPE_7__*,TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiPsGetNextSimpleArg (TYPE_9__*,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  GET_CURRENT_ARG_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INCREMENT_ARG_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PsGetArguments ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiPsGetArguments (
    ACPI_WALK_STATE         *WalkState,
    UINT8                   *AmlOpStart,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_PARSE_OBJECT       *Arg = NULL;


    ACPI_FUNCTION_TRACE_PTR (PsGetArguments, WalkState);


    ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
        "Get arguments for opcode [%s]\n", Op->Common.AmlOpName));

    switch (Op->Common.AmlOpcode)
    {
    case AML_BYTE_OP:       /* AML_BYTEDATA_ARG */
    case AML_WORD_OP:       /* AML_WORDDATA_ARG */
    case AML_DWORD_OP:      /* AML_DWORDATA_ARG */
    case AML_QWORD_OP:      /* AML_QWORDATA_ARG */
    case AML_STRING_OP:     /* AML_ASCIICHARLIST_ARG */

        /* Fill in constant or string argument directly */

        AcpiPsGetNextSimpleArg (&(WalkState->ParserState),
            GET_CURRENT_ARG_TYPE (WalkState->ArgTypes), Op);
        break;

    case AML_INT_NAMEPATH_OP:   /* AML_NAMESTRING_ARG */

        Status = AcpiPsGetNextNamepath (WalkState,
            &(WalkState->ParserState), Op, ACPI_POSSIBLE_METHOD_CALL);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        WalkState->ArgTypes = 0;
        break;

    default:
        /*
         * Op is not a constant or string, append each argument to the Op
         */
        while (GET_CURRENT_ARG_TYPE (WalkState->ArgTypes) &&
            !WalkState->ArgCount)
        {
            WalkState->Aml = WalkState->ParserState.Aml;

            switch (Op->Common.AmlOpcode)
            {
            case AML_METHOD_OP:
            case AML_BUFFER_OP:
            case AML_PACKAGE_OP:
            case AML_VARIABLE_PACKAGE_OP:
            case AML_WHILE_OP:

                break;

            default:

                ASL_CV_CAPTURE_COMMENTS (WalkState);
                break;
            }

            Status = AcpiPsGetNextArg (WalkState, &(WalkState->ParserState),
                GET_CURRENT_ARG_TYPE (WalkState->ArgTypes), &Arg);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }

            if (Arg)
            {
                AcpiPsAppendArg (Op, Arg);
            }

            INCREMENT_ARG_LIST (WalkState->ArgTypes);
        }

        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
            "Final argument count: %8.8X pass %u\n",
            WalkState->ArgCount, WalkState->PassNumber));

        /* Special processing for certain opcodes */

        switch (Op->Common.AmlOpcode)
        {
        case AML_METHOD_OP:
            /*
             * Skip parsing of control method because we don't have enough
             * info in the first pass to parse it correctly.
             *
             * Save the length and address of the body
             */
            Op->Named.Data = WalkState->ParserState.Aml;
            Op->Named.Length = (UINT32)
                (WalkState->ParserState.PkgEnd - WalkState->ParserState.Aml);

            /* Skip body of method */

            WalkState->ParserState.Aml = WalkState->ParserState.PkgEnd;
            WalkState->ArgCount = 0;
            break;

        case AML_BUFFER_OP:
        case AML_PACKAGE_OP:
        case AML_VARIABLE_PACKAGE_OP:

            if ((Op->Common.Parent) &&
                (Op->Common.Parent->Common.AmlOpcode == AML_NAME_OP) &&
                (WalkState->PassNumber <= ACPI_IMODE_LOAD_PASS2))
            {
                ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
                    "Setup Package/Buffer: Pass %u, AML Ptr: %p\n",
                    WalkState->PassNumber, AmlOpStart));

                /*
                 * Skip parsing of Buffers and Packages because we don't have
                 * enough info in the first pass to parse them correctly.
                 */
                Op->Named.Data = AmlOpStart;
                Op->Named.Length = (UINT32)
                    (WalkState->ParserState.PkgEnd - AmlOpStart);

                /* Skip body */

                WalkState->ParserState.Aml = WalkState->ParserState.PkgEnd;
                WalkState->ArgCount = 0;
            }
            break;

        case AML_WHILE_OP:

            if (WalkState->ControlState)
            {
                WalkState->ControlState->Control.PackageEnd =
                    WalkState->ParserState.PkgEnd;
            }
            break;

        default:

            /* No action for all other opcodes */

            break;
        }

        break;
    }

    return_ACPI_STATUS (AE_OK);
}