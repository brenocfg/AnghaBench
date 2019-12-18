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
struct itimerval {int /*<<< orphan*/  it_interval; int /*<<< orphan*/  it_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timerclear (int /*<<< orphan*/ *) ; 

void
end_msgs(void)
{
	struct itimerval itimer;

	timerclear(&itimer.it_value);
	timerclear(&itimer.it_interval);
	setitimer(ITIMER_REAL, &itimer, (struct itimerval *)0);
	signal(SIGALRM, SIG_DFL);
}