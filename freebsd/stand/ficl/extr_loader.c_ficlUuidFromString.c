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
typedef  char uuid_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  ficlFree (char*) ; 
 scalar_t__ ficlMalloc (int) ; 
 int stackPopINT (int /*<<< orphan*/ ) ; 
 scalar_t__ stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  uuid_from_string (char*,char*,scalar_t__*) ; 
 scalar_t__ uuid_s_ok ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmThrowErr (TYPE_1__*,char*) ; 

void
ficlUuidFromString(FICL_VM *pVM)
{
#ifndef	TESTMAIN
	char	*uuid;
	uint32_t status;
#endif
	char	*uuidp;
	int	uuids;
	uuid_t	*u;

#if FICL_ROBUST > 1
	vmCheckStack(pVM, 2, 0);
#endif

	uuids = stackPopINT(pVM->pStack);
	uuidp = (char *) stackPopPtr(pVM->pStack);

#ifndef	TESTMAIN
	uuid = (char *)ficlMalloc(uuids + 1);
	if (!uuid)
		vmThrowErr(pVM, "Error: out of memory");
	strncpy(uuid, uuidp, uuids);
	uuid[uuids] = '\0';

	u = (uuid_t *)ficlMalloc(sizeof (*u));

	uuid_from_string(uuid, u, &status);
	ficlFree(uuid);
	if (status != uuid_s_ok) {
		ficlFree(u);
		u = NULL;
	}
#else
	u = NULL;
#endif
	stackPushPtr(pVM->pStack, u);


	return;
}