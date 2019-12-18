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
struct TYPE_12__ {scalar_t__ rStack; scalar_t__ pStack; int /*<<< orphan*/ * pState; TYPE_1__* pSys; } ;
struct TYPE_11__ {TYPE_2__* pExitInner; } ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_2__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_STACK ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHINT (int) ; 
#define  VM_INNEREXIT 128 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stackPopPtr (scalar_t__) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmExecute (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmInnerLoop (TYPE_2__*) ; 
 int /*<<< orphan*/  vmPopIP (TYPE_2__*) ; 
 int /*<<< orphan*/  vmPushIP (TYPE_2__*,TYPE_2__**) ; 

__attribute__((used)) static void ficlCatch(FICL_VM *pVM)
{
    int         except;
    jmp_buf     vmState;
    FICL_VM     VM;
    FICL_STACK  pStack;
    FICL_STACK  rStack;
    FICL_WORD   *pFW;

    assert(pVM);
    assert(pVM->pSys->pExitInner);
    

    /*
    ** Get xt.
    ** We need this *before* we save the stack pointer, or
    ** we'll have to pop one element out of the stack after
    ** an exception. I prefer to get done with it up front. :-)
    */
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 0);
#endif
    pFW = stackPopPtr(pVM->pStack);

    /* 
    ** Save vm's state -- a catch will not back out environmental
    ** changes.
    **
    ** We are *not* saving dictionary state, since it is
    ** global instead of per vm, and we are not saving
    ** stack contents, since we are not required to (and,
    ** thus, it would be useless). We save pVM, and pVM
    ** "stacks" (a structure containing general information
    ** about it, including the current stack pointer).
    */
    memcpy((void*)&VM, (void*)pVM, sizeof(FICL_VM));
    memcpy((void*)&pStack, (void*)pVM->pStack, sizeof(FICL_STACK));
    memcpy((void*)&rStack, (void*)pVM->rStack, sizeof(FICL_STACK));

    /*
    ** Give pVM a jmp_buf
    */
    pVM->pState = &vmState;

    /*
    ** Safety net
    */
    except = setjmp(vmState);

    switch (except)
    {
        /*
        ** Setup condition - push poison pill so that the VM throws
        ** VM_INNEREXIT if the XT terminates normally, then execute
        ** the XT
        */
    case 0:
        vmPushIP(pVM, &(pVM->pSys->pExitInner));          /* Open mouth, insert emetic */
        vmExecute(pVM, pFW);
        vmInnerLoop(pVM);
        break;

        /*
        ** Normal exit from XT - lose the poison pill, 
        ** restore old setjmp vector and push a zero. 
        */
    case VM_INNEREXIT:
        vmPopIP(pVM);                   /* Gack - hurl poison pill */
        pVM->pState = VM.pState;        /* Restore just the setjmp vector */
        PUSHINT(0);   /* Push 0 -- everything is ok */
        break;

        /*
        ** Some other exception got thrown - restore pre-existing VM state
        ** and push the exception code
        */
    default:
        /* Restore vm's state */
        memcpy((void*)pVM, (void*)&VM, sizeof(FICL_VM));
        memcpy((void*)pVM->pStack, (void*)&pStack, sizeof(FICL_STACK));
        memcpy((void*)pVM->rStack, (void*)&rStack, sizeof(FICL_STACK));

        PUSHINT(except);/* Push error */
        break;
    }
}