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
typedef  int /*<<< orphan*/  token_t ;

/* Variables and functions */
 int /*<<< orphan*/  AU_TO_NO_WRITE ; 
 int /*<<< orphan*/  AU_TO_WRITE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ au_close (int,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  au_free_token (int /*<<< orphan*/ *) ; 
 int au_open () ; 
 int /*<<< orphan*/ * au_to_return32 (char,int) ; 
 int au_write (int,int /*<<< orphan*/ *) ; 
 int kAUCloseErr ; 
 int kAUMakeReturnTokErr ; 
 int kAUNoErr ; 
 int kAUOpenErr ; 
 int kAUWriteCallerTokErr ; 
 int kAUWriteReturnTokErr ; 
 int kAUWriteSubjectTokErr ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

int
audit_write(short event_code, token_t *subject, token_t *misctok, char retval,
    int errcode)
{
	int aufd;
	char *func = "audit_write()";
	token_t *rettok;

	if ((aufd = au_open()) == -1) {
		au_free_token(subject);
		au_free_token(misctok);
		syslog(LOG_ERR, "%s: au_open() failed", func);
		return (kAUOpenErr);
	}

	/* Save subject. */
	if (subject && au_write(aufd, subject) == -1) {
		au_free_token(subject);
		au_free_token(misctok);
		(void)au_close(aufd, AU_TO_NO_WRITE, event_code);
		syslog(LOG_ERR, "%s: write of subject failed", func);
		return (kAUWriteSubjectTokErr);
	}

	/* Save the event-specific token. */
	if (misctok && au_write(aufd, misctok) == -1) {
		au_free_token(misctok);
		(void)au_close(aufd, AU_TO_NO_WRITE, event_code);
		syslog(LOG_ERR, "%s: write of caller token failed", func);
		return (kAUWriteCallerTokErr);
	}

	/* Tokenize and save the return value. */
	if ((rettok = au_to_return32(retval, errcode)) == NULL) {
		(void)au_close(aufd, AU_TO_NO_WRITE, event_code);
		syslog(LOG_ERR, "%s: au_to_return32() failed", func);
		return (kAUMakeReturnTokErr);
	}

	if (au_write(aufd, rettok) == -1) {
		au_free_token(rettok);
		(void)au_close(aufd, AU_TO_NO_WRITE, event_code);
		syslog(LOG_ERR, "%s: write of return code failed", func);
		return (kAUWriteReturnTokErr);
	}

	/*
	 * We assume the caller wouldn't have bothered with this
	 * function if it hadn't already decided to keep the record.
	 */
	if (au_close(aufd, AU_TO_WRITE, event_code) < 0) {
		syslog(LOG_ERR, "%s: au_close() failed", func);
		return (kAUCloseErr);
	}

	return (kAUNoErr);
}