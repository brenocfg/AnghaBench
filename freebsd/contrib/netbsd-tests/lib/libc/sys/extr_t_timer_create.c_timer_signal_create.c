#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_3__ {scalar_t__* sival_ptr; } ;
struct sigevent {TYPE_2__ it_value; int /*<<< orphan*/  sigev_notify; TYPE_1__ sigev_value; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_flags; } ;
struct sigaction {TYPE_2__ it_value; int /*<<< orphan*/  sigev_notify; TYPE_1__ sigev_value; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_flags; } ;
struct itimerspec {TYPE_2__ it_value; int /*<<< orphan*/  sigev_notify; TYPE_1__ sigev_value; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_flags; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGEV_SIGNAL ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int fail ; 
 int /*<<< orphan*/  memset (struct sigevent*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigevent*,int /*<<< orphan*/ *) ; 
 scalar_t__ sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ t ; 
 scalar_t__ timer_create (int /*<<< orphan*/ ,struct sigevent*,scalar_t__*) ; 
 scalar_t__ timer_delete (scalar_t__) ; 
 scalar_t__ timer_settime (scalar_t__,int /*<<< orphan*/ ,struct sigevent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_signal_handler ; 

__attribute__((used)) static void
timer_signal_create(clockid_t cid, bool expire)
{
	struct itimerspec tim;
	struct sigaction act;
	struct sigevent evt;
	sigset_t set;

	t = 0;
	fail = true;

	(void)memset(&evt, 0, sizeof(struct sigevent));
	(void)memset(&act, 0, sizeof(struct sigaction));
	(void)memset(&tim, 0, sizeof(struct itimerspec));

	/*
	 * Set handler.
	 */
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = timer_signal_handler;

	ATF_REQUIRE(sigemptyset(&set) == 0);
	ATF_REQUIRE(sigemptyset(&act.sa_mask) == 0);

	/*
	 * Block SIGALRM while configuring the timer.
	 */
	ATF_REQUIRE(sigaction(SIGALRM, &act, NULL) == 0);
	ATF_REQUIRE(sigaddset(&set, SIGALRM) == 0);
	ATF_REQUIRE(sigprocmask(SIG_SETMASK, &set, NULL) == 0);

	/*
	 * Create the timer (SIGEV_SIGNAL).
	 */
	evt.sigev_signo = SIGALRM;
	evt.sigev_value.sival_ptr = &t;
	evt.sigev_notify = SIGEV_SIGNAL;

	ATF_REQUIRE(timer_create(cid, &evt, &t) == 0);

	/*
	 * Start the timer. After this, unblock the signal.
	 */
	tim.it_value.tv_sec = expire ? 5 : 1;
	tim.it_value.tv_nsec = 0;

	ATF_REQUIRE(timer_settime(t, 0, &tim, NULL) == 0);

	(void)sigprocmask(SIG_UNBLOCK, &set, NULL);
	(void)sleep(2);

	if (expire) {
		if (!fail)
			atf_tc_fail("timer fired too soon");
	} else {
		if (fail)
			atf_tc_fail("timer failed to fire");
	}

	ATF_REQUIRE(timer_delete(t) == 0);
}