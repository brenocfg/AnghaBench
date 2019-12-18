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
 int ADE_ACTL ; 
 int ADE_NOERR ; 
 int ADE_SOFTLIM ; 
 int /*<<< orphan*/  AUE_audit_startup ; 
 int /*<<< orphan*/  TIMESTAMP_LEN ; 
 scalar_t__ auditd_gen_record (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ auditd_new_curlink (char*) ; 
 scalar_t__ auditd_prevent_audit () ; 
 int auditd_read_dirs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auditd_set_dist () ; 
 int /*<<< orphan*/  auditd_set_evcmap () ; 
 int /*<<< orphan*/  auditd_set_fsize () ; 
 int /*<<< orphan*/  auditd_set_host () ; 
 int /*<<< orphan*/  auditd_set_minfree () ; 
 int /*<<< orphan*/  auditd_set_namask () ; 
 int /*<<< orphan*/  auditd_set_policy () ; 
 int auditd_swap_trail (char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getTSstr (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  getgid () ; 

int
audit_quick_start(void)
{
	int err;
	char *newfile = NULL;
	time_t tt;
	char TS[TIMESTAMP_LEN + 1];
	int ret = 0;

	/*
	 * Mask auditing of this process.
	 */
	if (auditd_prevent_audit() != 0)
		return (-1);

	/*
	 * Read audit_control and get log directories.
	 */
	err = auditd_read_dirs(NULL, NULL);
	if (err != ADE_NOERR && err != ADE_SOFTLIM)
		return (-1);

	/*
	 * Setup trail file distribution.
	 */
	(void) auditd_set_dist();

	/*
	 *  Create a new audit trail log.
	 */
	if (getTSstr(tt, TS, sizeof(TS)) != 0)
		return (-1);
	err = auditd_swap_trail(TS, &newfile, getgid(), NULL);
	if (err != ADE_NOERR && err != ADE_ACTL) {
		ret = -1;
		goto out;
	}

	/*
	 * Add the current symlink and recover from crash, if needed.
	 */
	if (auditd_new_curlink(newfile) != 0) {
		ret = -1;
		goto out;
	}

	/*
	 * At this point auditing has started so generate audit start-up record.
	 */
	if (auditd_gen_record(AUE_audit_startup, NULL) != 0) {
		ret = -1;
		goto out;
	}

	/*
	 *  Configure the audit controls.
	 */
	(void) auditd_set_evcmap();
	(void) auditd_set_namask();
	(void) auditd_set_policy();
	(void) auditd_set_fsize();
	(void) auditd_set_minfree();
	(void) auditd_set_host();

out:
	if (newfile != NULL)
		free(newfile);

	return (ret);
}