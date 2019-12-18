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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  au_free_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * au_to_me () ; 
 int /*<<< orphan*/ * au_to_text (char*) ; 
 int audit_write (short,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int kAUMakeSubjectTokErr ; 
 int kAUMakeTextTokErr ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

int
audit_write_failure_self(short event_code, char *errmsg, int errret)
{
	char *func = "audit_write_failure_self()";
	token_t *subject, *errtok;

	if ((subject = au_to_me()) == NULL) {
		syslog(LOG_ERR, "%s: au_to_me() failed", func);
		return (kAUMakeSubjectTokErr);
	}
	/* tokenize and save the error message */
	if ((errtok = au_to_text(errmsg)) == NULL) {
		au_free_token(subject);
		syslog(LOG_ERR, "%s: au_to_text() failed", func);
		return (kAUMakeTextTokErr);
	}
	return (audit_write(event_code, subject, errtok, -1, errret));
}