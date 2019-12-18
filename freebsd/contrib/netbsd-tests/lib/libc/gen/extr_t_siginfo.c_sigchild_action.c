#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long si_signo; unsigned long si_errno; unsigned long si_code; unsigned long si_uid; unsigned long si_pid; unsigned long si_status; scalar_t__ si_stime; scalar_t__ si_utime; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int WSTOPSIG (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  child ; 
 int /*<<< orphan*/  code ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  status ; 

__attribute__((used)) static void
sigchild_action(int signo, siginfo_t *info, void *ptr)
{
	if (info != NULL) {
		printf("info=%p\n", info);
		printf("ptr=%p\n", ptr);
		printf("si_signo=%d\n", info->si_signo);
		printf("si_errno=%d\n", info->si_errno);
		printf("si_code=%d\n", info->si_code);
		printf("si_uid=%d\n", info->si_uid);
		printf("si_pid=%d\n", info->si_pid);
		printf("si_status=%d\n", info->si_status);
#ifdef __NetBSD__
		printf("si_utime=%lu\n", (unsigned long int)info->si_utime);
		printf("si_stime=%lu\n", (unsigned long int)info->si_stime);
#endif
	}
	ATF_REQUIRE_EQ(info->si_code, code);
	ATF_REQUIRE_EQ(info->si_signo, SIGCHLD);
	ATF_REQUIRE_EQ(info->si_uid, getuid());
	ATF_REQUIRE_EQ(info->si_pid, child);
	if (WIFEXITED(info->si_status))
		ATF_REQUIRE_EQ(WEXITSTATUS(info->si_status), status);
	else if (WIFSTOPPED(info->si_status))
		ATF_REQUIRE_EQ(WSTOPSIG(info->si_status), status);
	else if (WIFSIGNALED(info->si_status))
		ATF_REQUIRE_EQ(WTERMSIG(info->si_status), status);
}