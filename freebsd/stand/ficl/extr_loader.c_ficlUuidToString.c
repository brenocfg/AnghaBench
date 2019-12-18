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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 scalar_t__ stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 scalar_t__ uuid_s_ok ; 
 int /*<<< orphan*/  uuid_to_string (int /*<<< orphan*/ *,char**,scalar_t__*) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void
ficlUuidToString(FICL_VM *pVM)
{
#ifndef	TESTMAIN
	char	*uuid;
	uint32_t status;
#endif
	uuid_t	*u;

#if FICL_ROBUST > 1
	vmCheckStack(pVM, 1, 0);
#endif

	u = (uuid_t *)stackPopPtr(pVM->pStack);

#ifndef	TESTMAIN
	uuid_to_string(u, &uuid, &status);
	if (status != uuid_s_ok) {
		stackPushPtr(pVM->pStack, uuid);
		stackPushINT(pVM->pStack, strlen(uuid));
	} else
#endif
		stackPushINT(pVM->pStack, -1);

	return;
}