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
struct TYPE_6__ {int /*<<< orphan*/  cp; } ;
struct TYPE_7__ {TYPE_1__ tib; } ;
typedef  TYPE_2__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSHPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmGetInBufLen (TYPE_2__*) ; 

__attribute__((used)) static void source(FICL_VM *pVM)
{
#if FICL_ROBUST > 1
    vmCheckStack(pVM,0,2);
#endif
    PUSHPTR(pVM->tib.cp);
    PUSHINT(vmGetInBufLen(pVM));
    return;
}