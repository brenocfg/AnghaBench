#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ i; } ;
struct TYPE_7__ {scalar_t__ i; } ;
struct TYPE_6__ {scalar_t__* ip; int /*<<< orphan*/  rStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  scalar_t__ FICL_INT ;

/* Variables and functions */
 int /*<<< orphan*/  LVALUEtoCELL (scalar_t__) ; 
 int /*<<< orphan*/  stackDrop (int /*<<< orphan*/ ,int) ; 
 TYPE_4__ stackFetch (int /*<<< orphan*/ ,int) ; 
 TYPE_3__ stackGetTop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackSetTop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmBranchRelative (TYPE_1__*,uintptr_t) ; 

__attribute__((used)) static void loopParen(FICL_VM *pVM)
{
    FICL_INT index = stackGetTop(pVM->rStack).i;
    FICL_INT limit = stackFetch(pVM->rStack, 1).i;

    index++;

    if (index >= limit) 
    {
        stackDrop(pVM->rStack, 3); /* nuke the loop indices & "leave" addr */
        vmBranchRelative(pVM, 1);  /* fall through the loop */
    }
    else 
    {                       /* update index, branch to loop head */
        stackSetTop(pVM->rStack, LVALUEtoCELL(index));
        vmBranchRelative(pVM, (uintptr_t)*(pVM->ip));
    }

    return;
}