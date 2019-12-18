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
struct itimerval {int dummy; } ;
typedef  int /*<<< orphan*/  it ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 scalar_t__ alarm_errno ; 
 int alarm_id ; 
 int /*<<< orphan*/  bzero (struct itimerval*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 scalar_t__ setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
check_alarm(int just_clear)
{
	struct itimerval it;

	bzero(&it, sizeof(it));
	if (just_clear) {
		setitimer(ITIMER_REAL, &it, NULL);
		alarm_errno = 0;
		alarm_id = -1;
		return (0);
	}
	if (setitimer(ITIMER_REAL, &it, NULL) < 0) {
		fail_errno("setitimer");
		return (-1);
	}
	if (alarm_errno != 0 && !just_clear) {
		errno = alarm_errno;
		fail_errno("ksem_post() (via timeout)");
		alarm_errno = 0;
		return (-1);
	}
	alarm_id = -1;
	
	return (0);
}