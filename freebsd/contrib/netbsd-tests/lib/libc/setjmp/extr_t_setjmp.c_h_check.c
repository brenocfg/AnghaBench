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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  sigjmp_buf ;
typedef  int /*<<< orphan*/  jmp_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*) ; 
 int /*<<< orphan*/  REQUIRE_ERRNO (int) ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int TEST_SETJMP ; 
 int TEST_SIGSETJMP_NOSAVE ; 
 int TEST_SIGSETJMP_SAVE ; 
 int TEST_U_SETJMP ; 
 int /*<<< orphan*/  _longjmp (int /*<<< orphan*/ ,int) ; 
 int _setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aborthandler ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_pass () ; 
 int expectsignal ; 
 int getpid () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sigsetjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
h_check(int test)
{
	struct sigaction sa;
	jmp_buf jb;
	sigjmp_buf sjb;
	sigset_t ss;
	int i, x;

	i = getpid();

	if (test == TEST_SETJMP || test == TEST_SIGSETJMP_SAVE)
		expectsignal = 0;
	else if (test == TEST_U_SETJMP || test == TEST_SIGSETJMP_NOSAVE)
		expectsignal = 1;
	else
		atf_tc_fail("unknown test");

	sa.sa_handler = aborthandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	REQUIRE_ERRNO(sigaction(SIGABRT, &sa, NULL) != -1);
	REQUIRE_ERRNO(sigemptyset(&ss) != -1);
	REQUIRE_ERRNO(sigaddset(&ss, SIGABRT) != -1);
	REQUIRE_ERRNO(sigprocmask(SIG_BLOCK, &ss, NULL) != -1);

	if (test == TEST_SETJMP)
		x = setjmp(jb);
	else if (test == TEST_U_SETJMP)
		x = _setjmp(jb);
	else 
		x = sigsetjmp(sjb, !expectsignal);

	if (x != 0) {
		ATF_REQUIRE_MSG(x == i, "setjmp returned wrong value");
		kill(i, SIGABRT);
		ATF_REQUIRE_MSG(!expectsignal, "kill(SIGABRT) failed");
		atf_tc_pass();
	}

	REQUIRE_ERRNO(sigprocmask(SIG_UNBLOCK, &ss, NULL) != -1);

	if (test == TEST_SETJMP)
		longjmp(jb, i);
	else if (test == TEST_U_SETJMP)
		_longjmp(jb, i);
	else 
		siglongjmp(sjb, i);

	atf_tc_fail("jmp failed");
}