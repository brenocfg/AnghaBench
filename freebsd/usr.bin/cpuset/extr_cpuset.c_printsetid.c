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
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  cpusetid_t ;

/* Variables and functions */
 size_t CPU_LEVEL_CPUSET ; 
 size_t CPU_LEVEL_WHICH ; 
 scalar_t__ cpuset_getid (size_t,size_t,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ id ; 
 size_t level ; 
 int /*<<< orphan*/ * levelnames ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sflag ; 
 size_t which ; 
 char** whichnames ; 

__attribute__((used)) static void
printsetid(void)
{
	cpusetid_t setid;

	/*
	 * Only LEVEL_WHICH && WHICH_CPUSET has a numbered id.
	 */
	if (level == CPU_LEVEL_WHICH && !sflag)
		level = CPU_LEVEL_CPUSET;
	if (cpuset_getid(level, which, id, &setid))
		err(errno, "getid");
	printf("%s %jd%s id: %d\n", whichnames[which], (intmax_t)id,
	    levelnames[level], setid);
}