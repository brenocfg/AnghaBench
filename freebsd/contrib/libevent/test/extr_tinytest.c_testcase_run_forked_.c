#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct testgroup_t {char* prefix; } ;
struct testcase_t {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  info ;
typedef  enum outcome { ____Placeholder_outcome } outcome ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_6__ {int cb; int /*<<< orphan*/  hThread; int /*<<< orphan*/  hProcess; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_1__ PROCESS_INFORMATION ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int CreateProcessA (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int FAIL ; 
 int /*<<< orphan*/  GetExitCodeProcess (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LONGEST_TEST_NAME ; 
 scalar_t__ MAGIC_EXITCODE ; 
 int OK ; 
 int SKIP ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 char* commandname ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  in_tinytest_main ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ opt_verbosity ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int testcase_run_bare_ (struct testcase_t const*) ; 
 char* verbosity_flag ; 
 int /*<<< orphan*/  vproc_transaction_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,char*,int) ; 

__attribute__((used)) static enum outcome
testcase_run_forked_(const struct testgroup_t *group,
		     const struct testcase_t *testcase)
{
#ifdef _WIN32
	/* Fork? On Win32?  How primitive!  We'll do what the smart kids do:
	   we'll invoke our own exe (whose name we recall from the command
	   line) with a command line that tells it to run just the test we
	   want, and this time without forking.

	   (No, threads aren't an option.  The whole point of forking is to
	   share no state between tests.)
	 */
	int ok;
	char buffer[LONGEST_TEST_NAME+256];
	STARTUPINFOA si;
	PROCESS_INFORMATION info;
	DWORD exitcode;

	if (!in_tinytest_main) {
		printf("\nERROR.  On Windows, testcase_run_forked_ must be"
		       " called from within tinytest_main.\n");
		abort();
	}
	if (opt_verbosity>0)
		printf("[forking] ");

	snprintf(buffer, sizeof(buffer), "%s --RUNNING-FORKED %s %s%s",
		 commandname, verbosity_flag, group->prefix, testcase->name);

	memset(&si, 0, sizeof(si));
	memset(&info, 0, sizeof(info));
	si.cb = sizeof(si);

	ok = CreateProcessA(commandname, buffer, NULL, NULL, 0,
			   0, NULL, NULL, &si, &info);
	if (!ok) {
		printf("CreateProcess failed!\n");
		return 0;
	}
	WaitForSingleObject(info.hProcess, INFINITE);
	GetExitCodeProcess(info.hProcess, &exitcode);
	CloseHandle(info.hProcess);
	CloseHandle(info.hThread);
	if (exitcode == 0)
		return OK;
	else if (exitcode == MAGIC_EXITCODE)
		return SKIP;
	else
		return FAIL;
#else
	int outcome_pipe[2];
	pid_t pid;
	(void)group;

	if (pipe(outcome_pipe))
		perror("opening pipe");

	if (opt_verbosity>0)
		printf("[forking] ");
	pid = fork();
#ifdef FORK_BREAKS_GCOV
	vproc_transaction_begin(0);
#endif
	if (!pid) {
		/* child. */
		int test_r, write_r;
		char b[1];
		close(outcome_pipe[0]);
		test_r = testcase_run_bare_(testcase);
		assert(0<=(int)test_r && (int)test_r<=2);
		b[0] = "NYS"[test_r];
		write_r = (int)write(outcome_pipe[1], b, 1);
		if (write_r != 1) {
			perror("write outcome to pipe");
			exit(1);
		}
		exit(0);
		return FAIL; /* unreachable */
	} else {
		/* parent */
		int status, r;
		char b[1];
		/* Close this now, so that if the other side closes it,
		 * our read fails. */
		close(outcome_pipe[1]);
		r = (int)read(outcome_pipe[0], b, 1);
		if (r == 0) {
			printf("[Lost connection!] ");
			return 0;
		} else if (r != 1) {
			perror("read outcome from pipe");
		}
		waitpid(pid, &status, 0);
		close(outcome_pipe[0]);
		return b[0]=='Y' ? OK : (b[0]=='S' ? SKIP : FAIL);
	}
#endif
}