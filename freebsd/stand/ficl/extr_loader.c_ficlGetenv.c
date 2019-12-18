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
struct TYPE_5__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  ficlFree (char*) ; 
 scalar_t__ ficlMalloc (int) ; 
 char* getenv (char*) ; 
 int stackPopINT (int /*<<< orphan*/ ) ; 
 scalar_t__ stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_1__*,char*) ; 

void
ficlGetenv(FICL_VM *pVM)
{
#ifndef TESTMAIN
	char	*name, *value;
#endif
	char	*namep;
	int	names;

#if FICL_ROBUST > 1
	vmCheckStack(pVM, 2, 2);
#endif
	names = stackPopINT(pVM->pStack);
	namep = (char*) stackPopPtr(pVM->pStack);

#ifndef TESTMAIN
	name = (char*) ficlMalloc(names+1);
	if (!name)
		vmThrowErr(pVM, "Error: out of memory");
	strncpy(name, namep, names);
	name[names] = '\0';

	value = getenv(name);
	ficlFree(name);

	if(value != NULL) {
		stackPushPtr(pVM->pStack, value);
		stackPushINT(pVM->pStack, strlen(value));
	} else
#endif
		stackPushINT(pVM->pStack, -1);

	return;
}