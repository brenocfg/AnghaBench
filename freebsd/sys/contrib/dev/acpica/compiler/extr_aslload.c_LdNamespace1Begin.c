#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
typedef  int UINT32 ;
struct TYPE_31__ {int Flags; scalar_t__ Type; int Value; TYPE_5__* Op; } ;
struct TYPE_30__ {scalar_t__ Class; } ;
struct TYPE_25__ {char* Name; scalar_t__ Integer; } ;
struct TYPE_27__ {int AmlOpcode; char* ExternalName; int ParseOpcode; int CompileFlags; char* Namepath; int AcpiBtype; scalar_t__ Extra; TYPE_7__* Node; TYPE_5__* Parent; TYPE_1__ Value; TYPE_5__* Next; TYPE_5__* Child; int /*<<< orphan*/  ParseOpName; } ;
struct TYPE_29__ {TYPE_3__ Asl; } ;
struct TYPE_28__ {int /*<<< orphan*/  ScopeInfo; TYPE_2__* OpInfo; } ;
struct TYPE_26__ {int Flags; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_4__ ACPI_WALK_STATE ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;
typedef  TYPE_6__ ACPI_OPCODE_INFO ;
typedef  scalar_t__ ACPI_OBJECT_TYPE ;
typedef  TYPE_7__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (scalar_t__ (*) (TYPE_5__*,int,void*)) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int /*<<< orphan*/  ACPI_NAMESEG_SIZE ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_ERROR_IF_FOUND ; 
 int ACPI_NS_EXTERNAL ; 
 int ACPI_NS_NO_UPSEARCH ; 
 int ACPI_NS_PREFIX_MUST_EXIST ; 
 int ACPI_NS_SEARCH_PARENT ; 
 scalar_t__ ACPI_TYPE_ANY ; 
#define  ACPI_TYPE_BUFFER 143 
#define  ACPI_TYPE_DEVICE 142 
#define  ACPI_TYPE_INTEGER 141 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_REGION_FIELD ; 
#define  ACPI_TYPE_LOCAL_SCOPE 140 
#define  ACPI_TYPE_POWER 139 
#define  ACPI_TYPE_PROCESSOR 138 
 int /*<<< orphan*/  ACPI_TYPE_REGION ; 
#define  ACPI_TYPE_STRING 137 
#define  ACPI_TYPE_THERMAL 136 
 scalar_t__ AE_ALREADY_EXISTS ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_OK ; 
#define  AML_BANK_FIELD_OP 135 
 scalar_t__ AML_CLASS_NAMED_OBJECT ; 
 int AML_CREATE ; 
 int AML_EXTERNAL_OP ; 
#define  AML_FIELD_OP 134 
#define  AML_INDEX_FIELD_OP 133 
#define  AML_INT_CONNECTION_OP 132 
 int AML_INT_NAMEPATH_OP ; 
 int AML_NAMED ; 
 int ANOBJ_IS_EXTERNAL ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int ASL_EXTERNAL_METHOD ; 
 int /*<<< orphan*/  ASL_MSG_CROSS_TABLE_SCOPE ; 
 int /*<<< orphan*/  ASL_MSG_FOUND_HERE ; 
 int /*<<< orphan*/  ASL_MSG_NAMEPATH_NOT_EXIST ; 
 int /*<<< orphan*/  ASL_MSG_NAME_EXISTS ; 
 int /*<<< orphan*/  ASL_MSG_NOT_FOUND ; 
 int /*<<< orphan*/  ASL_MSG_SCOPE_TYPE ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 scalar_t__ AcpiDsScopeStackPush (TYPE_7__*,int const,TYPE_4__*) ; 
 TYPE_7__* AcpiGbl_RootNode ; 
 scalar_t__ AcpiNsLookup (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int,TYPE_4__*,TYPE_7__**) ; 
 scalar_t__ AcpiNsOpensScope (scalar_t__) ; 
 void* AcpiPsGetOpcodeInfo (int) ; 
 char* AcpiUtGetTypeName (scalar_t__) ; 
 int /*<<< orphan*/  AslCoreSubsystemError (TYPE_5__*,scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  AslDualParseOpError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,char*,int /*<<< orphan*/ ,TYPE_5__*,char*) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,char*) ; 
 char* AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  AslGbl_TableSignature ; 
 scalar_t__ AslMapNamedOpcodeToDataType (int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LdCheckSpecialNames (TYPE_7__*,TYPE_5__*) ; 
 scalar_t__ LdLoadFieldElements (int /*<<< orphan*/ ,TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ LdLoadResourceElements (TYPE_5__*,TYPE_4__*) ; 
 int OP_IS_RESOURCE_DESC ; 
 int OP_NOT_FOUND_DURING_LOAD ; 
#define  PARSEOP_DEFAULT_ARG 131 
#define  PARSEOP_EXTERNAL 130 
 int PARSEOP_METHOD ; 
#define  PARSEOP_NAME 129 
 int PARSEOP_NAMESEG ; 
 int PARSEOP_NAMESTRING ; 
 scalar_t__ PARSEOP_PACKAGE ; 
#define  PARSEOP_SCOPE 128 
 scalar_t__ PARSEOP_VAR_PACKAGE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ACPI_STATUS
LdNamespace1Begin (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = (ACPI_WALK_STATE *) Context;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_PARSE_OBJECT       *MethodOp;
    ACPI_STATUS             Status;
    ACPI_OBJECT_TYPE        ObjectType;
    ACPI_OBJECT_TYPE        ActualObjectType = ACPI_TYPE_ANY;
    char                    *Path;
    UINT32                  Flags = ACPI_NS_NO_UPSEARCH;
    ACPI_PARSE_OBJECT       *Arg;
    UINT32                  i;
    BOOLEAN                 ForceNewScope = FALSE;
    const ACPI_OPCODE_INFO  *OpInfo;
    ACPI_PARSE_OBJECT       *ParentOp;


    ACPI_FUNCTION_NAME (LdNamespace1Begin);


    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH, "Op %p [%s]\n",
        Op, Op->Asl.ParseOpName));

    /*
     * We are only interested in opcodes that have an associated name
     * (or multiple names)
     */
    switch (Op->Asl.AmlOpcode)
    {
    case AML_INDEX_FIELD_OP:

        Status = LdLoadFieldElements (ACPI_TYPE_LOCAL_REGION_FIELD, Op, WalkState);
        return (Status);

    case AML_BANK_FIELD_OP:
    case AML_FIELD_OP:

        Status = LdLoadFieldElements (ACPI_TYPE_REGION, Op, WalkState);
        return (Status);

    case AML_INT_CONNECTION_OP:

        if (Op->Asl.Child->Asl.AmlOpcode != AML_INT_NAMEPATH_OP)
        {
            break;
        }

        Arg = Op->Asl.Child;
        Status = AcpiNsLookup (WalkState->ScopeInfo, Arg->Asl.ExternalName,
            ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT,
            WalkState, &Node);
        if (ACPI_FAILURE (Status))
        {
            break;
        }

        break;

    default:

        /* All other opcodes go below */

        break;
    }

    /* Check if this object has already been installed in the namespace */

    if (Op->Asl.Node)
    {
        return (AE_OK);
    }

    /* Check for a possible illegal forward reference */

    if ((Op->Asl.ParseOpcode == PARSEOP_NAMESEG) ||
        (Op->Asl.ParseOpcode == PARSEOP_NAMESTRING))
    {
        /*
         * Op->Asl.Namepath will be NULL for these opcodes.
         * These opcodes are guaranteed to have a parent.
         * Examine the parent opcode.
         */
        ParentOp = Op->Asl.Parent;
        OpInfo = AcpiPsGetOpcodeInfo (ParentOp->Asl.AmlOpcode);

        /*
         * Exclude all operators that actually declare a new name:
         *      Name (ABCD, 1) -> Ignore (AML_CLASS_NAMED_OBJECT)
         * We only want references to named objects:
         *      Store (2, WXYZ) -> Attempt to resolve the name
         */
        if (OpInfo->Class == AML_CLASS_NAMED_OBJECT)
        {
            return (AE_OK);
        }

        /*
         * Check if the referenced object exists at this point during
         * the load:
         * 1) If it exists, then this cannot be a forward reference.
         * 2) If it does not exist, it could be a forward reference or
         * it truly does not exist (and no external declaration).
         */
        Status = AcpiNsLookup (WalkState->ScopeInfo,
            Op->Asl.Value.Name, ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
            ACPI_NS_SEARCH_PARENT | ACPI_NS_DONT_OPEN_SCOPE,
            WalkState, &Node);
        if (Status == AE_NOT_FOUND)
        {
            /*
             * This is either a forward reference or the object truly
             * does not exist. The two cases can only be differentiated
             * during the cross-reference stage later. Mark the Op/Name
             * as not-found for now to indicate the need for further
             * processing.
             *
             * Special case: Allow forward references from elements of
             * Package objects. This provides compatibility with other
             * ACPI implementations. To correctly implement this, the
             * ACPICA table load defers package resolution until the entire
             * namespace has been loaded.
             */
            if ((ParentOp->Asl.ParseOpcode != PARSEOP_PACKAGE) &&
                (ParentOp->Asl.ParseOpcode != PARSEOP_VAR_PACKAGE))
            {
                Op->Asl.CompileFlags |= OP_NOT_FOUND_DURING_LOAD;
            }

            return (AE_OK);
        }

        return (Status);
    }

    Path = Op->Asl.Namepath;
    if (!Path)
    {
        return (AE_OK);
    }

    /* Map the raw opcode into an internal object type */

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_NAME:

        Arg = Op->Asl.Child;  /* Get the NameSeg/NameString node */
        Arg = Arg->Asl.Next;  /* First peer is the object to be associated with the name */

        /*
         * If this name refers to a ResourceTemplate, we will need to open
         * a new scope so that the resource subfield names can be entered into
         * the namespace underneath this name
         */
        if (Op->Asl.CompileFlags & OP_IS_RESOURCE_DESC)
        {
            ForceNewScope = TRUE;
        }

        /* Get the data type associated with the named object, not the name itself */

        /* Log2 loop to convert from Btype (binary) to Etype (encoded) */

        ObjectType = 1;
        for (i = 1; i < Arg->Asl.AcpiBtype; i *= 2)
        {
            ObjectType++;
        }
        break;

    case PARSEOP_EXTERNAL:
        /*
         * "External" simply enters a name and type into the namespace.
         * We must be careful to not open a new scope, however, no matter
         * what type the external name refers to (e.g., a method)
         *
         * first child is name, next child is ObjectType
         */
        ActualObjectType = (UINT8) Op->Asl.Child->Asl.Next->Asl.Value.Integer;
        ObjectType = ACPI_TYPE_ANY;

        /*
         * We will mark every new node along the path as "External". This
         * allows some or all of the nodes to be created later in the ASL
         * code. Handles cases like this:
         *
         *   External (\_SB_.PCI0.ABCD, IntObj)
         *   Scope (_SB_)
         *   {
         *       Device (PCI0)
         *       {
         *       }
         *   }
         *   Method (X)
         *   {
         *       Store (\_SB_.PCI0.ABCD, Local0)
         *   }
         */
        Flags |= ACPI_NS_EXTERNAL;
        break;

    case PARSEOP_DEFAULT_ARG:

        if (Op->Asl.CompileFlags == OP_IS_RESOURCE_DESC)
        {
            Status = LdLoadResourceElements (Op, WalkState);
            return_ACPI_STATUS (Status);
        }

        ObjectType = AslMapNamedOpcodeToDataType (Op->Asl.AmlOpcode);
        break;

    case PARSEOP_SCOPE:
        /*
         * The name referenced by Scope(Name) must already exist at this point.
         * In other words, forward references for Scope() are not supported.
         * The only real reason for this is that the MS interpreter cannot
         * handle this case. Perhaps someday this case can go away.
         */
        Status = AcpiNsLookup (WalkState->ScopeInfo, Path, ACPI_TYPE_ANY,
            ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT, WalkState, &Node);
        if (ACPI_FAILURE (Status))
        {
            if (Status == AE_NOT_FOUND)
            {
                /* The name was not found, go ahead and create it */

                Status = AcpiNsLookup (WalkState->ScopeInfo, Path,
                    ACPI_TYPE_LOCAL_SCOPE, ACPI_IMODE_LOAD_PASS1,
                    Flags, WalkState, &Node);
                if (ACPI_FAILURE (Status))
                {
                    return_ACPI_STATUS (Status);
                }

                /* However, this is an error -- operand to Scope must exist */

                if (strlen (Op->Asl.ExternalName) == ACPI_NAMESEG_SIZE)
                {
                    AslError (ASL_ERROR, ASL_MSG_NOT_FOUND, Op,
                        Op->Asl.ExternalName);
                }
                else
                {
                    AslError (ASL_ERROR, ASL_MSG_NAMEPATH_NOT_EXIST, Op,
                        Op->Asl.ExternalName);
                }

                goto FinishNode;
            }

            AslCoreSubsystemError (Op, Status,
                "Failure from namespace lookup", FALSE);

            return_ACPI_STATUS (Status);
        }
        else /* Status AE_OK */
        {
            /*
             * Do not allow references to external scopes from the DSDT.
             * This is because the DSDT is always loaded first, and the
             * external reference cannot be resolved -- causing a runtime
             * error because Scope() must be resolved immediately.
             * 10/2015.
             */
            if ((Node->Flags & ANOBJ_IS_EXTERNAL) &&
                (ACPI_COMPARE_NAMESEG (AslGbl_TableSignature, "DSDT")))
            {
                /* However, allowed if the reference is within a method */

                MethodOp = Op->Asl.Parent;
                while (MethodOp &&
                      (MethodOp->Asl.ParseOpcode != PARSEOP_METHOD))
                {
                    MethodOp = MethodOp->Asl.Parent;
                }

                if (!MethodOp)
                {
                    /* Not in a control method, error */

                    AslError (ASL_ERROR, ASL_MSG_CROSS_TABLE_SCOPE, Op, NULL);
                }
            }
        }

        /* We found a node with this name, now check the type */

        switch (Node->Type)
        {
        case ACPI_TYPE_LOCAL_SCOPE:
        case ACPI_TYPE_DEVICE:
        case ACPI_TYPE_POWER:
        case ACPI_TYPE_PROCESSOR:
        case ACPI_TYPE_THERMAL:

            /* These are acceptable types - they all open a new scope */
            break;

        case ACPI_TYPE_INTEGER:
        case ACPI_TYPE_STRING:
        case ACPI_TYPE_BUFFER:
            /*
             * These types we will allow, but we will change the type.
             * This enables some existing code of the form:
             *
             *  Name (DEB, 0)
             *  Scope (DEB) { ... }
             *
             * Which is used to workaround the fact that the MS interpreter
             * does not allow Scope() forward references.
             */
            sprintf (AslGbl_MsgBuffer, "%s [%s], changing type to [Scope]",
                Op->Asl.ExternalName, AcpiUtGetTypeName (Node->Type));
            AslError (ASL_REMARK, ASL_MSG_SCOPE_TYPE, Op, AslGbl_MsgBuffer);

            /* Switch the type to scope, open the new scope */

            Node->Type = ACPI_TYPE_LOCAL_SCOPE;
            Status = AcpiDsScopeStackPush (Node, ACPI_TYPE_LOCAL_SCOPE,
                WalkState);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }
            break;

        default:

            /* All other types are an error */

            sprintf (AslGbl_MsgBuffer, "%s [%s]", Op->Asl.ExternalName,
                AcpiUtGetTypeName (Node->Type));
            AslError (ASL_ERROR, ASL_MSG_SCOPE_TYPE, Op, AslGbl_MsgBuffer);

            /*
             * However, switch the type to be an actual scope so
             * that compilation can continue without generating a whole
             * cascade of additional errors. Open the new scope.
             */
            Node->Type = ACPI_TYPE_LOCAL_SCOPE;
            Status = AcpiDsScopeStackPush (Node, ACPI_TYPE_LOCAL_SCOPE,
                WalkState);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }
            break;
        }

        Status = AE_OK;
        goto FinishNode;

    default:

        ObjectType = AslMapNamedOpcodeToDataType (Op->Asl.AmlOpcode);
        break;
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH, "Loading name: %s, (%s)\n",
        Op->Asl.ExternalName, AcpiUtGetTypeName (ObjectType)));

    /* The name must not already exist */

    Flags |= ACPI_NS_ERROR_IF_FOUND;

    /*
     * For opcodes that enter new names into the namespace,
     * all prefix NameSegs must exist.
     */
    WalkState->OpInfo = AcpiPsGetOpcodeInfo (Op->Asl.AmlOpcode);
    if (((WalkState->OpInfo->Flags & AML_NAMED) ||
        (WalkState->OpInfo->Flags & AML_CREATE)) &&
        (Op->Asl.AmlOpcode != AML_EXTERNAL_OP))
    {
        Flags |= ACPI_NS_PREFIX_MUST_EXIST;
    }

    /*
     * Enter the named type into the internal namespace. We enter the name
     * as we go downward in the parse tree. Any necessary subobjects that
     * involve arguments to the opcode must be created as we go back up the
     * parse tree later.
     */
    Status = AcpiNsLookup (WalkState->ScopeInfo, Path, ObjectType,
        ACPI_IMODE_LOAD_PASS1, Flags, WalkState, &Node);
    if (ACPI_FAILURE (Status))
    {
        if (Status == AE_ALREADY_EXISTS)
        {
            /* The name already exists in this scope */

            if (Node->Type == ACPI_TYPE_LOCAL_SCOPE)
            {
                /* Allow multiple references to the same scope */

                Node->Type = (UINT8) ObjectType;
                Status = AE_OK;
            }
            else if ((Node->Flags & ANOBJ_IS_EXTERNAL) &&
                     (Op->Asl.ParseOpcode != PARSEOP_EXTERNAL))
            {
                /*
                 * Allow one create on an object or segment that was
                 * previously declared External
                 */
                Node->Flags &= ~ANOBJ_IS_EXTERNAL;
                Node->Type = (UINT8) ObjectType;

                /* Just retyped a node, probably will need to open a scope */

                if (AcpiNsOpensScope (ObjectType))
                {
                    Status = AcpiDsScopeStackPush (Node, ObjectType, WalkState);
                    if (ACPI_FAILURE (Status))
                    {
                        return_ACPI_STATUS (Status);
                    }
                }

                Status = AE_OK;
            }
            else if (!(Node->Flags & ANOBJ_IS_EXTERNAL) &&
                     (Op->Asl.ParseOpcode == PARSEOP_EXTERNAL))
            {
                /*
                 * Allow externals in same scope as the definition of the
                 * actual object. Similar to C. Allows multiple definition
                 * blocks that refer to each other in the same file.
                 */
                Status = AE_OK;
            }
            else if ((Node->Flags & ANOBJ_IS_EXTERNAL) &&
                     (Op->Asl.ParseOpcode == PARSEOP_EXTERNAL) &&
                     (ObjectType == ACPI_TYPE_ANY))
            {
                /* Allow update of externals of unknown type. */

                if (AcpiNsOpensScope (ActualObjectType))
                {
                    Node->Type = (UINT8) ActualObjectType;
                    Status = AE_OK;
                }
                else
                {
                    sprintf (AslGbl_MsgBuffer, "%s [%s]", Op->Asl.ExternalName,
                        AcpiUtGetTypeName (Node->Type));
                    AslError (ASL_ERROR, ASL_MSG_SCOPE_TYPE, Op, AslGbl_MsgBuffer);
                    return_ACPI_STATUS (AE_OK);
                }
            }
            else
            {
                /* Valid error, object already exists */

                AslDualParseOpError (ASL_ERROR, ASL_MSG_NAME_EXISTS, Op,
                    Op->Asl.ExternalName, ASL_MSG_FOUND_HERE, Node->Op,
                    Node->Op->Asl.ExternalName);
                return_ACPI_STATUS (AE_OK);
            }
        }
        else if (AE_NOT_FOUND)
        {
            /*
             * One or more prefix NameSegs of the NamePath do not exist
             * (all of them must exist). Attempt to continue compilation
             * by setting the current scope to the root.
             */
            Node = AcpiGbl_RootNode;
            Status = AE_OK;
        }
        else
        {
            /* Flag all other errors as coming from the ACPICA core */

            AslCoreSubsystemError (Op, Status,
                "Failure from namespace lookup", FALSE);
            return_ACPI_STATUS (Status);
        }
    }

    /* Check special names like _WAK and _PTS */

    LdCheckSpecialNames (Node, Op);

    if (ForceNewScope)
    {
        Status = AcpiDsScopeStackPush (Node, ObjectType, WalkState);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

FinishNode:
    /*
     * Point the parse node to the new namespace node, and point
     * the Node back to the original Parse node
     */
    Op->Asl.Node = Node;
    Node->Op = Op;

    /* Set the actual data type if appropriate (EXTERNAL term only) */

    if (ActualObjectType != ACPI_TYPE_ANY)
    {
        Node->Type = (UINT8) ActualObjectType;
        Node->Value = ASL_EXTERNAL_METHOD;
    }

    if (Op->Asl.ParseOpcode == PARSEOP_METHOD)
    {
        /*
         * Get the method argument count from "Extra" and save
         * it in the namespace node
         */
        Node->Value = (UINT32) Op->Asl.Extra;
    }

    return_ACPI_STATUS (Status);
}