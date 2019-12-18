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
struct kclock {int /*<<< orphan*/ * event_hook; int /*<<< orphan*/  timer_gettime; int /*<<< orphan*/  timer_settime; int /*<<< orphan*/  timer_delete; int /*<<< orphan*/  timer_create; } ;
struct itimer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  CTL_P1003_1B_DELAYTIMER_MAX ; 
 int /*<<< orphan*/  CTL_P1003_1B_TIMERS ; 
 int /*<<< orphan*/  CTL_P1003_1B_TIMER_MAX ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 long INT_MAX ; 
 scalar_t__ ITIMER_EV_EXEC ; 
 scalar_t__ ITIMER_EV_EXIT ; 
 long TIMER_MAX ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  itimer_fini ; 
 int /*<<< orphan*/  itimer_init ; 
 int /*<<< orphan*/  itimer_zone ; 
 int /*<<< orphan*/  itimers_event_hook_exec ; 
 int /*<<< orphan*/  itimers_event_hook_exit ; 
 int /*<<< orphan*/  p31b_setcfg (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  process_exec ; 
 int /*<<< orphan*/  process_exit ; 
 int /*<<< orphan*/  realtimer_create ; 
 int /*<<< orphan*/  realtimer_delete ; 
 int /*<<< orphan*/  realtimer_gettime ; 
 int /*<<< orphan*/  realtimer_settime ; 
 int /*<<< orphan*/  register_posix_clock (int /*<<< orphan*/ ,struct kclock*) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
itimer_start(void)
{
	struct kclock rt_clock = {
		.timer_create  = realtimer_create,
		.timer_delete  = realtimer_delete,
		.timer_settime = realtimer_settime,
		.timer_gettime = realtimer_gettime,
		.event_hook    = NULL
	};

	itimer_zone = uma_zcreate("itimer", sizeof(struct itimer),
		NULL, NULL, itimer_init, itimer_fini, UMA_ALIGN_PTR, 0);
	register_posix_clock(CLOCK_REALTIME,  &rt_clock);
	register_posix_clock(CLOCK_MONOTONIC, &rt_clock);
	p31b_setcfg(CTL_P1003_1B_TIMERS, 200112L);
	p31b_setcfg(CTL_P1003_1B_DELAYTIMER_MAX, INT_MAX);
	p31b_setcfg(CTL_P1003_1B_TIMER_MAX, TIMER_MAX);
	EVENTHANDLER_REGISTER(process_exit, itimers_event_hook_exit,
		(void *)ITIMER_EV_EXIT, EVENTHANDLER_PRI_ANY);
	EVENTHANDLER_REGISTER(process_exec, itimers_event_hook_exec,
		(void *)ITIMER_EV_EXEC, EVENTHANDLER_PRI_ANY);
}