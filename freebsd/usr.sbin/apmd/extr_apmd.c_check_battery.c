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
struct battery_watch_event {int direction; scalar_t__ type; int level; int /*<<< orphan*/  cmdlist; scalar_t__ done; struct battery_watch_event* next; } ;
struct apm_info {int ai_batt_time; scalar_t__ ai_batt_life; } ;

/* Variables and functions */
 int AC_POWER_STATE ; 
 int /*<<< orphan*/  APMIO_GETINFO ; 
 int BATTERY_CHARGING ; 
 scalar_t__ BATTERY_MINUTES ; 
 scalar_t__ BATTERY_PERCENT ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 size_t PMEV_POWERSTATECHANGE ; 
 int /*<<< orphan*/  apmnorm_fd ; 
 struct battery_watch_event* battery_watch_list ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * events ; 
 int exec_event_cmd (int /*<<< orphan*/ *) ; 
 int exec_run_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct apm_info*) ; 
 scalar_t__ soft_power_state_change ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 scalar_t__ verbose ; 

void
check_battery(void)
{

	static int first_time=1, last_state;
	int status;

	struct apm_info pw_info;
	struct battery_watch_event *p;

	/* If we don't care, don't bother */
	if (battery_watch_list == NULL)
		return;

	if (first_time) {
		if ( ioctl(apmnorm_fd, APMIO_GETINFO, &pw_info) < 0)
			err(1, "cannot check battery state.");
/*
 * This next statement isn't entirely true. The spec does not tie AC
 * line state to battery charging or not, but this is a bit lazier to do.
 */
		last_state = AC_POWER_STATE;
		first_time = 0;
		return; /* We can't process events, we have no baseline */
	}

	/*
	 * XXX - should we do this a bunch of times and perform some sort
	 * of smoothing or correction?
	 */
	if ( ioctl(apmnorm_fd, APMIO_GETINFO, &pw_info) < 0)
		err(1, "cannot check battery state.");

	/*
	 * If we're not in the state now that we were in last time,
	 * then it's a transition, which means we must clean out
	 * the event-caught state.
	 */
	if (last_state != AC_POWER_STATE) {
		if (soft_power_state_change && fork() == 0) {
			status = exec_event_cmd(&events[PMEV_POWERSTATECHANGE]);
			exit(status);
		}
		last_state = AC_POWER_STATE;
		for (p = battery_watch_list ; p!=NULL ; p = p -> next)
			p->done = 0;
	}
	for (p = battery_watch_list ; p != NULL ; p = p -> next)
		if (p -> direction == AC_POWER_STATE &&
			!(p -> done) &&
			((p -> type == BATTERY_PERCENT && 
				p -> level == (int)pw_info.ai_batt_life) ||
			(p -> type == BATTERY_MINUTES &&
				p -> level == (pw_info.ai_batt_time / 60)))) {
			p -> done++;
			if (verbose)
				syslog(LOG_NOTICE, "Caught battery event: %s, %d%s",
					(p -> direction == BATTERY_CHARGING)?"charging":"discharging",
					p -> level,
					(p -> type == BATTERY_PERCENT)?"%":" minutes");
			if (fork() == 0) {
				status = exec_run_cmd(p -> cmdlist);
				exit(status);
			}
		}
}