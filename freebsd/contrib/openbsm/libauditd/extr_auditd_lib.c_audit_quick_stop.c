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
typedef  int /*<<< orphan*/  oldname ;
typedef  int /*<<< orphan*/  newname ;
typedef  int /*<<< orphan*/  TS ;

/* Variables and functions */
 int AUC_DISABLED ; 
 int AUC_NOAUDIT ; 
 int /*<<< orphan*/  AUDIT_CURRENT_LINK ; 
 int /*<<< orphan*/  AUE_audit_shutdown ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  NOT_TERMINATED ; 
 int /*<<< orphan*/  POSTFIX_LEN ; 
 int /*<<< orphan*/  TIMESTAMP_LEN ; 
 int /*<<< orphan*/  __BSM_INTERNAL_NOTIFY_KEY ; 
 scalar_t__ audit_get_cond (int*) ; 
 scalar_t__ audit_set_cond (int*) ; 
 int /*<<< orphan*/  auditd_gen_record (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ auditd_rename (char*,char*) ; 
 scalar_t__ getTSstr (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_post (int /*<<< orphan*/ ) ; 
 int readlink (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int
audit_quick_stop(void)
{
	int len;
	int cond;
	char *ptr;
	time_t tt;
	char oldname[MAXPATHLEN];
	char newname[MAXPATHLEN];
	char TS[TIMESTAMP_LEN + 1];

	/*
	 * Auditing already disabled?
	 */
	if (audit_get_cond(&cond) != 0)
		return (-1);
	if (cond == AUC_NOAUDIT)
		return (0);

	/*
	 *  Generate audit shutdown record.
	 */
	(void) auditd_gen_record(AUE_audit_shutdown, NULL);

	/*
	 * Shutdown auditing in the kernel.
	 */
	cond = AUC_DISABLED;
	if (audit_set_cond(&cond) != 0)
		return (-1);
#ifdef	__BSM_INTERNAL_NOTIFY_KEY
	notify_post(__BSM_INTERNAL_NOTIFY_KEY);
#endif

	/*
	 * Rename last audit trail and remove 'current' link.
	 */
	len = readlink(AUDIT_CURRENT_LINK, oldname, sizeof(oldname) - 1);
	if (len < 0)
		return (-1);
	oldname[len++] = '\0';

	if (getTSstr(tt, TS, sizeof(TS)) != 0)
		return (-1);

	strlcpy(newname, oldname, sizeof(newname));

	if ((ptr = strstr(newname, NOT_TERMINATED)) != NULL) {
		memcpy(ptr, TS, POSTFIX_LEN);
		if (auditd_rename(oldname, newname) != 0)
			return (-1);
	} else
		return (-1);

	(void) unlink(AUDIT_CURRENT_LINK);

	return (0);
}