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
struct TYPE_6__ {TYPE_1__* vmList; } ;
struct TYPE_5__ {struct TYPE_5__* link; TYPE_2__* pSys; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  TYPE_2__ FICL_SYSTEM ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmDelete (TYPE_1__*) ; 

void ficlFreeVM(FICL_VM *pVM)
{
    FICL_SYSTEM *pSys = pVM->pSys;
    FICL_VM *pList = pSys->vmList;

    assert(pVM != NULL);

    if (pSys->vmList == pVM)
    {
        pSys->vmList = pSys->vmList->link;
    }
    else for (; pList != NULL; pList = pList->link)
    {
        if (pList->link == pVM)
        {
            pList->link = pVM->link;
            break;
        }
    }

    if (pList)
        vmDelete(pVM);
    return;
}