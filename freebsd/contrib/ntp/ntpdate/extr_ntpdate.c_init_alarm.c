#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_12__ {int tv_usec; scalar_t__ tv_sec; } ;
struct itimerval {TYPE_4__ it_value; TYPE_3__ it_interval; } ;
struct TYPE_11__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_10__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct itimerspec {TYPE_2__ it_value; TYPE_1__ it_interval; } ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int /*<<< orphan*/  wPeriodMax; int /*<<< orphan*/  wPeriodMin; } ;
struct TYPE_15__ {int PrivilegeCount; TYPE_5__* Privileges; } ;
struct TYPE_14__ {int /*<<< orphan*/  Attributes; int /*<<< orphan*/  Luid; } ;
typedef  TYPE_6__ TOKEN_PRIVILEGES ;
typedef  TYPE_7__ TIMECAPS ;
typedef  int /*<<< orphan*/  PTOKEN_PRIVILEGES ;
typedef  int /*<<< orphan*/  LPTIMECALLBACK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustTokenPrivileges (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int ERROR ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LookupPrivilegeValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenProcessToken (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SE_PRIVILEGE_ENABLED ; 
 int /*<<< orphan*/  SE_SYSTEMTIME_NAME ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  TARGET_RESOLUTION ; 
 scalar_t__ TIMERR_NOERROR ; 
 int TIMER_HZ ; 
 int /*<<< orphan*/  TIME_PERIODIC ; 
 int TOKEN_ADJUST_PRIVILEGES ; 
 int TOKEN_QUERY ; 
 int /*<<< orphan*/  _tzset () ; 
 scalar_t__ alarm_flag ; 
 scalar_t__ alarming ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callTimeEndPeriod ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ntpdate_timerid ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_no_reset (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  simple_query ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  timeBeginPeriod (int /*<<< orphan*/ ) ; 
 scalar_t__ timeGetDevCaps (TYPE_7__*,int) ; 
 scalar_t__ timeSetEvent (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int timer_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wTimerRes ; 

__attribute__((used)) static void
init_alarm(void)
{
#ifndef SYS_WINNT
# ifdef HAVE_TIMER_CREATE
	struct itimerspec its;
# else
	struct itimerval itv;
# endif
#else	/* SYS_WINNT follows */
	TIMECAPS tc;
	UINT wTimerID;
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	DWORD dwUser = 0;
#endif /* SYS_WINNT */

	alarm_flag = 0;

#ifndef SYS_WINNT
# ifdef HAVE_TIMER_CREATE
	alarm_flag = 0;
	/* this code was put in as setitimer() is non existant this us the
	 * POSIX "equivalents" setup - casey
	 */
	/* ntpdate_timerid is global - so we can kill timer later */
	if (timer_create (CLOCK_REALTIME, NULL, &ntpdate_timerid) ==
#  ifdef SYS_VXWORKS
		ERROR
#  else
		-1
#  endif
		)
	{
		fprintf (stderr, "init_alarm(): timer_create (...) FAILED\n");
		return;
	}

	/*	TIMER_HZ = (5)
	 * Set up the alarm interrupt.	The first comes 1/(2*TIMER_HZ)
	 * seconds from now and they continue on every 1/TIMER_HZ seconds.
	 */
	signal_no_reset(SIGALRM, alarming);
	its.it_interval.tv_sec = 0;
	its.it_value.tv_sec = 0;
	its.it_interval.tv_nsec = 1000000000/TIMER_HZ;
	its.it_value.tv_nsec = 1000000000/(TIMER_HZ<<1);
	timer_settime(ntpdate_timerid, 0 /* !TIMER_ABSTIME */, &its, NULL);
# else	/* !HAVE_TIMER_CREATE follows */
	/*
	 * Set up the alarm interrupt.	The first comes 1/(2*TIMER_HZ)
	 * seconds from now and they continue on every 1/TIMER_HZ seconds.
	 */
	signal_no_reset(SIGALRM, alarming);
	itv.it_interval.tv_sec = 0;
	itv.it_value.tv_sec = 0;
	itv.it_interval.tv_usec = 1000000/TIMER_HZ;
	itv.it_value.tv_usec = 1000000/(TIMER_HZ<<1);

	setitimer(ITIMER_REAL, &itv, NULL);
# endif	/* !HAVE_TIMER_CREATE */
#else	/* SYS_WINNT follows */
	_tzset();

	if (!simple_query && !debug) {
		/*
		 * Get privileges needed for fiddling with the clock
		 */

		/* get the current process token handle */
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
			msyslog(LOG_ERR, "OpenProcessToken failed: %m");
			exit(1);
		}
		/* get the LUID for system-time privilege. */
		LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &tkp.Privileges[0].Luid);
		tkp.PrivilegeCount = 1;		/* one privilege to set */
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		/* get set-time privilege for this process. */
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES) NULL, 0);
		/* cannot test return value of AdjustTokenPrivileges. */
		if (GetLastError() != ERROR_SUCCESS)
			msyslog(LOG_ERR, "AdjustTokenPrivileges failed: %m");
	}

	/*
	 * Set up timer interrupts for every 2**EVENT_TIMEOUT seconds
	 * Under Win/NT, expiry of timer interval leads to invocation
	 * of a callback function (on a different thread) rather than
	 * generating an alarm signal
	 */

	/* determine max and min resolution supported */
	if(timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
		msyslog(LOG_ERR, "timeGetDevCaps failed: %m");
		exit(1);
	}
	wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
	/* establish the minimum timer resolution that we'll use */
	timeBeginPeriod(wTimerRes);
	atexit(callTimeEndPeriod);

	/* start the timer event */
	wTimerID = timeSetEvent(
		(UINT) (1000/TIMER_HZ),		/* Delay */
		wTimerRes,			/* Resolution */
		(LPTIMECALLBACK) alarming,	/* Callback function */
		(DWORD) dwUser,			/* User data */
		TIME_PERIODIC);			/* Event type (periodic) */
	if (wTimerID == 0) {
		msyslog(LOG_ERR, "timeSetEvent failed: %m");
		exit(1);
	}
#endif /* SYS_WINNT */
}