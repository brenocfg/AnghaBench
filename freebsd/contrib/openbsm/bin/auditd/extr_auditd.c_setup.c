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

/* Variables and functions */
 int /*<<< orphan*/  AUD_STATE_INIT ; 
 int /*<<< orphan*/  audit_setup () ; 
 int /*<<< orphan*/  auditd_log_err (char*,...) ; 
 scalar_t__ auditd_open_trigger (int /*<<< orphan*/ ) ; 
 int auditd_prevent_audit () ; 
 int /*<<< orphan*/  auditd_set_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auditd_strerror (int) ; 
 int /*<<< orphan*/  fail_exit () ; 
 int /*<<< orphan*/  launchd_flag ; 

__attribute__((used)) static void
setup(void)
{
	int err;

	if (auditd_open_trigger(launchd_flag) < 0) {
		auditd_log_err("Error opening trigger messaging mechanism");
		fail_exit();
	}

	/*
	 * To prevent event feedback cycles and avoid auditd becoming
	 * stalled if auditing is suspended, auditd and its children run
	 * without their events being audited.  We allow the uid, tid, and
	 * mask fields to be implicitly set to zero, but do set the pid.  We
	 * run this after opening the trigger device to avoid configuring
	 * audit state without audit present in the system.
	 */
	err = auditd_prevent_audit();
	if (err) {
		auditd_log_err("auditd_prevent_audit() %s: %m",
		    auditd_strerror(err));
		fail_exit();
	}

	/*
	 * Make sure auditd auditing state is correct.
	 */
	auditd_set_state(AUD_STATE_INIT);

	/*
	 * If under launchd, don't start auditing.  Wait for a trigger to
	 * do so.
	 */
	if (!launchd_flag)
		audit_setup();
}