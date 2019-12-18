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
typedef  int time_t ;
struct timezone {int dummy; } ;
struct timeval {scalar_t__ tv_sec; } ;

/* Variables and functions */
#define  AUDIT_TRIGGER_CLOSE_AND_DIE 135 
#define  AUDIT_TRIGGER_EXPIRE_TRAILS 134 
#define  AUDIT_TRIGGER_INITIALIZE 133 
#define  AUDIT_TRIGGER_LOW_SPACE 132 
#define  AUDIT_TRIGGER_NO_SPACE 131 
#define  AUDIT_TRIGGER_READ_FILE 130 
#define  AUDIT_TRIGGER_ROTATE_KERNEL 129 
#define  AUDIT_TRIGGER_ROTATE_USER 128 
 int AUD_STATE_DISABLED ; 
 int AUD_STATE_ENABLED ; 
 int DUPLICATE_INTERVAL ; 
 int /*<<< orphan*/  audit_setup () ; 
 int /*<<< orphan*/  audit_warn_expired ; 
 int auditd_config_controls () ; 
 int auditd_expire_trails (int /*<<< orphan*/ ) ; 
 int auditd_get_state () ; 
 int /*<<< orphan*/  auditd_log_err (char*,...) ; 
 int /*<<< orphan*/  auditd_log_info (char*,...) ; 
 int /*<<< orphan*/  auditd_log_notice (char*) ; 
 int auditd_strerror (int) ; 
 int close_all () ; 
 int do_trail_file () ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ gettimeofday (struct timeval*,struct timezone*) ; 
 int /*<<< orphan*/  launchd_flag ; 

void
auditd_handle_trigger(int trigger)
{
	static int last_trigger, last_warning;
	static time_t last_time;
	struct timeval ts;
	struct timezone tzp;
	time_t tt;
	int au_state;
	int err = 0;

	/*
	 * Suppress duplicate messages from the kernel within the specified
	 * interval.
	 */
	if (gettimeofday(&ts, &tzp) == 0) {
		tt = (time_t)ts.tv_sec;
		switch (trigger) {
		case AUDIT_TRIGGER_LOW_SPACE:
		case AUDIT_TRIGGER_NO_SPACE:
			/*
			 * Triggers we can suppress.  Of course, we also need
			 * to rate limit the warnings, so apply the same
			 * interval limit on syslog messages.
			 */
			if ((trigger == last_trigger) &&
			    (tt < (last_time + DUPLICATE_INTERVAL))) {
				if (tt >= (last_warning + DUPLICATE_INTERVAL))
					auditd_log_info(
					    "Suppressing duplicate trigger %d",
					    trigger);
				return;
			}
			last_warning = tt;
			break;

		case AUDIT_TRIGGER_ROTATE_KERNEL:
		case AUDIT_TRIGGER_ROTATE_USER:
		case AUDIT_TRIGGER_READ_FILE:
		case AUDIT_TRIGGER_CLOSE_AND_DIE:
		case AUDIT_TRIGGER_INITIALIZE:
			/*
			 * Triggers that we cannot suppress.
			 */
			break;
		}

		/*
		 * Only update last_trigger after aborting due to a duplicate
		 * trigger, not before, or we will never allow that trigger
		 * again.
		 */
		last_trigger = trigger;
		last_time = tt;
	}

	au_state = auditd_get_state();

	/*
	 * Message processing is done here.
	 */
	switch(trigger) {
	case AUDIT_TRIGGER_LOW_SPACE:
		auditd_log_notice("Got low space trigger");
		if (do_trail_file() == -1)
			auditd_log_err("Error swapping audit file");
		break;

	case AUDIT_TRIGGER_NO_SPACE:
		auditd_log_notice("Got no space trigger");
		if (do_trail_file() == -1)
			auditd_log_err("Error swapping audit file");
		break;

	case AUDIT_TRIGGER_ROTATE_KERNEL:
	case AUDIT_TRIGGER_ROTATE_USER:
		auditd_log_info("Got open new trigger from %s", trigger ==
		    AUDIT_TRIGGER_ROTATE_KERNEL ? "kernel" : "user");
		if (au_state == AUD_STATE_ENABLED && do_trail_file() == -1)
			auditd_log_err("Error swapping audit file");
		break;

	case AUDIT_TRIGGER_READ_FILE:
		auditd_log_info("Got read file trigger");
		if (au_state == AUD_STATE_ENABLED) {
			if (auditd_config_controls() == -1)
				auditd_log_err("Error setting audit controls");
			else if (do_trail_file() == -1)
				auditd_log_err("Error swapping audit file");
		}
		break;

	case AUDIT_TRIGGER_CLOSE_AND_DIE:
		auditd_log_info("Got close and die trigger");
		if (au_state == AUD_STATE_ENABLED)
			err = close_all();
		/*
		 * Running under launchd don't exit.  Wait for launchd to
		 * send SIGTERM.
		 */
		if (!launchd_flag) {
			auditd_log_info("auditd exiting.");
			exit (err);
		}
		break;

	case AUDIT_TRIGGER_INITIALIZE:
		auditd_log_info("Got audit initialize trigger");
		if (au_state == AUD_STATE_DISABLED)
			audit_setup();
		break;

	case AUDIT_TRIGGER_EXPIRE_TRAILS:
		auditd_log_info("Got audit expire trails trigger");
		err = auditd_expire_trails(audit_warn_expired);
		if (err)
			auditd_log_err("auditd_expire_trails(): %s",
			    auditd_strerror(err));
		break;

	default:
		auditd_log_err("Got unknown trigger %d", trigger);
		break;
	}
}