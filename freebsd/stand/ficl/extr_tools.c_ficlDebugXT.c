#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int WORDKIND ;
struct TYPE_8__ {TYPE_1__* pSys; int /*<<< orphan*/  pStack; } ;
struct TYPE_7__ {int /*<<< orphan*/  bpStep; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_2__ FICL_VM ;

/* Variables and functions */
#define  COLON 129 
#define  DOES 128 
 int ficlWordClassify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seeXT (TYPE_2__*) ; 
 int /*<<< orphan*/ * stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmExecute (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmSetBreak (TYPE_2__*,int /*<<< orphan*/ *) ; 

void ficlDebugXT(FICL_VM *pVM)
{
    FICL_WORD *xt    = stackPopPtr(pVM->pStack);
    WORDKIND   wk    = ficlWordClassify(xt);

    stackPushPtr(pVM->pStack, xt);
    seeXT(pVM);

    switch (wk)
    {
    case COLON:
    case DOES:
        /*
        ** Run the colon code and set a breakpoint at the next instruction
        */
        vmExecute(pVM, xt);
        vmSetBreak(pVM, &(pVM->pSys->bpStep));
        break;

    default:
        vmExecute(pVM, xt);
        break;
    }

    return;
}