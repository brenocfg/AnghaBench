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
struct TYPE_5__ {int /*<<< orphan*/  pad; int /*<<< orphan*/  pSys; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int /*<<< orphan*/  FICL_UNS ;

/* Variables and functions */
 unsigned int POPUNS () ; 
 int /*<<< orphan*/  ficlSetEnv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmGetWordToPad (TYPE_1__*) ; 

__attribute__((used)) static void envConstant(FICL_VM *pVM)
{
    unsigned value;

#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 0);
#endif

    vmGetWordToPad(pVM);
    value = POPUNS();
    ficlSetEnv(pVM->pSys, pVM->pad, (FICL_UNS)value);
    return;
}