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
typedef  int /*<<< orphan*/  FICL_VM ;

/* Variables and functions */
 char* POPPTR () ; 
 int /*<<< orphan*/  PUSHPTR (char*) ; 
 int /*<<< orphan*/  vmCheckStack (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void charPlus(FICL_VM *pVM)
{
    char *cp;
#if FICL_ROBUST > 1
    vmCheckStack(pVM,1,1);
#endif

    cp = POPPTR();
    PUSHPTR(cp + 1);
    return;
}