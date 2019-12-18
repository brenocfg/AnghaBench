#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ParseOpcode; TYPE_2__* Next; TYPE_2__* Child; TYPE_2__* Parent; int /*<<< orphan*/  NameSeg; } ;
struct TYPE_6__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASL_MSG_NO_REGION ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  METHOD_NAME__REG ; 
 scalar_t__ PARSEOP_OPERATIONREGION ; 

void
ApCheckRegMethod (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;
    ACPI_PARSE_OBJECT       *Parent;


    /* We are only interested in _REG methods */

    if (!ACPI_COMPARE_NAMESEG (METHOD_NAME__REG, &Op->Asl.NameSeg))
    {
        return;
    }

    /* Get the start of the current scope */

    Parent = Op->Asl.Parent;
    Next = Parent->Asl.Child;

    /* Search entire scope for an operation region declaration */

    while (Next)
    {
        if (Next->Asl.ParseOpcode == PARSEOP_OPERATIONREGION)
        {
            return; /* Found region, OK */
        }

        Next = Next->Asl.Next;
    }

    /* No region found, issue warning */

    AslError (ASL_WARNING, ASL_MSG_NO_REGION, Op, NULL);
}