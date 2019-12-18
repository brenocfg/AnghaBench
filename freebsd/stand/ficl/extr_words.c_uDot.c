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
struct TYPE_5__ {int /*<<< orphan*/  pad; int /*<<< orphan*/  base; int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_UNS ;

/* Variables and functions */
 int /*<<< orphan*/  stackPopUNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ultoa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmTextOut (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uDot(FICL_VM *pVM)
{
    FICL_UNS u;
#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 0);
#endif
    u = stackPopUNS(pVM->pStack);
    ultoa(u, pVM->pad, pVM->base);
    strcat(pVM->pad, " ");
    vmTextOut(pVM, pVM->pad, 0);
    return;
}