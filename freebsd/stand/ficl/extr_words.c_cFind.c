#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  int /*<<< orphan*/  FICL_VM ;
typedef  int /*<<< orphan*/  FICL_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * POPPTR () ; 
 int /*<<< orphan*/  SI_PFS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmCheckStack (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void cFind(FICL_VM *pVM)
{
    FICL_STRING *sp;
    STRINGINFO si;

#if FICL_ROBUST > 1
    vmCheckStack(pVM,1,2);
#endif
    sp = POPPTR();
    SI_PFS(si, sp);
    do_find(pVM, si, sp);
}