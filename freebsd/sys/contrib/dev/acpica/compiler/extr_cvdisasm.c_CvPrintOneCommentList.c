#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {struct TYPE_4__* Next; int /*<<< orphan*/ * Comment; } ;
typedef  TYPE_1__ ACPI_COMMENT_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDmIndent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_RegCommentCache ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsReleaseObject (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
CvPrintOneCommentList (
    ACPI_COMMENT_NODE       *CommentList,
    UINT32                  Level)
{
    ACPI_COMMENT_NODE       *Current = CommentList;
    ACPI_COMMENT_NODE       *Previous;


    while (Current)
    {
        Previous = Current;
        if (Current->Comment)
        {
            AcpiDmIndent(Level);
            AcpiOsPrintf("%s\n", Current->Comment);
            Current->Comment = NULL;
        }

        Current = Current->Next;
        AcpiOsReleaseObject(AcpiGbl_RegCommentCache, Previous);
    }
}