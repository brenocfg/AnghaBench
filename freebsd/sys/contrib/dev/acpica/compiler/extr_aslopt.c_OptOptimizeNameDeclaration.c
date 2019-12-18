#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* Parent; } ;
struct TYPE_12__ {TYPE_3__ Common; } ;
struct TYPE_9__ {scalar_t__ ParseOpcode; } ;
struct TYPE_10__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_OPTIMIZATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**)) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 scalar_t__ ACPI_IS_ROOT_PREFIX (char) ; 
 int /*<<< orphan*/  ACPI_NS_DONT_OPEN_SCOPE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_INTERNAL ; 
 int /*<<< orphan*/  ASL_MSG_NAME_OPTIMIZATION ; 
 int /*<<< orphan*/  ASL_NO_ABORT ; 
 int /*<<< orphan*/  ASL_OPTIMIZATION ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int /*<<< orphan*/ * AcpiGbl_RootNode ; 
 int /*<<< orphan*/  AcpiNsExternalizeName (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  AcpiNsLookup (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AslCoreSubsystemError (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,char*) ; 
 scalar_t__ PARSEOP_DEFINITION_BLOCK ; 

__attribute__((used)) static ACPI_STATUS
OptOptimizeNameDeclaration (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState,
    ACPI_NAMESPACE_NODE     *CurrentNode,
    ACPI_NAMESPACE_NODE     *TargetNode,
    char                    *AmlNameString,
    char                    **NewPath)
{
    ACPI_STATUS             Status;
    char                    *NewPathExternal;
    ACPI_NAMESPACE_NODE     *Node;


    ACPI_FUNCTION_TRACE (OptOptimizeNameDeclaration);


    if (((CurrentNode == AcpiGbl_RootNode) ||
        (Op->Common.Parent->Asl.ParseOpcode == PARSEOP_DEFINITION_BLOCK)) &&
            (ACPI_IS_ROOT_PREFIX (AmlNameString[0])))
    {
        /*
         * The current scope is the root, and the namepath has a root prefix
         * that is therefore extraneous. Remove it.
         */
        *NewPath = &AmlNameString[1];

        /* Debug output */

        Status = AcpiNsExternalizeName (ACPI_UINT32_MAX, *NewPath,
            NULL, &NewPathExternal);
        if (ACPI_FAILURE (Status))
        {
            AslCoreSubsystemError (Op, Status, "Externalizing NamePath",
                ASL_NO_ABORT);
            return (Status);
        }

        /*
         * Check to make sure that the optimization finds the node we are
         * looking for. This is simply a sanity check on the new
         * path that has been created.
         *
         * We know that we are at the root, so NULL is used for the scope.
         */
        Status = AcpiNsLookup (NULL, *NewPath,
            ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
            ACPI_NS_DONT_OPEN_SCOPE, WalkState, &(Node));
        if (ACPI_SUCCESS (Status))
        {
            /* Found the namepath, but make sure the node is correct */

            if (Node == TargetNode)
            {
                /* The lookup matched the node, accept this optimization */

                AslError (ASL_OPTIMIZATION, ASL_MSG_NAME_OPTIMIZATION,
                    Op, NewPathExternal);

                ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
                    "AT ROOT:   %-24s", NewPathExternal));
            }
            else
            {
                /* Node is not correct, do not use this optimization */

                Status = AE_NOT_FOUND;
                ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
                    " ***** WRONG NODE"));
                AslError (ASL_WARNING, ASL_MSG_COMPILER_INTERNAL, Op,
                    "Not using optimized name - found wrong node");
            }
        }
        else
        {
            /* The lookup failed, we obviously cannot use this optimization */

            ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
                " ***** NOT FOUND"));
            AslError (ASL_WARNING, ASL_MSG_COMPILER_INTERNAL, Op,
                "Not using optimized name - did not find node");
        }

        ACPI_FREE (NewPathExternal);
        return (Status);
    }

    /* Could not optimize */

    return (AE_NOT_FOUND);
}