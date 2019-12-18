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
typedef  int /*<<< orphan*/  setmask ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  cpusetid_t ;
typedef  int /*<<< orphan*/  cpuset_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  CHILD_REQUIRE (int) ; 
 int /*<<< orphan*/  CPU_LEVEL_CPUSET ; 
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_WHICH_CPUSET ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROC_REAP_ACQUIRE ; 
 int /*<<< orphan*/  PT_CONTINUE ; 
 int /*<<< orphan*/  P_PID ; 
 scalar_t__ SIGKILL ; 
 scalar_t__ SIGSTOP ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 scalar_t__ WTERMSIG (int) ; 
 scalar_t__ cpuset (int /*<<< orphan*/ *) ; 
 scalar_t__ cpuset_setaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ procctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raise (scalar_t__) ; 
 int /*<<< orphan*/  raise_sigstop_thread ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  sleep_thread ; 
 int /*<<< orphan*/  trace_me () ; 
 scalar_t__ wait (int*) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
terminate_with_pending_sigstop(bool sigstop_from_main_thread)
{
	pid_t fpid, wpid;
	int status, i;
	cpuset_t setmask;
	cpusetid_t setid;
	pthread_t t;

	/*
	 * Become the reaper for this process tree. We need to be able to check
	 * that both child and grandchild have died.
	 */
	ATF_REQUIRE(procctl(P_PID, getpid(), PROC_REAP_ACQUIRE, NULL) == 0);

	fpid = fork();
	ATF_REQUIRE(fpid >= 0);
	if (fpid == 0) {
		fpid = fork();
		CHILD_REQUIRE(fpid >= 0);
		if (fpid == 0) {
			trace_me();

			/* Pin to CPU 0 to serialize thread execution. */
			CPU_ZERO(&setmask);
			CPU_SET(0, &setmask);
			CHILD_REQUIRE(cpuset(&setid) == 0);
			CHILD_REQUIRE(cpuset_setaffinity(CPU_LEVEL_CPUSET,
			    CPU_WHICH_CPUSET, setid,
			    sizeof(setmask), &setmask) == 0);

			if (sigstop_from_main_thread) {
				/*
				 * We expect the SIGKILL sent when our parent
				 * dies to be delivered to the new thread.
				 * Raise the SIGSTOP in this thread so the
				 * threads compete.
				 */
				CHILD_REQUIRE(pthread_create(&t, NULL,
				    sleep_thread, NULL) == 0);
				raise(SIGSTOP);
			} else {
				/*
				 * We expect the SIGKILL to be delivered to
				 * this thread. After creating the new thread,
				 * just get off the CPU so the other thread can
				 * raise the SIGSTOP.
				 */
				CHILD_REQUIRE(pthread_create(&t, NULL,
				    raise_sigstop_thread, NULL) == 0);
				sleep(60);
			}

			exit(0);
		}
		/* First stop is trace_me() immediately after fork. */
		wpid = waitpid(fpid, &status, 0);
		CHILD_REQUIRE(wpid == fpid);
		CHILD_REQUIRE(WIFSTOPPED(status));
		CHILD_REQUIRE(WSTOPSIG(status) == SIGSTOP);

		CHILD_REQUIRE(ptrace(PT_CONTINUE, fpid, (caddr_t)1, 0) == 0);

		/* Second stop is from the raise(SIGSTOP). */
		wpid = waitpid(fpid, &status, 0);
		CHILD_REQUIRE(wpid == fpid);
		CHILD_REQUIRE(WIFSTOPPED(status));
		CHILD_REQUIRE(WSTOPSIG(status) == SIGSTOP);

		/*
		 * Terminate tracing process without detaching. Our child
		 * should be killed.
		 */
		exit(0);
	}

	/*
	 * We should get a normal exit from our immediate child and a SIGKILL
	 * exit from our grandchild. The latter case is the interesting one.
	 * Our grandchild should not have stopped due to the SIGSTOP that was
	 * left dangling when its parent died.
	 */
	for (i = 0; i < 2; ++i) {
		wpid = wait(&status);
		if (wpid == fpid)
			ATF_REQUIRE(WIFEXITED(status) &&
			    WEXITSTATUS(status) == 0);
		else
			ATF_REQUIRE(WIFSIGNALED(status) &&
			    WTERMSIG(status) == SIGKILL);
	}
}