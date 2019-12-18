#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_20__ {scalar_t__ Class; scalar_t__ RuntimeArgs; int Flags; char* Name; } ;
struct TYPE_18__ {int AmlOpcode; TYPE_5__* Next; int /*<<< orphan*/  ParseOpcode; TYPE_3__* Node; TYPE_2__* Parent; TYPE_5__* Child; } ;
struct TYPE_19__ {TYPE_4__ Asl; } ;
struct TYPE_17__ {int /*<<< orphan*/  Type; } ;
struct TYPE_15__ {scalar_t__ AmlOpcode; } ;
struct TYPE_16__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;
typedef  TYPE_6__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_RESOURCE ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_RESOURCE_FIELD ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
#define  AML_BANK_FIELD_OP 176 
#define  AML_BUFFER_OP 175 
#define  AML_CLASS_CONTROL 174 
#define  AML_CLASS_CREATE 173 
#define  AML_CLASS_EXECUTE 172 
 scalar_t__ AML_CLASS_NAMED_OBJECT ; 
#define  AML_CLASS_RETURN_VALUE 171 
#define  AML_DATA_REGION_OP 170 
 int AML_DEBUG_OP ; 
#define  AML_DEFAULT_ARG_OP 169 
#define  AML_EXTERNAL_OP 168 
#define  AML_IF_OP 167 
 int AML_NSNODE ; 
#define  AML_PACKAGE_LENGTH 166 
#define  AML_PACKAGE_OP 165 
#define  AML_RAW_DATA_BUFFER 164 
#define  AML_RAW_DATA_BYTE 163 
#define  AML_RAW_DATA_CHAIN 162 
#define  AML_RAW_DATA_DWORD 161 
#define  AML_RAW_DATA_QWORD 160 
#define  AML_RAW_DATA_WORD 159 
#define  AML_REGION_OP 158 
#define  AML_RETURN_OP 157 
 int AML_SCOPE_OP ; 
#define  AML_STORE_OP 156 
#define  AML_UNASSIGNED_OPCODE 155 
#define  AML_VARIABLE_PACKAGE_OP 154 
#define  AML_WHILE_OP 153 
#define  ARGI_DEVICE_REF 152 
#define  ARGI_INTEGER 151 
#define  ARGI_INTEGER_REF 150 
 scalar_t__ ARGI_INVALID_OPCODE ; 
#define  ARGI_OBJECT_REF 149 
#define  ARGI_REFERENCE 148 
#define  ARGI_STORE_TARGET 147 
#define  ARGI_TARGETREF 146 
 scalar_t__ ARG_TYPE_WIDTH ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_TYPE ; 
 int /*<<< orphan*/  ASL_MSG_NAMED_OBJECT_IN_WHILE ; 
 int /*<<< orphan*/  ASL_MSG_RESOURCE_FIELD ; 
 TYPE_6__* AcpiPsGetOpcodeInfo (int) ; 
 int /*<<< orphan*/  AnCheckMethodReturnValue (TYPE_5__*,TYPE_6__ const*,TYPE_5__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  AnFormatBtype (char*,scalar_t__) ; 
 scalar_t__ AnGetBtype (TYPE_5__*) ; 
 int /*<<< orphan*/  AnIsInternalMethod (TYPE_5__*) ; 
 scalar_t__ AnMapArgTypeToBtype (scalar_t__) ; 
 int /*<<< orphan*/  AslAbort () ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,char*) ; 
 char* AslGbl_MsgBuffer ; 
 char* AslGbl_StringBuffer ; 
 char* AslGbl_StringBuffer2 ; 
 scalar_t__ GET_CURRENT_ARG_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  INCREMENT_ARG_LIST (scalar_t__) ; 
#define  PARSEOP_ARG0 145 
#define  PARSEOP_ARG1 144 
#define  PARSEOP_ARG2 143 
#define  PARSEOP_ARG3 142 
#define  PARSEOP_ARG4 141 
#define  PARSEOP_ARG5 140 
#define  PARSEOP_ARG6 139 
#define  PARSEOP_DEBUG 138 
#define  PARSEOP_INDEX 137 
 int /*<<< orphan*/  PARSEOP_INTEGER ; 
#define  PARSEOP_LOCAL0 136 
#define  PARSEOP_LOCAL1 135 
#define  PARSEOP_LOCAL2 134 
#define  PARSEOP_LOCAL3 133 
#define  PARSEOP_LOCAL4 132 
#define  PARSEOP_LOCAL5 131 
#define  PARSEOP_LOCAL6 130 
#define  PARSEOP_LOCAL7 129 
 int /*<<< orphan*/  PARSEOP_METHODCALL ; 
 int /*<<< orphan*/  PARSEOP_RAW_DATA ; 
#define  PARSEOP_REFOF 128 
 int /*<<< orphan*/  PARSEOP_ZERO ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 

ACPI_STATUS
AnOperandTypecheckWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    const ACPI_OPCODE_INFO  *OpInfo;
    UINT32                  RuntimeArgTypes;
    UINT32                  RuntimeArgTypes2;
    UINT32                  RequiredBtypes;
    UINT32                  ThisNodeBtype;
    UINT32                  CommonBtypes;
    UINT32                  OpcodeClass;
    ACPI_PARSE_OBJECT       *ArgOp;
    UINT32                  ArgType;


    switch (Op->Asl.AmlOpcode)
    {
    case AML_RAW_DATA_BYTE:
    case AML_RAW_DATA_WORD:
    case AML_RAW_DATA_DWORD:
    case AML_RAW_DATA_QWORD:
    case AML_RAW_DATA_BUFFER:
    case AML_RAW_DATA_CHAIN:
    case AML_PACKAGE_LENGTH:
    case AML_UNASSIGNED_OPCODE:
    case AML_DEFAULT_ARG_OP:

        /* Ignore the internal (compiler-only) AML opcodes */

        return (AE_OK);

    default:

        break;
    }

    OpInfo = AcpiPsGetOpcodeInfo (Op->Asl.AmlOpcode);
    if (!OpInfo)
    {
        return (AE_OK);
    }

    ArgOp = Op->Asl.Child;
    OpcodeClass = OpInfo->Class;
    RuntimeArgTypes = OpInfo->RuntimeArgs;

#ifdef ASL_ERROR_NAMED_OBJECT_IN_WHILE
    /*
     * Update 11/2008: In practice, we can't perform this check. A simple
     * analysis is not sufficient. Also, it can cause errors when compiling
     * disassembled code because of the way Switch operators are implemented
     * (a While(One) loop with a named temp variable created within.)
     */

    /*
     * If we are creating a named object, check if we are within a while loop
     * by checking if the parent is a WHILE op. This is a simple analysis, but
     * probably sufficient for many cases.
     *
     * Allow Scope(), Buffer(), and Package().
     */
    if (((OpcodeClass == AML_CLASS_NAMED_OBJECT) && (Op->Asl.AmlOpcode != AML_SCOPE_OP)) ||
        ((OpcodeClass == AML_CLASS_CREATE) && (OpInfo->Flags & AML_NSNODE)))
    {
        if (Op->Asl.Parent->Asl.AmlOpcode == AML_WHILE_OP)
        {
            AslError (ASL_ERROR, ASL_MSG_NAMED_OBJECT_IN_WHILE, Op, NULL);
        }
    }
#endif

    /*
     * Special case for control opcodes IF/RETURN/WHILE since they
     * have no runtime arg list (at this time)
     */
    switch (Op->Asl.AmlOpcode)
    {
    case AML_IF_OP:
    case AML_WHILE_OP:
    case AML_RETURN_OP:

        if (ArgOp->Asl.ParseOpcode == PARSEOP_METHODCALL)
        {
            /* Check for an internal method */

            if (AnIsInternalMethod (ArgOp))
            {
                return (AE_OK);
            }

            /* The lone arg is a method call, check it */

            RequiredBtypes = AnMapArgTypeToBtype (ARGI_INTEGER);
            if (Op->Asl.AmlOpcode == AML_RETURN_OP)
            {
                RequiredBtypes = 0xFFFFFFFF;
            }

            ThisNodeBtype = AnGetBtype (ArgOp);
            if (ThisNodeBtype == ACPI_UINT32_MAX)
            {
                return (AE_OK);
            }

            AnCheckMethodReturnValue (Op, OpInfo, ArgOp,
                RequiredBtypes, ThisNodeBtype);
        }
        return (AE_OK);

    case AML_EXTERNAL_OP:
        /*
         * Not really a "runtime" opcode since it used by disassembler only.
         * The parser will find any issues with the operands.
         */
        return (AE_OK);

    default:

        break;
    }

    /* Ignore the non-executable opcodes */

    if (RuntimeArgTypes == ARGI_INVALID_OPCODE)
    {
        return (AE_OK);
    }

    /*
     * Special handling for certain opcodes.
     */
    switch (Op->Asl.AmlOpcode)
    {
        /* BankField has one TermArg */

    case AML_BANK_FIELD_OP:

        OpcodeClass = AML_CLASS_EXECUTE;
        ArgOp = ArgOp->Asl.Next;
        ArgOp = ArgOp->Asl.Next;
        break;

        /* Operation Region has 2 TermArgs */

    case AML_REGION_OP:

        OpcodeClass = AML_CLASS_EXECUTE;
        ArgOp = ArgOp->Asl.Next;
        ArgOp = ArgOp->Asl.Next;
        break;

        /* DataTableRegion has 3 TermArgs */

    case AML_DATA_REGION_OP:

        OpcodeClass = AML_CLASS_EXECUTE;
        ArgOp = ArgOp->Asl.Next;
        break;

        /* Buffers/Packages have a length that is a TermArg */

    case AML_BUFFER_OP:
    case AML_PACKAGE_OP:
    case AML_VARIABLE_PACKAGE_OP:

            /* If length is a constant, we are done */

        if ((ArgOp->Asl.ParseOpcode == PARSEOP_INTEGER) ||
            (ArgOp->Asl.ParseOpcode == PARSEOP_RAW_DATA))
        {
            return (AE_OK);
        }
        break;

        /* Store can write any object to the Debug object */

    case AML_STORE_OP:
        /*
         * If this is a Store() to the Debug object, we don't need
         * to perform any further validation -- because a Store of
         * any object to Debug is permitted and supported.
         */
        if (ArgOp->Asl.Next->Asl.AmlOpcode == AML_DEBUG_OP)
        {
            return (AE_OK);
        }
        break;

    default:
        break;
    }

    switch (OpcodeClass)
    {
    case AML_CLASS_EXECUTE:
    case AML_CLASS_CREATE:
    case AML_CLASS_CONTROL:
    case AML_CLASS_RETURN_VALUE:

        /* Reverse the runtime argument list */

        RuntimeArgTypes2 = 0;
        while ((ArgType = GET_CURRENT_ARG_TYPE (RuntimeArgTypes)))
        {
            RuntimeArgTypes2 <<= ARG_TYPE_WIDTH;
            RuntimeArgTypes2 |= ArgType;
            INCREMENT_ARG_LIST (RuntimeArgTypes);
        }

        /* Typecheck each argument */

        while ((ArgType = GET_CURRENT_ARG_TYPE (RuntimeArgTypes2)))
        {
            /* Get the required type(s) for the argument */

            RequiredBtypes = AnMapArgTypeToBtype (ArgType);

            if (!ArgOp)
            {
                AslError (ASL_ERROR, ASL_MSG_COMPILER_INTERNAL, Op,
                    "Null ArgOp in argument loop");
                AslAbort ();
            }

            /* Get the actual type of the argument */

            ThisNodeBtype = AnGetBtype (ArgOp);
            if (ThisNodeBtype == ACPI_UINT32_MAX)
            {
                goto NextArgument;
            }

            /* Examine the arg based on the required type of the arg */

            switch (ArgType)
            {
            case ARGI_TARGETREF:

                if (ArgOp->Asl.ParseOpcode == PARSEOP_ZERO)
                {
                    /* ZERO is the placeholder for "don't store result" */

                    ThisNodeBtype = RequiredBtypes;
                    break;
                }

            /* Fallthrough */

            case ARGI_STORE_TARGET:

                if (ArgOp->Asl.ParseOpcode == PARSEOP_INTEGER)
                {
                    /*
                     * This is the case where an original reference to a resource
                     * descriptor field has been replaced by an (Integer) offset.
                     * These named fields are supported at compile-time only;
                     * the names are not passed to the interpreter (via the AML).
                     */
                    if ((ArgOp->Asl.Node->Type == ACPI_TYPE_LOCAL_RESOURCE_FIELD) ||
                        (ArgOp->Asl.Node->Type == ACPI_TYPE_LOCAL_RESOURCE))
                    {
                        AslError (ASL_ERROR, ASL_MSG_RESOURCE_FIELD,
                            ArgOp, NULL);
                    }
                    else
                    {
                        AslError (ASL_ERROR, ASL_MSG_INVALID_TYPE,
                            ArgOp, NULL);
                    }
                }
                break;


#ifdef __FUTURE_IMPLEMENTATION
/*
 * Possible future typechecking support
 */
            case ARGI_REFERENCE:            /* References */
            case ARGI_INTEGER_REF:
            case ARGI_OBJECT_REF:
            case ARGI_DEVICE_REF:

                switch (ArgOp->Asl.ParseOpcode)
                {
                case PARSEOP_LOCAL0:
                case PARSEOP_LOCAL1:
                case PARSEOP_LOCAL2:
                case PARSEOP_LOCAL3:
                case PARSEOP_LOCAL4:
                case PARSEOP_LOCAL5:
                case PARSEOP_LOCAL6:
                case PARSEOP_LOCAL7:

                    /* TBD: implement analysis of current value (type) of the local */
                    /* For now, just treat any local as a typematch */

                    /*ThisNodeBtype = RequiredBtypes;*/
                    break;

                case PARSEOP_ARG0:
                case PARSEOP_ARG1:
                case PARSEOP_ARG2:
                case PARSEOP_ARG3:
                case PARSEOP_ARG4:
                case PARSEOP_ARG5:
                case PARSEOP_ARG6:

                    /* Hard to analyze argument types, so we won't */
                    /* for now. Just treat any arg as a typematch */

                    /* ThisNodeBtype = RequiredBtypes; */
                    break;

                case PARSEOP_DEBUG:
                case PARSEOP_REFOF:
                case PARSEOP_INDEX:
                default:

                    break;
                }
                break;
#endif
            case ARGI_INTEGER:
            default:

                break;
            }


            /* Check for a type mismatch (required versus actual) */

            CommonBtypes = ThisNodeBtype & RequiredBtypes;

            if (ArgOp->Asl.ParseOpcode == PARSEOP_METHODCALL)
            {
                if (AnIsInternalMethod (ArgOp))
                {
                    return (AE_OK);
                }

                /* Check a method call for a valid return value */

                AnCheckMethodReturnValue (Op, OpInfo, ArgOp,
                    RequiredBtypes, ThisNodeBtype);
            }

            /*
             * Now check if the actual type(s) match at least one
             * bit to the required type
             */
            else if (!CommonBtypes)
            {
                /* No match -- this is a type mismatch error */

                AnFormatBtype (AslGbl_StringBuffer, ThisNodeBtype);
                AnFormatBtype (AslGbl_StringBuffer2, RequiredBtypes);

                sprintf (AslGbl_MsgBuffer, "[%s] found, %s operator requires [%s]",
                    AslGbl_StringBuffer, OpInfo->Name, AslGbl_StringBuffer2);

                AslError (ASL_ERROR, ASL_MSG_INVALID_TYPE,
                    ArgOp, AslGbl_MsgBuffer);
            }

        NextArgument:
            ArgOp = ArgOp->Asl.Next;
            INCREMENT_ARG_LIST (RuntimeArgTypes2);
        }
        break;

    default:

        break;
    }

    return (AE_OK);
}