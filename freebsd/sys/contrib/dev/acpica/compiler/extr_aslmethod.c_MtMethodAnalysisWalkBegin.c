#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  size_t UINT32 ;
struct TYPE_21__ {int Integer; int /*<<< orphan*/  String; } ;
struct TYPE_22__ {int ParseOpcode; char* NameSeg; char* ExternalName; int AmlOpcode; int CompileFlags; TYPE_5__* Next; TYPE_5__* Child; TYPE_1__ Value; TYPE_5__* Parent; int /*<<< orphan*/  Node; } ;
struct TYPE_25__ {TYPE_2__ Asl; } ;
struct TYPE_24__ {TYPE_3__* MethodStack; } ;
struct TYPE_23__ {int NumArguments; int ShouldBeSerialized; int /*<<< orphan*/  NumReturnNoValue; int /*<<< orphan*/  NumReturnWithValue; void** ArgInitialized; void** LocalInitialized; TYPE_5__* Op; int /*<<< orphan*/  CreatesNamedObjects; int /*<<< orphan*/ * ValidArgTypes; int /*<<< orphan*/  ValidReturnTypes; struct TYPE_23__* Next; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_3__ ASL_METHOD_INFO ;
typedef  TYPE_4__ ASL_ANALYSIS_WALK_INFO ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,char*) ; 
 int ACPI_UINT8_MAX ; 
 size_t ACPI_VALID_RESERVED_NAME_MAX ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_ARG_INIT ; 
 int /*<<< orphan*/  ASL_MSG_FOUND_HERE ; 
 int /*<<< orphan*/  ASL_MSG_ILLEGAL_RECURSION ; 
 int /*<<< orphan*/  ASL_MSG_INVALID_TIME ; 
 int /*<<< orphan*/  ASL_MSG_LOCAL_INIT ; 
 int /*<<< orphan*/  ASL_MSG_LOCAL_OUTSIDE_METHOD ; 
 int /*<<< orphan*/  ASL_MSG_MISSING_DEPENDENCY ; 
 int /*<<< orphan*/  ASL_MSG_MULTIPLE_TYPES ; 
 int /*<<< orphan*/  ASL_MSG_NOT_PARAMETER ; 
 int /*<<< orphan*/  ASL_MSG_NO_WHILE ; 
 int /*<<< orphan*/  ASL_MSG_RECURSION ; 
 int /*<<< orphan*/  ASL_MSG_RESERVED_USE ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 int /*<<< orphan*/  ASL_TYPE_CID ; 
 int /*<<< orphan*/  ASL_TYPE_HID ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int /*<<< orphan*/  AnCheckId (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AnMapObjTypeToBtype (TYPE_5__*) ; 
 size_t ApCheckForPredefinedName (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  ApCheckForPredefinedObject (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  ApFindNameInDeviceTree (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ApFindNameInScope (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  AslDualParseOpError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,char*) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,char*) ; 
 scalar_t__ AslGbl_CrossReferenceOutput ; 
 char* AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  AslGbl_TotalMethods ; 
 int /*<<< orphan*/  METHOD_NAME__ADR ; 
 int /*<<< orphan*/  METHOD_NAME__CID ; 
 int /*<<< orphan*/  METHOD_NAME__HID ; 
 int /*<<< orphan*/  METHOD_NAME__PS0 ; 
 int /*<<< orphan*/  METHOD_NAME__PS1 ; 
 int /*<<< orphan*/  METHOD_NAME__PS2 ; 
 int /*<<< orphan*/  METHOD_NAME__PS3 ; 
 int /*<<< orphan*/  MtCheckNamedObjectInMethod (TYPE_5__*,TYPE_3__*) ; 
 int OP_IS_NULL_RETURN ; 
 int OP_IS_TARGET ; 
 int /*<<< orphan*/  OtXrefWalkPart1 (TYPE_5__*,size_t,TYPE_3__*) ; 
#define  PARSEOP_ARG0 156 
#define  PARSEOP_ARG1 155 
#define  PARSEOP_ARG2 154 
#define  PARSEOP_ARG3 153 
#define  PARSEOP_ARG4 152 
#define  PARSEOP_ARG5 151 
#define  PARSEOP_ARG6 150 
#define  PARSEOP_BREAK 149 
#define  PARSEOP_CONTINUE 148 
 void* PARSEOP_DEFAULT_ARG ; 
#define  PARSEOP_DEVICE 147 
#define  PARSEOP_EVENT 146 
 void* PARSEOP_INTEGER ; 
#define  PARSEOP_LOCAL0 145 
#define  PARSEOP_LOCAL1 144 
#define  PARSEOP_LOCAL2 143 
#define  PARSEOP_LOCAL3 142 
#define  PARSEOP_LOCAL4 141 
#define  PARSEOP_LOCAL5 140 
#define  PARSEOP_LOCAL6 139 
#define  PARSEOP_LOCAL7 138 
#define  PARSEOP_METHOD 137 
#define  PARSEOP_METHODCALL 136 
#define  PARSEOP_MUTEX 135 
#define  PARSEOP_NAME 134 
 void* PARSEOP_OBJECTTYPE ; 
#define  PARSEOP_OPERATIONREGION 133 
 void* PARSEOP_PACKAGE ; 
#define  PARSEOP_POWERRESOURCE 132 
#define  PARSEOP_PROCESSOR 131 
#define  PARSEOP_RETURN 130 
#define  PARSEOP_STALL 129 
#define  PARSEOP_THERMALZONE 128 
 void* PARSEOP_VAR_PACKAGE ; 
 void* PARSEOP_WHILE ; 
 void* TRUE ; 
 TYPE_3__* UtLocalCalloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

ACPI_STATUS
MtMethodAnalysisWalkBegin (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ASL_ANALYSIS_WALK_INFO  *WalkInfo = (ASL_ANALYSIS_WALK_INFO *) Context;
    ASL_METHOD_INFO         *MethodInfo = WalkInfo->MethodStack;
    ACPI_PARSE_OBJECT       *Next;
    UINT32                  RegisterNumber;
    UINT32                  i;
    char                    LocalName[] = "Local0";
    char                    ArgName[] = "Arg0";
    ACPI_PARSE_OBJECT       *ArgNode;
    ACPI_PARSE_OBJECT       *NextType;
    ACPI_PARSE_OBJECT       *NextParamType;
    UINT8                   ActualArgs = 0;
    BOOLEAN                 HidExists;
    BOOLEAN                 AdrExists;


    /* Build cross-reference output file if requested */

    if (AslGbl_CrossReferenceOutput)
    {
        OtXrefWalkPart1 (Op, Level, MethodInfo);
    }

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_METHOD:

        AslGbl_TotalMethods++;

        /* Create and init method info */

        MethodInfo = UtLocalCalloc (sizeof (ASL_METHOD_INFO));
        MethodInfo->Next = WalkInfo->MethodStack;
        MethodInfo->Op = Op;

        WalkInfo->MethodStack = MethodInfo;

        /*
         * Special handling for _PSx methods. Dependency rules (same scope):
         *
         * 1) _PS0 - One of these must exist: _PS1, _PS2, _PS3
         * 2) _PS1/_PS2/_PS3: A _PS0 must exist
         */
        if (ACPI_COMPARE_NAMESEG (METHOD_NAME__PS0, Op->Asl.NameSeg))
        {
            /* For _PS0, one of _PS1/_PS2/_PS3 must exist */

            if ((!ApFindNameInScope (METHOD_NAME__PS1, Op)) &&
                (!ApFindNameInScope (METHOD_NAME__PS2, Op)) &&
                (!ApFindNameInScope (METHOD_NAME__PS3, Op)))
            {
                AslError (ASL_WARNING, ASL_MSG_MISSING_DEPENDENCY, Op,
                    "_PS0 requires one of _PS1/_PS2/_PS3 in same scope");
            }
        }
        else if (
            ACPI_COMPARE_NAMESEG (METHOD_NAME__PS1, Op->Asl.NameSeg) ||
            ACPI_COMPARE_NAMESEG (METHOD_NAME__PS2, Op->Asl.NameSeg) ||
            ACPI_COMPARE_NAMESEG (METHOD_NAME__PS3, Op->Asl.NameSeg))
        {
            /* For _PS1/_PS2/_PS3, a _PS0 must exist */

            if (!ApFindNameInScope (METHOD_NAME__PS0, Op))
            {
                sprintf (AslGbl_MsgBuffer,
                    "%4.4s requires _PS0 in same scope", Op->Asl.NameSeg);

                AslError (ASL_WARNING, ASL_MSG_MISSING_DEPENDENCY, Op,
                    AslGbl_MsgBuffer);
            }
        }

        /* Get the name node */

        Next = Op->Asl.Child;

        /* Get the NumArguments node */

        Next = Next->Asl.Next;
        MethodInfo->NumArguments = (UINT8)
            (((UINT8) Next->Asl.Value.Integer) & 0x07);

        /* Get the SerializeRule and SyncLevel nodes, ignored here */

        Next = Next->Asl.Next;
        MethodInfo->ShouldBeSerialized = (UINT8) Next->Asl.Value.Integer;

        Next = Next->Asl.Next;
        ArgNode = Next;

        /* Get the ReturnType node */

        Next = Next->Asl.Next;

        NextType = Next->Asl.Child;
        while (NextType)
        {
            /* Get and map each of the ReturnTypes */

            MethodInfo->ValidReturnTypes |= AnMapObjTypeToBtype (NextType);
            NextType->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
            NextType = NextType->Asl.Next;
        }

        /* Get the ParameterType node */

        Next = Next->Asl.Next;

        NextType = Next->Asl.Child;
        while (NextType)
        {
            if (NextType->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG)
            {
                NextParamType = NextType->Asl.Child;
                while (NextParamType)
                {
                    MethodInfo->ValidArgTypes[ActualArgs] |=
                        AnMapObjTypeToBtype (NextParamType);

                    NextParamType->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
                    NextParamType = NextParamType->Asl.Next;
                }
            }
            else
            {
                MethodInfo->ValidArgTypes[ActualArgs] =
                    AnMapObjTypeToBtype (NextType);

                NextType->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
                ActualArgs++;
            }

            NextType = NextType->Asl.Next;
        }

        if ((MethodInfo->NumArguments) &&
            (MethodInfo->NumArguments != ActualArgs))
        {
            /* error: Param list did not match number of args */
        }

        /* Allow numarguments == 0 for Function() */

        if ((!MethodInfo->NumArguments) && (ActualArgs))
        {
            MethodInfo->NumArguments = ActualArgs;
            ArgNode->Asl.Value.Integer |= ActualArgs;
        }

        /*
         * Actual arguments are initialized at method entry.
         * All other ArgX "registers" can be used as locals, so we
         * track their initialization.
         */
        for (i = 0; i < MethodInfo->NumArguments; i++)
        {
            MethodInfo->ArgInitialized[i] = TRUE;
        }
        break;

    case PARSEOP_METHODCALL:

        /* Check for a recursive method call */

        if (MethodInfo &&
           (Op->Asl.Node == MethodInfo->Op->Asl.Node))
        {
            if (MethodInfo->CreatesNamedObjects)
            {
                /*
                 * This is an error, as it will fail at runtime on all ACPI
                 * implementations. Any named object declarations will be
                 * executed twice, causing failure the second time. Note,
                 * this is independent of whether the method is declared
                 * Serialized, because the same thread is attempting to
                 * reenter the method, and this will always succeed.
                 */
                AslDualParseOpError (ASL_ERROR, ASL_MSG_ILLEGAL_RECURSION, Op,
                    Op->Asl.Value.String, ASL_MSG_FOUND_HERE, MethodInfo->Op,
                    MethodInfo->Op->Asl.ExternalName);
            }
            else
            {
                /* Method does not create objects, issue a remark */

                AslError (ASL_REMARK, ASL_MSG_RECURSION, Op, Op->Asl.ExternalName);
            }
        }
        break;

    case PARSEOP_LOCAL0:
    case PARSEOP_LOCAL1:
    case PARSEOP_LOCAL2:
    case PARSEOP_LOCAL3:
    case PARSEOP_LOCAL4:
    case PARSEOP_LOCAL5:
    case PARSEOP_LOCAL6:
    case PARSEOP_LOCAL7:

        if (!MethodInfo)
        {
            /*
             * Local was used outside a control method, or there was an error
             * in the method declaration.
             */
            AslError (ASL_REMARK, ASL_MSG_LOCAL_OUTSIDE_METHOD,
                Op, Op->Asl.ExternalName);
            return (AE_ERROR);
        }

        RegisterNumber = (Op->Asl.AmlOpcode & 0x0007);

        /*
         * If the local is being used as a target, mark the local
         * initialized
         */
        if (Op->Asl.CompileFlags & OP_IS_TARGET)
        {
            MethodInfo->LocalInitialized[RegisterNumber] = TRUE;
        }

        /*
         * Otherwise, this is a reference, check if the local
         * has been previously initialized.
         *
         * The only operator that accepts an uninitialized value is ObjectType()
         */
        else if ((!MethodInfo->LocalInitialized[RegisterNumber]) &&
                 (Op->Asl.Parent->Asl.ParseOpcode != PARSEOP_OBJECTTYPE))
        {
            LocalName[strlen (LocalName) -1] = (char) (RegisterNumber + 0x30);
            AslError (ASL_ERROR, ASL_MSG_LOCAL_INIT, Op, LocalName);
        }
        break;

    case PARSEOP_ARG0:
    case PARSEOP_ARG1:
    case PARSEOP_ARG2:
    case PARSEOP_ARG3:
    case PARSEOP_ARG4:
    case PARSEOP_ARG5:
    case PARSEOP_ARG6:

        if (!MethodInfo)
        {
            /*
             * Arg was used outside a control method, or there was an error
             * in the method declaration.
             */
            AslError (ASL_REMARK, ASL_MSG_LOCAL_OUTSIDE_METHOD,
                Op, Op->Asl.ExternalName);
            return (AE_ERROR);
        }

        RegisterNumber = (Op->Asl.AmlOpcode & 0x000F) - 8;
        ArgName[strlen (ArgName) -1] = (char) (RegisterNumber + 0x30);

        /*
         * If the Arg is being used as a target, mark the local
         * initialized
         */
        if (Op->Asl.CompileFlags & OP_IS_TARGET)
        {
            MethodInfo->ArgInitialized[RegisterNumber] = TRUE;
        }

        /*
         * Otherwise, this is a reference, check if the Arg
         * has been previously initialized.
         *
         * The only operator that accepts an uninitialized value is ObjectType()
         */
        else if ((!MethodInfo->ArgInitialized[RegisterNumber]) &&
            (Op->Asl.Parent->Asl.ParseOpcode != PARSEOP_OBJECTTYPE))
        {
            AslError (ASL_ERROR, ASL_MSG_ARG_INIT, Op, ArgName);
        }

        /* Flag this arg if it is not a "real" argument to the method */

        if (RegisterNumber >= MethodInfo->NumArguments)
        {
            AslError (ASL_REMARK, ASL_MSG_NOT_PARAMETER, Op, ArgName);
        }
        break;

    case PARSEOP_RETURN:

        if (!MethodInfo)
        {
            /*
             * Probably was an error in the method declaration,
             * no additional error here
             */
            ACPI_WARNING ((AE_INFO, "%p, No parent method", Op));
            return (AE_ERROR);
        }

        /*
         * A child indicates a possible return value. A simple Return or
         * Return() is marked with OP_IS_NULL_RETURN by the parser so
         * that it is not counted as a "real" return-with-value, although
         * the AML code that is actually emitted is Return(0). The AML
         * definition of Return has a required parameter, so we are
         * forced to convert a null return to Return(0).
         */
        if ((Op->Asl.Child) &&
            (Op->Asl.Child->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG) &&
            (!(Op->Asl.Child->Asl.CompileFlags & OP_IS_NULL_RETURN)))
        {
            MethodInfo->NumReturnWithValue++;
        }
        else
        {
            MethodInfo->NumReturnNoValue++;
        }
        break;

    case PARSEOP_BREAK:
    case PARSEOP_CONTINUE:

        Next = Op->Asl.Parent;
        while (Next)
        {
            if (Next->Asl.ParseOpcode == PARSEOP_WHILE)
            {
                break;
            }
            Next = Next->Asl.Parent;
        }

        if (!Next)
        {
            AslError (ASL_ERROR, ASL_MSG_NO_WHILE, Op, NULL);
        }
        break;

    case PARSEOP_STALL:

        /* We can range check if the argument is an integer */

        if ((Op->Asl.Child->Asl.ParseOpcode == PARSEOP_INTEGER) &&
            (Op->Asl.Child->Asl.Value.Integer > ACPI_UINT8_MAX))
        {
            AslError (ASL_ERROR, ASL_MSG_INVALID_TIME, Op, NULL);
        }
        break;

    case PARSEOP_DEVICE:

        /* Check usage of _HID and _ADR objects */

        HidExists = ApFindNameInDeviceTree (METHOD_NAME__HID, Op);
        AdrExists = ApFindNameInDeviceTree (METHOD_NAME__ADR, Op);

        if (!HidExists && !AdrExists)
        {
            AslError (ASL_WARNING, ASL_MSG_MISSING_DEPENDENCY, Op,
                "Device object requires a _HID or _ADR in same scope");
        }
        else if (HidExists && AdrExists)
        {
            /*
             * According to the ACPI spec, "A device object must contain
             * either an _HID object or an _ADR object, but should not contain
             * both".
             */
            AslError (ASL_WARNING, ASL_MSG_MULTIPLE_TYPES, Op,
                "Device object requires either a _HID or _ADR, but not both");
        }
        break;

    case PARSEOP_EVENT:
    case PARSEOP_MUTEX:
    case PARSEOP_OPERATIONREGION:
    case PARSEOP_POWERRESOURCE:
    case PARSEOP_PROCESSOR:
    case PARSEOP_THERMALZONE:

        /*
         * The first operand is a name to be created in the namespace.
         * Check against the reserved list.
         */
        i = ApCheckForPredefinedName (Op, Op->Asl.NameSeg);
        if (i < ACPI_VALID_RESERVED_NAME_MAX)
        {
            AslError (ASL_ERROR, ASL_MSG_RESERVED_USE,
                Op, Op->Asl.ExternalName);
        }
        break;

    case PARSEOP_NAME:

        /* Typecheck any predefined names statically defined with Name() */

        ApCheckForPredefinedObject (Op, Op->Asl.NameSeg);

        /* Special typechecking for _HID */

        if (!strcmp (METHOD_NAME__HID, Op->Asl.NameSeg))
        {
            Next = Op->Asl.Child->Asl.Next;
            AnCheckId (Next, ASL_TYPE_HID);
        }

        /* Special typechecking for _CID */

        else if (!strcmp (METHOD_NAME__CID, Op->Asl.NameSeg))
        {
            Next = Op->Asl.Child->Asl.Next;

            if ((Next->Asl.ParseOpcode == PARSEOP_PACKAGE) ||
                (Next->Asl.ParseOpcode == PARSEOP_VAR_PACKAGE))
            {
                Next = Next->Asl.Child;
                while (Next)
                {
                    AnCheckId (Next, ASL_TYPE_CID);
                    Next = Next->Asl.Next;
                }
            }
            else
            {
                AnCheckId (Next, ASL_TYPE_CID);
            }
        }

        break;

    default:

        break;
    }

    /* Check for named object creation within a non-serialized method */

    MtCheckNamedObjectInMethod (Op, MethodInfo);
    return (AE_OK);
}