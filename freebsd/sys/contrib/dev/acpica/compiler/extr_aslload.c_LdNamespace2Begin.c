#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_17__ {int /*<<< orphan*/  Object; } ;
struct TYPE_14__ {scalar_t__ ParseOpcode; int CompileFlags; char* Namepath; int /*<<< orphan*/  ExternalName; TYPE_3__* Child; int /*<<< orphan*/  AmlOpcode; TYPE_4__* Node; int /*<<< orphan*/  ParseOpName; } ;
struct TYPE_16__ {TYPE_1__ Asl; } ;
struct TYPE_15__ {int /*<<< orphan*/  ScopeInfo; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_2__ ACPI_WALK_STATE ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OBJECT_TYPE ;
typedef  TYPE_4__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (scalar_t__ (*) (TYPE_3__*,int /*<<< orphan*/ ,void*)) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 scalar_t__ ACPI_NAMESEG_SIZE ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_NO_UPSEARCH ; 
 int ACPI_NS_SEARCH_PARENT ; 
 int /*<<< orphan*/  ACPI_OPERAND_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_TYPE_LOCAL_RESOURCE ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_NAMEPATH_NOT_EXIST ; 
 int /*<<< orphan*/  ASL_MSG_NOT_FOUND ; 
 scalar_t__ AcpiDsScopeStackPush (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ AcpiNsLookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,TYPE_4__**) ; 
 scalar_t__ AcpiNsOpensScope (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslCoreSubsystemError (TYPE_3__*,scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslMapNamedOpcodeToDataType (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int OP_IS_RESOURCE_DESC ; 
 scalar_t__ PARSEOP_ALIAS ; 
 scalar_t__ PARSEOP_DEFAULT_ARG ; 
 scalar_t__ PARSEOP_NAME ; 
 scalar_t__ TRUE ; 
 scalar_t__ UtInternalizeName (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
LdNamespace2Begin (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_WALK_STATE         *WalkState = (ACPI_WALK_STATE *) Context;
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_OBJECT_TYPE        ObjectType;
    BOOLEAN                 ForceNewScope = FALSE;
    ACPI_PARSE_OBJECT       *Arg;
    char                    *Path;
    ACPI_NAMESPACE_NODE     *TargetNode;


    ACPI_FUNCTION_NAME (LdNamespace2Begin);
    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH, "Op %p [%s]\n",
        Op, Op->Asl.ParseOpName));


    /* Ignore Ops with no namespace node */

    Node = Op->Asl.Node;
    if (!Node)
    {
        return (AE_OK);
    }

    /* Get the type to determine if we should push the scope */

    if ((Op->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG) &&
        (Op->Asl.CompileFlags == OP_IS_RESOURCE_DESC))
    {
        ObjectType = ACPI_TYPE_LOCAL_RESOURCE;
    }
    else
    {
        ObjectType = AslMapNamedOpcodeToDataType (Op->Asl.AmlOpcode);
    }

    /* Push scope for Resource Templates */

    if (Op->Asl.ParseOpcode == PARSEOP_NAME)
    {
        if (Op->Asl.CompileFlags & OP_IS_RESOURCE_DESC)
        {
            ForceNewScope = TRUE;
        }
    }

    /* Push the scope stack */

    if (ForceNewScope || AcpiNsOpensScope (ObjectType))
    {
        Status = AcpiDsScopeStackPush (Node, ObjectType, WalkState);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    if (Op->Asl.ParseOpcode == PARSEOP_ALIAS)
    {
        /*
         * Complete the alias node by getting and saving the target node.
         * First child is the alias target
         */
        Arg = Op->Asl.Child;

        /* Get the target pathname */

        Path = Arg->Asl.Namepath;
        if (!Path)
        {
            Status = UtInternalizeName (Arg->Asl.ExternalName, &Path);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
        }

        /* Get the NS node associated with the target. It must exist. */

        Status = AcpiNsLookup (WalkState->ScopeInfo, Path, ACPI_TYPE_ANY,
            ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT | ACPI_NS_DONT_OPEN_SCOPE,
            WalkState, &TargetNode);
        if (ACPI_FAILURE (Status))
        {
            if (Status == AE_NOT_FOUND)
            {
                /* Standalone NameSeg vs. NamePath */

                if (strlen (Arg->Asl.ExternalName) == ACPI_NAMESEG_SIZE)
                {
                    AslError (ASL_ERROR, ASL_MSG_NOT_FOUND, Op,
                        Arg->Asl.ExternalName);
                }
                else
                {
                    AslError (ASL_ERROR, ASL_MSG_NAMEPATH_NOT_EXIST, Op,
                        Arg->Asl.ExternalName);
                }

#if 0
/*
 * NOTE: Removed 10/2018 to enhance compiler error reporting. No
 * regressions seen.
 */
                /*
                 * The name was not found, go ahead and create it.
                 * This prevents more errors later.
                 */
                Status = AcpiNsLookup (WalkState->ScopeInfo, Path,
                    ACPI_TYPE_ANY, ACPI_IMODE_LOAD_PASS1,
                    ACPI_NS_NO_UPSEARCH, WalkState, &Node);
#endif
                return (Status);
/* Removed: return (AE_OK)*/
            }

            AslCoreSubsystemError (Op, Status,
                "Failure from namespace lookup", FALSE);
            return (AE_OK);
        }

        /* Save the target node within the alias node */

        Node->Object = ACPI_CAST_PTR (ACPI_OPERAND_OBJECT, TargetNode);
    }

    return (AE_OK);
}