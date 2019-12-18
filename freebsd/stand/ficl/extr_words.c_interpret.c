#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_3__** parseList; } ;
struct TYPE_25__ {int /*<<< orphan*/  pStack; TYPE_5__* pSys; } ;
struct TYPE_24__ {scalar_t__ code; TYPE_1__* param; } ;
struct TYPE_23__ {scalar_t__ count; } ;
struct TYPE_22__ {scalar_t__ fn; } ;
typedef  TYPE_2__ STRINGINFO ;
typedef  TYPE_3__ FICL_WORD ;
typedef  TYPE_4__ FICL_VM ;
typedef  TYPE_5__ FICL_SYSTEM ;
typedef  scalar_t__ (* FICL_PARSE_STEP ) (TYPE_4__*,TYPE_2__) ;

/* Variables and functions */
 int FICL_MAX_PARSE_STEPS ; 
 int SI_COUNT (TYPE_2__) ; 
 int /*<<< orphan*/  SI_PTR (TYPE_2__) ; 
 int /*<<< orphan*/  VM_OUTOFTEXT ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int /*<<< orphan*/  ficlExecXT (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ ficlParseWord (TYPE_4__*,TYPE_2__) ; 
 scalar_t__ parseStepParen ; 
 scalar_t__ stackPopINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushUNS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_2__) ; 
 TYPE_2__ vmGetWord0 (TYPE_4__*) ; 
 int /*<<< orphan*/  vmThrow (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_4__*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void interpret(FICL_VM *pVM)
{
    STRINGINFO si;
    int i;
    FICL_SYSTEM *pSys;

    assert(pVM);

    pSys = pVM->pSys;
    si   = vmGetWord0(pVM);

    /*
    ** Get next word...if out of text, we're done.
    */
    if (si.count == 0)
    {
        vmThrow(pVM, VM_OUTOFTEXT);
    }

    /*
    ** Attempt to find the incoming token in the dictionary. If that fails...
    ** run the parse chain against the incoming token until somebody eats it.
    ** Otherwise emit an error message and give up.
    ** Although ficlParseWord could be part of the parse list, I've hard coded it
    ** in for robustness. ficlInitSystem adds the other default steps to the list.
    */
    if (ficlParseWord(pVM, si))
        return;

    for (i=0; i < FICL_MAX_PARSE_STEPS; i++)
    {
        FICL_WORD *pFW = pSys->parseList[i];
           
        if (pFW == NULL)
            break;

        if (pFW->code == parseStepParen)
        {
            FICL_PARSE_STEP pStep;
            pStep = (FICL_PARSE_STEP)(pFW->param->fn);
            if ((*pStep)(pVM, si))
                return;
        }
        else
        {
            stackPushPtr(pVM->pStack, SI_PTR(si));
            stackPushUNS(pVM->pStack, SI_COUNT(si));
            ficlExecXT(pVM, pFW);
            if (stackPopINT(pVM->pStack))
                return;
        }
    }

    i = SI_COUNT(si);
    vmThrowErr(pVM, "%.*s not found", i, SI_PTR(si));

    return;                 /* back to inner interpreter */
}