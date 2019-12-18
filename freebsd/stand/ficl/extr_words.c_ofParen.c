#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ u; } ;
struct TYPE_6__ {scalar_t__ ip; int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  scalar_t__ FICL_UNS ;

/* Variables and functions */
 scalar_t__ POPUNS () ; 
 int /*<<< orphan*/  stackDrop (int /*<<< orphan*/ ,int) ; 
 TYPE_4__ stackGetTop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmBranchRelative (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void ofParen(FICL_VM *pVM)
{
	FICL_UNS a, b;

#if FICL_ROBUST > 1
    vmCheckStack(pVM, 2, 1);
#endif

	a = POPUNS();
	b = stackGetTop(pVM->pStack).u;

    if (a == b)
    {                           /* fall through */
		stackDrop(pVM->pStack, 1);
        vmBranchRelative(pVM, 1);
    }
    else 
    {                           /* take branch to next of or endswitch */
        vmBranchRelative(pVM, *(int *)(pVM->ip));
    }

    return;
}