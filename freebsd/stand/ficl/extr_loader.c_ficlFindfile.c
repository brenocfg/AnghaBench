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
struct preloaded_file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 scalar_t__ ficlMalloc (int) ; 
 struct preloaded_file* file_findfile (char*,char*) ; 
 int stackPopINT (int /*<<< orphan*/ ) ; 
 scalar_t__ stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,struct preloaded_file*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_1__*,char*) ; 

void
ficlFindfile(FICL_VM *pVM)
{
#ifndef TESTMAIN
	char	*name, *type;
#endif
	char	*namep, *typep;
	struct	preloaded_file* fp;
	int	names, types;

#if FICL_ROBUST > 1
	vmCheckStack(pVM, 4, 1);
#endif

	types = stackPopINT(pVM->pStack);
	typep = (char*) stackPopPtr(pVM->pStack);
	names = stackPopINT(pVM->pStack);
	namep = (char*) stackPopPtr(pVM->pStack);
#ifndef TESTMAIN
	name = (char*) ficlMalloc(names+1);
	if (!name)
		vmThrowErr(pVM, "Error: out of memory");
	strncpy(name, namep, names);
	name[names] = '\0';
	type = (char*) ficlMalloc(types+1);
	if (!type)
		vmThrowErr(pVM, "Error: out of memory");
	strncpy(type, typep, types);
	type[types] = '\0';

	fp = file_findfile(name, type);
#else
	fp = NULL;
#endif
	stackPushPtr(pVM->pStack, fp);

	return;
}