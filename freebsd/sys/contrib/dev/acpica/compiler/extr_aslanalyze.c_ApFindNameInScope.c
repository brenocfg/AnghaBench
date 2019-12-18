#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ParseOpcode; TYPE_2__* Next; int /*<<< orphan*/  NameSeg; TYPE_2__* Child; TYPE_2__* Parent; } ;
struct TYPE_5__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PARSEOP_METHOD ; 
 scalar_t__ PARSEOP_NAME ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
ApFindNameInScope (
    char                    *Name,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;
    ACPI_PARSE_OBJECT       *Parent;


    /* Get the start of the current scope */

    Parent = Op->Asl.Parent;
    Next = Parent->Asl.Child;

    /* Search entire scope for a match to the name */

    while (Next)
    {
        if ((Next->Asl.ParseOpcode == PARSEOP_METHOD) ||
            (Next->Asl.ParseOpcode == PARSEOP_NAME))
        {
            if (ACPI_COMPARE_NAMESEG (Name, Next->Asl.NameSeg))
            {
                return (TRUE);
            }
        }

        Next = Next->Asl.Next;
    }

    return (FALSE);
}