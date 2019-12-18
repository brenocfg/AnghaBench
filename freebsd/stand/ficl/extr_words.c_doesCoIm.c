#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ nLocals; int /*<<< orphan*/  pDoesParen; int /*<<< orphan*/  pUnLinkParen; } ;
struct TYPE_14__ {TYPE_1__* pForthWords; } ;
struct TYPE_13__ {TYPE_7__* pSys; } ;
struct TYPE_12__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ FICL_VM ;
typedef  TYPE_3__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  IGNORE (TYPE_2__*) ; 
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictAppendCell (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictEmpty (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ficlGetLoc (TYPE_7__*) ; 
 TYPE_3__* vmGetDict (TYPE_2__*) ; 

__attribute__((used)) static void doesCoIm(FICL_VM *pVM)
{
    FICL_DICT *dp = vmGetDict(pVM);
#if FICL_WANT_LOCALS
    assert(pVM->pSys->pUnLinkParen);
    if (pVM->pSys->nLocals > 0)
    {
        FICL_DICT *pLoc = ficlGetLoc(pVM->pSys);
        dictEmpty(pLoc, pLoc->pForthWords->size);
        dictAppendCell(dp, LVALUEtoCELL(pVM->pSys->pUnLinkParen));
    }

    pVM->pSys->nLocals = 0;
#endif
    IGNORE(pVM);

    dictAppendCell(dp, LVALUEtoCELL(pVM->pSys->pDoesParen));
    return;
}