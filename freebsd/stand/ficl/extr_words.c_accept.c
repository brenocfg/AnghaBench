#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int FICL_UNS ;

/* Variables and functions */
 int /*<<< orphan*/  PUSHINT (int) ; 
 int /*<<< orphan*/  VM_RESTART ; 
 int stackPopINT (int /*<<< orphan*/ ) ; 
 char* stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 
 char* vmGetInBuf (TYPE_1__*) ; 
 char* vmGetInBufEnd (TYPE_1__*) ; 
 int /*<<< orphan*/  vmThrow (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmUpdateTib (TYPE_1__*,char*) ; 

__attribute__((used)) static void accept(FICL_VM *pVM)
{
    FICL_UNS count, len;
    char *cp;
    char *pBuf, *pEnd;

#if FICL_ROBUST > 1
    vmCheckStack(pVM,2,1);
#endif

    pBuf = vmGetInBuf(pVM);
    pEnd = vmGetInBufEnd(pVM);
    len = pEnd - pBuf;
    if (len == 0)
        vmThrow(pVM, VM_RESTART);

    /*
    ** Now we have something in the text buffer - use it 
    */
    count = stackPopINT(pVM->pStack);
    cp    = stackPopPtr(pVM->pStack);

    len = (count < len) ? count : len;
    strncpy(cp, vmGetInBuf(pVM), len);
    pBuf += len;
    vmUpdateTib(pVM, pBuf);
    PUSHINT(len);

    return;
}