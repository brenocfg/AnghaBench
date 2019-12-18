#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jmp_buf ;
struct TYPE_24__ {TYPE_17__* localp; TYPE_4__** pInterp; int /*<<< orphan*/ * dp; } ;
struct TYPE_21__ {int /*<<< orphan*/  i; } ;
struct TYPE_23__ {int fRestart; int /*<<< orphan*/ * pState; int /*<<< orphan*/  state; TYPE_2__ sourceID; TYPE_1__* runningWord; TYPE_5__* pSys; } ;
struct TYPE_22__ {int /*<<< orphan*/  size; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* code ) (TYPE_4__*) ;} ;
struct TYPE_19__ {TYPE_3__* pForthWords; } ;
typedef  int /*<<< orphan*/  TIB ;
typedef  TYPE_4__ FICL_VM ;
typedef  TYPE_5__ FICL_SYSTEM ;
typedef  int /*<<< orphan*/  FICL_INT ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILE ; 
 int /*<<< orphan*/  FICL_PROMPT ; 
#define  VM_ABORT 136 
#define  VM_ABORTQ 135 
#define  VM_BREAK 134 
#define  VM_ERREXIT 133 
#define  VM_INNEREXIT 132 
#define  VM_OUTOFTEXT 131 
#define  VM_QUIT 130 
#define  VM_RESTART 129 
#define  VM_USEREXIT 128 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int /*<<< orphan*/  dictAbortDefinition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictEmpty (TYPE_17__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictResetSearchOrder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ficlTextOut (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  vmInnerLoop (TYPE_4__*) ; 
 int /*<<< orphan*/  vmPopIP (TYPE_4__*) ; 
 int /*<<< orphan*/  vmPopTib (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmPushIP (TYPE_4__*,TYPE_4__**) ; 
 int /*<<< orphan*/  vmPushTib (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmQuit (TYPE_4__*) ; 
 int /*<<< orphan*/  vmReset (TYPE_4__*) ; 

int ficlExecC(FICL_VM *pVM, char *pText, FICL_INT size)
{
    FICL_SYSTEM *pSys = pVM->pSys;
    FICL_DICT   *dp   = pSys->dp;

    int        except;
    jmp_buf    vmState;
    jmp_buf   *oldState;
    TIB        saveTib;

    assert(pVM);
    assert(pSys->pInterp[0]);

    if (size < 0)
        size = strlen(pText);

    vmPushTib(pVM, pText, size, &saveTib);

    /*
    ** Save and restore VM's jmp_buf to enable nested calls to ficlExec 
    */
    oldState = pVM->pState;
    pVM->pState = &vmState; /* This has to come before the setjmp! */
    except = setjmp(vmState);

    switch (except)
    {
    case 0:
        if (pVM->fRestart)
        {
            pVM->runningWord->code(pVM);
            pVM->fRestart = 0;
        }
        else
        {   /* set VM up to interpret text */
            vmPushIP(pVM, &(pSys->pInterp[0]));
        }

        vmInnerLoop(pVM);
        break;

    case VM_RESTART:
        pVM->fRestart = 1;
        except = VM_OUTOFTEXT;
        break;

    case VM_OUTOFTEXT:
        vmPopIP(pVM);
#ifdef TESTMAIN
        if ((pVM->state != COMPILE) && (pVM->sourceID.i == 0))
            ficlTextOut(pVM, FICL_PROMPT, 0);
#endif
        break;

    case VM_USEREXIT:
    case VM_INNEREXIT:
    case VM_BREAK:
        break;

    case VM_QUIT:
        if (pVM->state == COMPILE)
        {
            dictAbortDefinition(dp);
#if FICL_WANT_LOCALS
            dictEmpty(pSys->localp, pSys->localp->pForthWords->size);
#endif
        }
        vmQuit(pVM);
        break;

    case VM_ERREXIT:
    case VM_ABORT:
    case VM_ABORTQ:
    default:    /* user defined exit code?? */
        if (pVM->state == COMPILE)
        {
            dictAbortDefinition(dp);
#if FICL_WANT_LOCALS
            dictEmpty(pSys->localp, pSys->localp->pForthWords->size);
#endif
        }
        dictResetSearchOrder(dp);
        vmReset(pVM);
        break;
   }

    pVM->pState    = oldState;
    vmPopTib(pVM, &saveTib);
    return (except);
}