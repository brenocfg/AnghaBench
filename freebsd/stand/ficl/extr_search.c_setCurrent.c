#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * pCompile; } ;
struct TYPE_6__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_HASH ;
typedef  TYPE_2__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ficlLockDictionary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stackPopPtr (int /*<<< orphan*/ ) ; 
 TYPE_2__* vmGetDict (TYPE_1__*) ; 

__attribute__((used)) static void setCurrent(FICL_VM *pVM)
{
    FICL_HASH *pHash = stackPopPtr(pVM->pStack);
    FICL_DICT *pDict = vmGetDict(pVM);
    ficlLockDictionary(TRUE);
    pDict->pCompile = pHash;
    ficlLockDictionary(FALSE);
    return;
}