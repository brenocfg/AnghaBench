#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ FileEnd; scalar_t__ FileStart; struct TYPE_3__* Parent; } ;
typedef  TYPE_1__ ACPI_FILE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiGbl_FileTreeRoot ; 
 TYPE_1__* CvFilenameExists (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CvSetFileParent (
    char                    *ChildFile,
    char                    *ParentFile)
{
    ACPI_FILE_NODE          *Child;
    ACPI_FILE_NODE          *Parent;


    Child  = CvFilenameExists (ChildFile, AcpiGbl_FileTreeRoot);
    Parent = CvFilenameExists (ParentFile, AcpiGbl_FileTreeRoot);

    if (Child && Parent)
    {
        Child->Parent = Parent;

        while (Child->Parent)
        {
            if (Child->Parent->FileEnd < Child->FileStart)
            {
                Child->Parent->FileEnd = Child->FileStart;
            }

            Child = Child->Parent;
        }
    }
}