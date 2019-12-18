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
 int /*<<< orphan*/  AUE_audit_startup ; 
 scalar_t__ auditd_config_controls () ; 
 int auditd_gen_record (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auditd_log_debug (char*) ; 
 int /*<<< orphan*/  auditd_log_err (char*,...) ; 
 int /*<<< orphan*/  auditd_log_info (char*) ; 
 int auditd_set_dist () ; 
 int /*<<< orphan*/  auditd_strerror (int) ; 
 int do_trail_file () ; 
 int /*<<< orphan*/  fail_exit () ; 

__attribute__((used)) static void
audit_setup(void)
{
	int err;

	/* Configure trail files distribution. */
	err = auditd_set_dist();
	if (err) {
		auditd_log_err("auditd_set_dist() %s: %m",
		    auditd_strerror(err));
	} else
		auditd_log_debug("Configured trail files distribution.");

	if (do_trail_file() == -1) {
		auditd_log_err("Error creating audit trail file");
		fail_exit();
	}

	/* Generate an audit record. */
	err = auditd_gen_record(AUE_audit_startup, NULL);
	if (err)
		auditd_log_err("auditd_gen_record(AUE_audit_startup) %s: %m",
		    auditd_strerror(err));

	if (auditd_config_controls() == 0)
		auditd_log_info("Audit controls init successful");
	else
		auditd_log_err("Audit controls init failed");
}