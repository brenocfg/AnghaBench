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
struct TYPE_4__ {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_3__ {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct itimerval {TYPE_2__ it_interval; TYPE_1__ it_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  MSG_INTERVAL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  current_state ; 
 int /*<<< orphan*/  disp_msg ; 
 int /*<<< orphan*/  message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
start_msgs(void)
{
	struct itimerval itimer;

	message(current_state);
	signal(SIGALRM, disp_msg);
	itimer.it_value.tv_sec = itimer.it_interval.tv_sec = MSG_INTERVAL;
	itimer.it_value.tv_usec = itimer.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &itimer, (struct itimerval *)0);
}