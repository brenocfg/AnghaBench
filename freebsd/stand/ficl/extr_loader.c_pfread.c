#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int read (int,char*,int) ; 
 int stackPopINT (int /*<<< orphan*/ ) ; 
 char* stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void pfread(FICL_VM *pVM)
{
    int     fd, len;
    char *buf;

#if FICL_ROBUST > 1
    vmCheckStack(pVM, 3, 1);
#endif
    len = stackPopINT(pVM->pStack); /* get number of bytes to read */
    buf = stackPopPtr(pVM->pStack); /* get buffer */
    fd = stackPopINT(pVM->pStack); /* get fd */
    if (len > 0 && buf && fd != -1)
	stackPushINT(pVM->pStack, read(fd, buf, len));
    else
	stackPushINT(pVM->pStack, -1);
    return;
}