#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ParseOpcode; int /*<<< orphan*/  Next; } ;
struct TYPE_9__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 TYPE_2__* ASL_GET_CHILD_NODE (TYPE_2__*) ; 
 TYPE_2__* ASL_GET_PEER_NODE (TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PARSEOP_RETURN ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
AnLastStatementIsReturn (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;


    /* Check if last statement is a return */

    Next = ASL_GET_CHILD_NODE (Op);
    while (Next)
    {
        if ((!Next->Asl.Next) &&
            (Next->Asl.ParseOpcode == PARSEOP_RETURN))
        {
            return (TRUE);
        }

        Next = ASL_GET_PEER_NODE (Next);
    }

    return (FALSE);
}