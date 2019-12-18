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
struct TYPE_9__ {size_t Length; scalar_t__ Pointer; } ;
struct TYPE_7__ {int /*<<< orphan*/ * Node; } ;
struct TYPE_8__ {TYPE_1__ Scope; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  TYPE_2__ ACPI_GENERIC_STATE ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_OPTIMIZATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,char**)) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 size_t ACPI_NAMESEG_SIZE ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_SEARCH_PARENT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_MSG_SINGLE_NAME_OPTIMIZATION ; 
 int /*<<< orphan*/  ASL_OPTIMIZATION ; 
 int /*<<< orphan*/  AcpiNsLookup (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 char* UtLocalCacheCalloc (size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static ACPI_STATUS
OptSearchToRoot (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState,
    ACPI_NAMESPACE_NODE     *CurrentNode,
    ACPI_NAMESPACE_NODE     *TargetNode,
    ACPI_BUFFER             *TargetPath,
    char                    **NewPath)
{
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_GENERIC_STATE      ScopeInfo;
    ACPI_STATUS             Status;
    char                    *Path;


    ACPI_FUNCTION_NAME (OptSearchToRoot);


    /*
     * Check if search-to-root can be utilized. Use the last NameSeg of
     * the NamePath and 1) See if can be found and 2) If found, make
     * sure that it is the same node that we want. If there is another
     * name in the search path before the one we want, the nodes will
     * not match, and we cannot use this optimization.
     */
    Path = &(((char *) TargetPath->Pointer)[
        TargetPath->Length - ACPI_NAMESEG_SIZE]);
    ScopeInfo.Scope.Node = CurrentNode;

    /* Lookup the NameSeg using SEARCH_PARENT (search-to-root) */

    Status = AcpiNsLookup (&ScopeInfo, Path, ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
        ACPI_NS_SEARCH_PARENT | ACPI_NS_DONT_OPEN_SCOPE,
        WalkState, &(Node));
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /*
     * We found the name, but we must check to make sure that the node
     * matches. Otherwise, there is another identical name in the search
     * path that precludes the use of this optimization.
     */
    if (Node != TargetNode)
    {
        /*
         * This means that another object with the same name was found first,
         * and we cannot use this optimization.
         */
        return (AE_NOT_FOUND);
    }

    /* Found the node, we can use this optimization */

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_OPTIMIZATIONS,
        "NAMESEG:   %-24s", Path));

    /* We must allocate a new string for the name (TargetPath gets deleted) */

    *NewPath = UtLocalCacheCalloc (ACPI_NAMESEG_SIZE + 1);
    strcpy (*NewPath, Path);

    if (strncmp (*NewPath, "_T_", 3))
    {
        AslError (ASL_OPTIMIZATION, ASL_MSG_SINGLE_NAME_OPTIMIZATION,
            Op, *NewPath);
    }

    return (AE_OK);
}