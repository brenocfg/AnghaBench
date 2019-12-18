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
struct TYPE_4__ {int ParseOpcode; TYPE_2__* Child; TYPE_2__* Parent; } ;
struct TYPE_5__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  PARSEOP_DECREMENT 134 
#define  PARSEOP_DEFINITION_BLOCK 133 
#define  PARSEOP_ELSE 132 
#define  PARSEOP_IF 131 
#define  PARSEOP_INCREMENT 130 
#define  PARSEOP_METHOD 129 
#define  PARSEOP_WHILE 128 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
AnIsResultUsed (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Parent;


    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_INCREMENT:
    case PARSEOP_DECREMENT:

        /* These are standalone operators, no return value */

        return (TRUE);

    default:

        break;
    }

    /* Examine parent to determine if the return value is used */

    Parent = Op->Asl.Parent;
    switch (Parent->Asl.ParseOpcode)
    {
    /* If/While - check if the operator is the predicate */

    case PARSEOP_IF:
    case PARSEOP_WHILE:

        /* First child is the predicate */

        if (Parent->Asl.Child == Op)
        {
            return (TRUE);
        }

        return (FALSE);

    /* Not used if one of these is the parent */

    case PARSEOP_METHOD:
    case PARSEOP_DEFINITION_BLOCK:
    case PARSEOP_ELSE:

        return (FALSE);

    default:

        /* Any other type of parent means that the result is used */

        return (TRUE);
    }
}