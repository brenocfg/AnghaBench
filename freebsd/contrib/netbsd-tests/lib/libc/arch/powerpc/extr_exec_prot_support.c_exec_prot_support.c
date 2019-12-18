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
typedef  int /*<<< orphan*/  execprot ;

/* Variables and functions */
 int NOTIMPL ; 
 int NO_XP ; 
 int PERPAGE_XP ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
exec_prot_support(void)
{
	int execprot = 0;
	size_t len = sizeof(execprot);

	if (sysctlbyname("machdep.execprot", &execprot, &len, NULL, 0) < 0)
		return NOTIMPL;

	if (execprot)
		return PERPAGE_XP;

	return NO_XP;
}