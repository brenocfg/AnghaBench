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
typedef  int u_int ;
struct TYPE_2__ {int tv_sec; int tv_usec; } ;
struct itimerval {TYPE_1__ it_value; } ;
typedef  int semid_t ;
typedef  int /*<<< orphan*/  it ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  alarm_handler ; 
 int alarm_handler_installed ; 
 int alarm_id ; 
 int /*<<< orphan*/  bzero (struct itimerval*,int) ; 
 int /*<<< orphan*/  fail_err (char*) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 scalar_t__ setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
schedule_post(semid_t id, u_int msec)
{
	struct itimerval it;

	if (!alarm_handler_installed) {
		if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
			fail_errno("signal(SIGALRM)");
			return (-1);
		}
		alarm_handler_installed = 1;
	}
	if (alarm_id != -1) {
		fail_err("ksem_post() already scheduled");
		return (-1);
	}
	alarm_id = id;
	bzero(&it, sizeof(it));
	it.it_value.tv_sec = msec / 1000;
	it.it_value.tv_usec = (msec % 1000) * 1000;
	if (setitimer(ITIMER_REAL, &it, NULL) < 0) {
		fail_errno("setitimer");
		return (-1);
	}
	return (0);
}