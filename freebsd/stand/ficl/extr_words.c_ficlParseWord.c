#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ nLocals; } ;
struct TYPE_9__ {scalar_t__ state; TYPE_7__* pSys; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int FICL_FALSE ; 
 scalar_t__ FICL_TRUE ; 
 scalar_t__ INTERPRET ; 
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictAppendCell (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictCheck (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictLookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ficlLookupLoc (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmExecute (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmGetDict (TYPE_1__*) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_1__*,char*) ; 
 scalar_t__ wordIsCompileOnly (int /*<<< orphan*/ *) ; 
 scalar_t__ wordIsImmediate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ficlParseWord(FICL_VM *pVM, STRINGINFO si)
{
    FICL_DICT *dp = vmGetDict(pVM);
    FICL_WORD *tempFW;

#if FICL_ROBUST
    dictCheck(dp, pVM, 0);
    vmCheckStack(pVM, 0, 0);
#endif

#if FICL_WANT_LOCALS
    if (pVM->pSys->nLocals > 0)
    {
        tempFW = ficlLookupLoc(pVM->pSys, si);
    }
    else
#endif
    tempFW = dictLookup(dp, si);

    if (pVM->state == INTERPRET)
    {
        if (tempFW != NULL)
        {
            if (wordIsCompileOnly(tempFW))
            {
                vmThrowErr(pVM, "Error: Compile only!");
            }

            vmExecute(pVM, tempFW);
            return (int)FICL_TRUE;
        }
    }

    else /* (pVM->state == COMPILE) */
    {
        if (tempFW != NULL)
        {
            if (wordIsImmediate(tempFW))
            {
                vmExecute(pVM, tempFW);
            }
            else
            {
                dictAppendCell(dp, LVALUEtoCELL(tempFW));
            }
            return (int)FICL_TRUE;
        }
    }

    return FICL_FALSE;
}