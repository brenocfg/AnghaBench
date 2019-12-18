#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dwOSVersionInfoSize; } ;
typedef  int /*<<< orphan*/  OSVERSIONINFOEX ;
typedef  int /*<<< orphan*/  OSVERSIONINFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ GetVersionEx (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 scalar_t__ bInit ; 
 TYPE_1__ osVer ; 

__attribute__((used)) static void
initialize_action(void) {
	BOOL bSuccess;

	if (bInit)
		return;	
	/*
	 * NOTE: VC++ 6.0 gets this function declaration wrong
	 * so we compensate by casting the argument
	 */
	osVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	bSuccess = GetVersionEx((OSVERSIONINFO *) &osVer);

	/*
	 * Versions of NT before NT4.0 SP6 did not return the
	 * extra info that the EX structure provides and returns
	 * a failure so we need to retry with the old structure.
	 */
	if(!bSuccess) {
		osVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		bSuccess = GetVersionEx((OSVERSIONINFO *) &osVer);
	}
	bInit = TRUE;
}