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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  TS ;

/* Variables and functions */
 int AUC_DISABLED ; 
 int /*<<< orphan*/  AUD_STATE_DISABLED ; 
 int /*<<< orphan*/  AUE_audit_shutdown ; 
 int /*<<< orphan*/  TIMESTAMP_LEN ; 
 int audit_set_cond (int*) ; 
 int /*<<< orphan*/  audit_warn_postsigterm () ; 
 int auditd_gen_record (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auditd_log_err (char*,...) ; 
 int /*<<< orphan*/  auditd_log_info (char*) ; 
 int /*<<< orphan*/  auditd_set_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auditd_strerror (int) ; 
 int /*<<< orphan*/  close_lastfile (char*) ; 
 scalar_t__ close_misc () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ getTSstr (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * lastfile ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
close_all(void)
{
	int err_ret = 0;
	char TS[TIMESTAMP_LEN + 1];
	int err;
	int cond;
	time_t tt;

	err = auditd_gen_record(AUE_audit_shutdown, NULL);
	if (err)
		auditd_log_err("auditd_gen_record(AUE_audit_shutdown) %s: %m",
		    auditd_strerror(err));

	/* Flush contents. */
	cond = AUC_DISABLED;
	err_ret = audit_set_cond(&cond);
	if (err_ret != 0) {
		auditd_log_err("Disabling audit failed! : %s", strerror(errno));
		err_ret = 1;
	}

	/*
	 * Updated the cached state that auditing has been disabled.
	 */
	auditd_set_state(AUD_STATE_DISABLED);

	if (getTSstr(tt, TS, sizeof(TS)) == 0)
		close_lastfile(TS);
	if (lastfile != NULL)
		free(lastfile);

	err_ret += close_misc();

	if (err_ret) {
		auditd_log_err("Could not unregister");
		audit_warn_postsigterm();
	}

	auditd_log_info("Finished");
	return (err_ret);
}