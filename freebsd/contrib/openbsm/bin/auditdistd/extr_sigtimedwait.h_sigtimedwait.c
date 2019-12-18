#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {scalar_t__ tv_sec; int tv_nsec; } ;
struct TYPE_2__ {scalar_t__ tv_sec; int tv_usec; } ;
struct itimerval {TYPE_1__ it_value; TYPE_1__ it_interval; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  int /*<<< orphan*/  mask ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
 int SIGALRM ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int errno ; 
 scalar_t__ setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 scalar_t__ sigaddset (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sigwait (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  timerclear (TYPE_1__*) ; 

__attribute__((used)) static int
sigtimedwait(const sigset_t *set, siginfo_t *info,
    const struct timespec *timeout)
{
	struct itimerval it;
	sigset_t mask;
	int error, signo;

	PJDLOG_ASSERT(info == NULL);

	PJDLOG_VERIFY(sigemptyset(&mask) == 0);
	PJDLOG_VERIFY(sigaddset(&mask, SIGALRM) == 0);
	PJDLOG_VERIFY(sigprocmask(SIG_BLOCK, &mask, NULL) == 0);

	timerclear(&it.it_interval);
	it.it_value.tv_sec = timeout->tv_sec;
	it.it_value.tv_usec = timeout->tv_nsec / 1000;
	if (it.it_value.tv_sec == 0 && it.it_value.tv_usec == 0)
		it.it_value.tv_usec = 1;
	PJDLOG_VERIFY(setitimer(ITIMER_REAL, &it, NULL) == 0);

	bcopy(set, &mask, sizeof(mask));
	PJDLOG_VERIFY(sigaddset(&mask, SIGALRM) == 0);

	PJDLOG_VERIFY(sigwait(&mask, &signo) == 0);
	error = errno;

	timerclear(&it.it_interval);
	timerclear(&it.it_value);
	PJDLOG_VERIFY(setitimer(ITIMER_REAL, &it, NULL) == 0);

	PJDLOG_VERIFY(sigemptyset(&mask) == 0);
	PJDLOG_VERIFY(sigaddset(&mask, SIGALRM) == 0);
	PJDLOG_VERIFY(sigprocmask(SIG_UNBLOCK, &mask, NULL) == 0);

	if (signo == SIGALRM) {
		errno = EAGAIN;
		signo = -1;
	} else {
		errno = error;
	}

	return (signo);
}