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
typedef  int /*<<< orphan*/  nsems_max ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int CSTAT_CLASS (int) ; 
 int /*<<< orphan*/  CSTAT_ERROR (int) ; 
 char* TEST_PATH ; 
 scalar_t__ child_worker (int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exhaust_named_child ; 
 int /*<<< orphan*/  fail_err (char*,int) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 int /*<<< orphan*/  ksem_unlink (char*) ; 
 int /*<<< orphan*/  pass () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
exhaust_named_sems(void)
{
	char buffer[64];
	size_t len;
	int i, nsems_max, stat;

	len = sizeof(nsems_max);
	if (sysctlbyname("p1003_1b.sem_nsems_max", &nsems_max, &len, NULL, 0) <
	    0) {
		fail_errno("sysctl(p1003_1b.sem_nsems_max)");
		return;
	}

	if (child_worker(exhaust_named_child, (void *)(uintptr_t)nsems_max,
	    &stat) < 0)
		return;
	errno = CSTAT_ERROR(stat);
	switch (CSTAT_CLASS(stat)) {
	case 0:
		pass();
		break;
	case 1:
		fail_errno("ksem_open");
		break;
	case 2:
		fail_err("Limit of %d semaphores not enforced", nsems_max);
		break;
	default:
		fail_err("bad child state %#x", stat);
		break;
	}

	/* Cleanup any semaphores created by the child. */
	for (i = 0; i < nsems_max + 1; i++) {
		snprintf(buffer, sizeof(buffer), "%s%d", TEST_PATH, i);
		ksem_unlink(buffer);
	}
}