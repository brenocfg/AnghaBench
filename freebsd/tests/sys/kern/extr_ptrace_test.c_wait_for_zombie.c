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
struct kinfo_proc {scalar_t__ ki_stat; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  kp ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int CTL_KERN ; 
 scalar_t__ ESRCH ; 
 int KERN_PROC ; 
 int KERN_PROC_PID ; 
 scalar_t__ SZOMB ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int sysctl (int*,int /*<<< orphan*/ ,struct kinfo_proc*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void
wait_for_zombie(pid_t pid)
{

	/*
	 * Wait for a process to exit.  This is kind of gross, but
	 * there is not a better way.
	 *
	 * Prior to r325719, the kern.proc.pid.<pid> sysctl failed
	 * with ESRCH.  After that change, a valid struct kinfo_proc
	 * is returned for zombies with ki_stat set to SZOMB.
	 */
	for (;;) {
		struct kinfo_proc kp;
		size_t len;
		int mib[4];

		mib[0] = CTL_KERN;
		mib[1] = KERN_PROC;
		mib[2] = KERN_PROC_PID;
		mib[3] = pid;
		len = sizeof(kp);
		if (sysctl(mib, nitems(mib), &kp, &len, NULL, 0) == -1) {
			ATF_REQUIRE(errno == ESRCH);
			break;
		}
		if (kp.ki_stat == SZOMB)
			break;
		usleep(5000);
	}
}