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
 scalar_t__ AUD_STATE_ENABLED ; 
 int /*<<< orphan*/  TIMESTAMP_LEN ; 
 int /*<<< orphan*/  audit_review_gid ; 
 int /*<<< orphan*/  audit_warn_getacdir ; 
 scalar_t__ auditd_get_state () ; 
 int /*<<< orphan*/  auditd_log_debug (char*) ; 
 int /*<<< orphan*/  auditd_log_err (char*,char*,...) ; 
 int /*<<< orphan*/  auditd_log_notice (char*,char*) ; 
 scalar_t__ auditd_new_curlink (char*) ; 
 int /*<<< orphan*/  auditd_set_state (scalar_t__) ; 
 int /*<<< orphan*/  auditd_strerror (int) ; 
 int auditd_swap_trail (char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_lastfile (char*) ; 
 scalar_t__ getTSstr (int /*<<< orphan*/ ,char*,int) ; 
 char* lastfile ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
swap_audit_file(void)
{
	int err;
	char *newfile, *name;
	char TS[TIMESTAMP_LEN + 1];
	time_t tt;

	if (getTSstr(tt, TS, sizeof(TS)) != 0)
		return (-1);
	/*
	 * If prefix and suffix are the same, it means that records are
	 * being produced too fast. We don't want to rename now, because
	 * next trail file can get the same name and once that one is
	 * terminated also within one second it will overwrite the current
	 * one. Just keep writing to the same trail and wait for the next
	 * trigger from the kernel.
	 * FREEBSD KERNEL WAS UPDATED TO KEEP SENDING TRIGGERS, WHICH MIGHT
	 * NOT BE THE CASE FOR OTHER OSES.
	 * If the kernel will not keep sending triggers, trail file will not
	 * be terminated.
	 */
	if (lastfile == NULL) {
		name = NULL;
	} else {
		name = strrchr(lastfile, '/');
		if (name != NULL)
			name++;
	}
	if (name != NULL && strncmp(name, TS, TIMESTAMP_LEN) == 0) {
		auditd_log_debug("Not ready to terminate trail file yet.");
		return (0);
	}
	err = auditd_swap_trail(TS, &newfile, audit_review_gid,
	    audit_warn_getacdir);
	if (err != ADE_NOERR) {
		auditd_log_err("%s: %m", auditd_strerror(err));
		if (err != ADE_ACTL)
			return (-1);
	}

	/*
	 * Only close the last file if were in an auditing state before
	 * calling swap_audit_file().  We may need to recover from a crash.
	 */
	if (auditd_get_state() == AUD_STATE_ENABLED)
		close_lastfile(TS);


	/*
	 * auditd_swap_trail() potentially enables auditing (if not already
	 * enabled) so updated the cached state as well.
	 */
	auditd_set_state(AUD_STATE_ENABLED);

	/*
	 *  Create 'current' symlink.  Recover from crash, if needed.
	 */
	if (auditd_new_curlink(newfile) != 0)
		auditd_log_err("auditd_new_curlink(\"%s\") failed: %s: %m",
		    newfile, auditd_strerror(err));

	lastfile = newfile;
	auditd_log_notice("New audit file is %s", newfile);

	return (0);
}