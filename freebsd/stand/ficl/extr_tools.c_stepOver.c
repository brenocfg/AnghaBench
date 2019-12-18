#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int WORDKIND ;
struct TYPE_6__ {int /*<<< orphan*/ * origXT; int /*<<< orphan*/ ** address; } ;
struct TYPE_8__ {TYPE_1__ bpStep; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** ip; TYPE_5__* pSys; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_2__ FICL_VM ;

/* Variables and functions */
#define  COLON 129 
#define  DOES 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ficlLookup (TYPE_5__*,char*) ; 
 int ficlWordClassify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stepIn (TYPE_2__*) ; 

void stepOver(FICL_VM *pVM)
{
    FICL_WORD *pFW;
    WORDKIND kind;
    FICL_WORD *pStep = ficlLookup(pVM->pSys, "step-break");
    assert(pStep);

    pFW = *pVM->ip;
    kind = ficlWordClassify(pFW);

    switch (kind)
    {
    case COLON: 
    case DOES:
        /*
        ** assume that the next cell holds an instruction 
        ** set a breakpoint there and return to the inner interp
        */
        pVM->pSys->bpStep.address = pVM->ip + 1;
        pVM->pSys->bpStep.origXT =  pVM->ip[1];
        pVM->ip[1] = pStep;
        break;

    default:
        stepIn(pVM);
        break;
    }

    return;
}