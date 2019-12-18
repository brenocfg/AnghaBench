#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  textOut; void* fStack; void* rStack; void* pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ ficlMalloc (int) ; 
 int /*<<< orphan*/  ficlTextOut ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* stackCreate (unsigned int) ; 
 int /*<<< orphan*/  stackDelete (void*) ; 
 int /*<<< orphan*/  vmReset (TYPE_1__*) ; 

FICL_VM *vmCreate(FICL_VM *pVM, unsigned nPStack, unsigned nRStack)
{
    if (pVM == NULL)
    {
        pVM = (FICL_VM *)ficlMalloc(sizeof (FICL_VM));
        assert (pVM);
        memset(pVM, 0, sizeof (FICL_VM));
    }

    if (pVM->pStack)
        stackDelete(pVM->pStack);
    pVM->pStack = stackCreate(nPStack);

    if (pVM->rStack)
        stackDelete(pVM->rStack);
    pVM->rStack = stackCreate(nRStack);

#if FICL_WANT_FLOAT
    if (pVM->fStack)
        stackDelete(pVM->fStack);
    pVM->fStack = stackCreate(nPStack);
#endif

    pVM->textOut = ficlTextOut;

    vmReset(pVM);
    return pVM;
}