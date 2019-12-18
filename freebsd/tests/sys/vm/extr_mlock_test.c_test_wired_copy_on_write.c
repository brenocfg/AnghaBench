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
typedef  int pid_t ;
typedef  void* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  PT_CONTINUE ; 
 int /*<<< orphan*/  PT_READ_D ; 
 int /*<<< orphan*/  PT_TRACE_ME ; 
 int /*<<< orphan*/  PT_WRITE_D ; 
 scalar_t__ SIGSTOP ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int WIFEXITED (int) ; 
 int WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int fork () ; 
 scalar_t__ mlock (void*,size_t) ; 
 scalar_t__ munlock (void*,size_t) ; 
 int ptrace (int /*<<< orphan*/ ,int,void*,int) ; 
 scalar_t__ raise (scalar_t__) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_wired_copy_on_write(void *addr, size_t len)
{
	int status, val;
	pid_t pid;

	pid = fork();
	if (pid == -1)
		atf_tc_fail("fork() failed: %s", strerror(errno));
	if (pid == 0) {
		if (mlock(addr, len) != 0)
			_exit(1);
		if (ptrace(PT_TRACE_ME, 0, NULL, 0) != 0)
			_exit(2);
		if (raise(SIGSTOP) != 0)
			_exit(3);
		if (munlock(addr, len) != 0)
			_exit(4);
		_exit(0);
	}

	ATF_REQUIRE(waitpid(pid, &status, 0) == pid);
	ATF_REQUIRE_MSG(!WIFEXITED(status),
	    "child exited with status %d", WEXITSTATUS(status));
	ATF_REQUIRE(WIFSTOPPED(status));
	ATF_REQUIRE(WSTOPSIG(status) == SIGSTOP);

	errno = 0;
	val = ptrace(PT_READ_D, pid, addr, 0);
	ATF_REQUIRE(errno == 0);
	ATF_REQUIRE(ptrace(PT_WRITE_D, pid, addr, val) == 0);
	ATF_REQUIRE(ptrace(PT_CONTINUE, pid, (caddr_t)1, 0) == 0);
	ATF_REQUIRE(waitpid(pid, &status, 0) == pid);
	ATF_REQUIRE(WIFEXITED(status));
	ATF_REQUIRE_MSG(WEXITSTATUS(status) == 0,
	    "child exited with status %d", WSTOPSIG(status));
}