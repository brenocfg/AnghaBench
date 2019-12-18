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
 int ADE_HARDLIM ; 
 int ADE_SOFTLIM ; 
 int /*<<< orphan*/  audit_warn_allhard () ; 
 int /*<<< orphan*/  audit_warn_allsoft () ; 
 int /*<<< orphan*/  audit_warn_expired ; 
 int /*<<< orphan*/  audit_warn_hard ; 
 int /*<<< orphan*/  audit_warn_soft ; 
 int auditd_expire_trails (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auditd_log_err (char*,int /*<<< orphan*/ ) ; 
 int auditd_read_dirs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auditd_strerror (int) ; 
 int swap_audit_file () ; 

__attribute__((used)) static int
do_trail_file(void)
{
	int err;

	/*
	 * First, refresh the list of audit log directories.
	 */
	err = auditd_read_dirs(audit_warn_soft, audit_warn_hard);
	if (err) {
		auditd_log_err("auditd_read_dirs(): %s",
		    auditd_strerror(err));
		if (err == ADE_HARDLIM)
			audit_warn_allhard();
		if (err != ADE_SOFTLIM)
			return (-1);
		else
			audit_warn_allsoft();
			/* continue on with soft limit error */
	}

	/*
	 * Create a new file and swap with the one being used in kernel.
	 */
	if (swap_audit_file() == -1) {
		/*
		 * XXX Faulty directory listing? - user should be given
		 * XXX an opportunity to change the audit_control file
		 * XXX switch to a reduced mode of auditing?
		 */
		return (-1);
	}

	/*
	 * Finally, see if there are any trail files to expire.
	 */
	err = auditd_expire_trails(audit_warn_expired);
	if (err)
		auditd_log_err("auditd_expire_trails(): %s",
		    auditd_strerror(err));

	return (0);
}