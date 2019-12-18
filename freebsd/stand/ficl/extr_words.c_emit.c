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
struct TYPE_5__ {char* pad; int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int stackPopINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmTextOut (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit(FICL_VM *pVM)
{
    char *cp = pVM->pad;
    int i;

#if FICL_ROBUST > 1
    vmCheckStack(pVM, 1, 0);
#endif
    i = stackPopINT(pVM->pStack);
    cp[0] = (char)i;
    cp[1] = '\0';
    vmTextOut(pVM, cp, 0);
    return;
}