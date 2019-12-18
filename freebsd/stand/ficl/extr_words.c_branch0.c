#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* ip; int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  scalar_t__ FICL_UNS ;

/* Variables and functions */
 scalar_t__ stackPopUNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmBranchRelative (TYPE_1__*,uintptr_t) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void branch0(FICL_VM *pVM)
{
    FICL_UNS flag;
    
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 0);
#endif
    flag = stackPopUNS(pVM->pStack);

    if (flag) 
    {                           /* fall through */
        vmBranchRelative(pVM, 1);
    }
    else 
    {                           /* take branch (to else/endif/begin) */
        vmBranchRelative(pVM, (uintptr_t)*(pVM->ip));
    }

    return;
}