#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jmp_buf ;
struct TYPE_12__ {int /*<<< orphan*/ * runningWord; int /*<<< orphan*/ * pState; TYPE_1__* pSys; } ;
struct TYPE_11__ {TYPE_2__* pExitInner; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_2__ FICL_VM ;

/* Variables and functions */
#define  VM_ABORT 136 
#define  VM_ABORTQ 135 
#define  VM_BREAK 134 
#define  VM_ERREXIT 133 
#define  VM_INNEREXIT 132 
#define  VM_OUTOFTEXT 131 
#define  VM_QUIT 130 
#define  VM_RESTART 129 
#define  VM_USEREXIT 128 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmExecute (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmInnerLoop (TYPE_2__*) ; 
 int /*<<< orphan*/  vmPopIP (TYPE_2__*) ; 
 int /*<<< orphan*/  vmPushIP (TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  vmThrow (TYPE_2__*,int) ; 

int ficlExecXT(FICL_VM *pVM, FICL_WORD *pWord)
{
    int        except;
    jmp_buf    vmState;
    jmp_buf   *oldState;
    FICL_WORD *oldRunningWord;

    assert(pVM);
    assert(pVM->pSys->pExitInner);
    
    /* 
    ** Save the runningword so that RESTART behaves correctly
    ** over nested calls.
    */
    oldRunningWord = pVM->runningWord;
    /*
    ** Save and restore VM's jmp_buf to enable nested calls
    */
    oldState = pVM->pState;
    pVM->pState = &vmState; /* This has to come before the setjmp! */
    except = setjmp(vmState);

    if (except)
        vmPopIP(pVM);
    else
        vmPushIP(pVM, &(pVM->pSys->pExitInner));

    switch (except)
    {
    case 0:
        vmExecute(pVM, pWord);
        vmInnerLoop(pVM);
        break;

    case VM_INNEREXIT:
    case VM_BREAK:
        break;

    case VM_RESTART:
    case VM_OUTOFTEXT:
    case VM_USEREXIT:
    case VM_QUIT:
    case VM_ERREXIT:
    case VM_ABORT:
    case VM_ABORTQ:
    default:    /* user defined exit code?? */
        if (oldState)
        {
            pVM->pState = oldState;
            vmThrow(pVM, except);
        }
        break;
    }

    pVM->pState    = oldState;
    pVM->runningWord = oldRunningWord;
    return (except);
}