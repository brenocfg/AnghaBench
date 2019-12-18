#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_11__ {TYPE_1__* Node; int /*<<< orphan*/  ParseOpcode; } ;
struct TYPE_16__ {TYPE_2__ Asl; } ;
struct TYPE_12__ {int /*<<< orphan*/  AcpiBtype; } ;
struct TYPE_15__ {TYPE_3__ Asl; } ;
struct TYPE_13__ {int ParseOpcode; TYPE_6__* ParentMethod; TYPE_9__* Child; int /*<<< orphan*/  CompileFlags; } ;
struct TYPE_14__ {TYPE_4__ Asl; } ;
struct TYPE_10__ {TYPE_6__* Op; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_WALK_VISIT_UPWARD ; 
 int /*<<< orphan*/  AnGetBtype (TYPE_9__*) ; 
 int /*<<< orphan*/  OP_METHOD_TYPED ; 
 int /*<<< orphan*/  PARSEOP_DEFAULT_ARG ; 
#define  PARSEOP_METHOD 129 
 int /*<<< orphan*/  PARSEOP_METHODCALL ; 
#define  PARSEOP_RETURN 128 
 int /*<<< orphan*/  TrWalkParseTree (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (TYPE_5__*,int /*<<< orphan*/ ,void*),int /*<<< orphan*/ *) ; 

ACPI_STATUS
AnMethodTypingWalkEnd (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    UINT32                  ThisOpBtype;


    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_METHOD:

        Op->Asl.CompileFlags |= OP_METHOD_TYPED;
        break;

    case PARSEOP_RETURN:

        if ((Op->Asl.Child) &&
            (Op->Asl.Child->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG))
        {
            ThisOpBtype = AnGetBtype (Op->Asl.Child);

            if ((Op->Asl.Child->Asl.ParseOpcode == PARSEOP_METHODCALL) &&
                (ThisOpBtype == (ACPI_UINT32_MAX -1)))
            {
                /*
                 * The called method is untyped at this time (typically a
                 * forward reference).
                 *
                 * Check for a recursive method call first. Note: the
                 * Child->Node will be null if the method has not been
                 * resolved.
                 */
                if (Op->Asl.Child->Asl.Node &&
                    (Op->Asl.ParentMethod != Op->Asl.Child->Asl.Node->Op))
                {
                    /* We must type the method here */

                    TrWalkParseTree (Op->Asl.Child->Asl.Node->Op,
                        ASL_WALK_VISIT_UPWARD, NULL,
                        AnMethodTypingWalkEnd, NULL);

                    ThisOpBtype = AnGetBtype (Op->Asl.Child);
                }
            }

            /* Returns a value, save the value type */

            if (Op->Asl.ParentMethod)
            {
                Op->Asl.ParentMethod->Asl.AcpiBtype |= ThisOpBtype;
            }
        }
        break;

    default:

        break;
    }

    return (AE_OK);
}