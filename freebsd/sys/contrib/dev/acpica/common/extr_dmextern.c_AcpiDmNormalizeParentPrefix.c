#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char UINT8 ;
typedef  size_t UINT32 ;
struct TYPE_8__ {struct TYPE_8__* Parent; } ;
struct TYPE_6__ {TYPE_3__* Node; TYPE_2__* Parent; } ;
struct TYPE_7__ {TYPE_1__ Common; } ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;
typedef  TYPE_3__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 char* ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 scalar_t__ AML_PARENT_PREFIX ; 
 char AML_ROOT_PREFIX ; 
 char* AcpiNsGetExternalPathname (TYPE_3__*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *
AcpiDmNormalizeParentPrefix (
    ACPI_PARSE_OBJECT       *Op,
    char                    *Path)
{
    ACPI_NAMESPACE_NODE     *Node;
    char                    *Fullpath;
    char                    *ParentPath;
    ACPI_SIZE               Length;
    UINT32                  Index = 0;


    if (!Op)
    {
        return (NULL);
    }

    /* Search upwards in the parse tree until we reach the next namespace node */

    Op = Op->Common.Parent;
    while (Op)
    {
        if (Op->Common.Node)
        {
            break;
        }

        Op = Op->Common.Parent;
    }

    if (!Op)
    {
        return (NULL);
    }

    /*
     * Find the actual parent node for the reference:
     * Remove all carat prefixes from the input path.
     * There may be multiple parent prefixes (For example, ^^^M000)
     */
    Node = Op->Common.Node;
    while (Node && (*Path == (UINT8) AML_PARENT_PREFIX))
    {
        Node = Node->Parent;
        Path++;
    }

    if (!Node)
    {
        return (NULL);
    }

    /* Get the full pathname for the parent node */

    ParentPath = AcpiNsGetExternalPathname (Node);
    if (!ParentPath)
    {
        return (NULL);
    }

    Length = (strlen (ParentPath) + strlen (Path) + 1);
    if (ParentPath[1])
    {
        /*
         * If ParentPath is not just a simple '\', increment the length
         * for the required dot separator (ParentPath.Path)
         */
        Length++;

        /* For External() statements, we do not want a leading '\' */

        if (*ParentPath == AML_ROOT_PREFIX)
        {
            Index = 1;
        }
    }

    Fullpath = ACPI_ALLOCATE_ZEROED (Length);
    if (!Fullpath)
    {
        goto Cleanup;
    }

    /*
     * Concatenate parent fullpath and path. For example,
     * parent fullpath "\_SB_", Path "^INIT", Fullpath "\_SB_.INIT"
     *
     * Copy the parent path
     */
    strcpy (Fullpath, &ParentPath[Index]);

    /*
     * Add dot separator
     * (don't need dot if parent fullpath is a single backslash)
     */
    if (ParentPath[1])
    {
        strcat (Fullpath, ".");
    }

    /* Copy child path (carat parent prefix(es) were skipped above) */

    strcat (Fullpath, Path);

Cleanup:
    ACPI_FREE (ParentPath);
    return (Fullpath);
}