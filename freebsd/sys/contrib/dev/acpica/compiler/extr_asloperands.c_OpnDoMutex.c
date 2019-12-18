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
struct TYPE_6__ {int Integer; } ;
struct TYPE_7__ {TYPE_1__ Value; TYPE_3__* Next; TYPE_3__* Child; } ;
struct TYPE_8__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_SYNC_LEVEL ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
OpnDoMutex (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Next;


    Next = Op->Asl.Child;
    Next = Next->Asl.Next;

    if (Next->Asl.Value.Integer > 15)
    {
        AslError (ASL_ERROR, ASL_MSG_SYNC_LEVEL, Next, NULL);
    }
    return;
}