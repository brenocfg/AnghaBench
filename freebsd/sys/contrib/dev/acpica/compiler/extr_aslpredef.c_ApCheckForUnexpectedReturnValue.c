#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ParseOpcode; TYPE_5__* Child; } ;
struct TYPE_13__ {TYPE_1__ Asl; } ;
struct TYPE_12__ {TYPE_3__* Op; } ;
struct TYPE_10__ {int /*<<< orphan*/  ExternalName; } ;
struct TYPE_11__ {TYPE_2__ Asl; } ;
typedef  TYPE_4__ ASL_METHOD_INFO ;
typedef  TYPE_5__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_MSG_RESERVED_NO_RETURN_VAL ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PARSEOP_ZERO ; 

__attribute__((used)) static void
ApCheckForUnexpectedReturnValue (
    ACPI_PARSE_OBJECT       *Op,
    ASL_METHOD_INFO         *MethodInfo)
{
    ACPI_PARSE_OBJECT       *ReturnValueOp;


    /* Ignore Return() and Return(Zero) (they are the same) */

    ReturnValueOp = Op->Asl.Child;
    if (ReturnValueOp->Asl.ParseOpcode == PARSEOP_ZERO)
    {
        return;
    }

    /* We have a valid return value, but the reserved name did not expect it */

    AslError (ASL_WARNING, ASL_MSG_RESERVED_NO_RETURN_VAL,
        Op, MethodInfo->Op->Asl.ExternalName);
}