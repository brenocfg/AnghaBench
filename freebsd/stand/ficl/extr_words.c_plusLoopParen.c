#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ i; } ;
struct TYPE_10__ {scalar_t__ i; } ;
struct TYPE_9__ {scalar_t__ i; } ;
struct TYPE_8__ {scalar_t__* ip; int /*<<< orphan*/  rStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  scalar_t__ FICL_INT ;

/* Variables and functions */
 int /*<<< orphan*/  LVALUEtoCELL (scalar_t__) ; 
 TYPE_7__ POP () ; 
 int /*<<< orphan*/  stackDrop (int /*<<< orphan*/ ,int) ; 
 TYPE_5__ stackFetch (int /*<<< orphan*/ ,int) ; 
 TYPE_4__ stackGetTop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackSetTop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmBranchRelative (TYPE_1__*,uintptr_t) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void plusLoopParen(FICL_VM *pVM)
{
    FICL_INT index,limit,increment;
    int flag;

#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 0);
#endif

    index = stackGetTop(pVM->rStack).i;
    limit = stackFetch(pVM->rStack, 1).i;
    increment = POP().i;
    
    index += increment;

    if (increment < 0)
        flag = (index < limit);
    else
        flag = (index >= limit);

    if (flag) 
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