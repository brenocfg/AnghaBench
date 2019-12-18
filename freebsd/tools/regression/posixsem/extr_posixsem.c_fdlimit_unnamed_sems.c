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

/* Variables and functions */
 int CSTAT_CLASS (int) ; 
 int /*<<< orphan*/  CSTAT_ERROR (int) ; 
 scalar_t__ child_worker (int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fail_err (char*,int) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 int /*<<< orphan*/  fdlimit_unnamed_child ; 
 int /*<<< orphan*/  pass () ; 

__attribute__((used)) static void
fdlimit_unnamed_sems(void)
{
	int nsems_max, stat;

	nsems_max = 10;
	if (child_worker(fdlimit_unnamed_child, (void *)(uintptr_t)nsems_max,
	    &stat))
		return;
	errno = CSTAT_ERROR(stat);
	switch (CSTAT_CLASS(stat)) {
	case 0:
		pass();
		break;
	case 1:
		fail_errno("ksem_init");
		break;
	case 2:
		fail_err("Limit of %d semaphores not enforced", nsems_max);
		break;
	case 3:
		fail_errno("getrlimit");
		break;
	case 4:
		fail_errno("getrlimit");
		break;
	default:
		fail_err("bad child state %#x", stat);
		break;
	}
}