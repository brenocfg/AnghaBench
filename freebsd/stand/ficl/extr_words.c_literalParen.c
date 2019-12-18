#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ip; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_INT ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmBranchRelative (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void literalParen(FICL_VM *pVM)
{
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 0, 1);
#endif
    PUSHINT(*(FICL_INT *)(pVM->ip));
    vmBranchRelative(pVM, 1);
    return;
}