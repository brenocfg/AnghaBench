#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int here; } ;
struct TYPE_8__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/ * FICL_INT ;
typedef  TYPE_2__ FICL_DICT ;
typedef  int /*<<< orphan*/  CELL ;

/* Variables and functions */
 int /*<<< orphan*/  LVALUEtoCELL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictAppendCell (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matchControlTag (TYPE_1__*,char*) ; 
 scalar_t__ stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resolveBackBranch(FICL_DICT *dp, FICL_VM *pVM, char *tag)
{
    FICL_INT offset;
    CELL *patchAddr;

    matchControlTag(pVM, tag);

#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 0);
#endif
    patchAddr = (CELL *)stackPopPtr(pVM->pStack);
    offset = patchAddr - dp->here;
    dictAppendCell(dp, LVALUEtoCELL(offset));

    return;
}