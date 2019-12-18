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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  token_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  au_tid_t ;
typedef  int /*<<< orphan*/  au_id_t ;
typedef  int /*<<< orphan*/  au_asid_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  au_free_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * au_to_subject32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * au_to_text (char*) ; 
 int audit_write (short,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int kAUMakeSubjectTokErr ; 
 int kAUMakeTextTokErr ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

int
audit_write_failure(short event_code, char *errmsg, int errcode, au_id_t auid,
    uid_t euid, gid_t egid, uid_t ruid, gid_t rgid, pid_t pid, au_asid_t sid,
    au_tid_t *tid)
{
	char *func = "audit_write_failure()";
	token_t *subject, *errtok;

	subject = au_to_subject32(auid, euid, egid, ruid, rgid, pid, sid, tid);
	if (subject == NULL) {
		syslog(LOG_ERR, "%s: au_to_subject32() failed", func);
		return (kAUMakeSubjectTokErr);
	}

	/* tokenize and save the error message */
	if ((errtok = au_to_text(errmsg)) == NULL) {
		au_free_token(subject);
		syslog(LOG_ERR, "%s: au_to_text() failed", func);
		return (kAUMakeTextTokErr);
	}

	return (audit_write(event_code, subject, errtok, -1, errcode));
}