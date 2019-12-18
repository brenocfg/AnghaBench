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
 int /*<<< orphan*/ * au_to_me () ; 
 int audit_write (short,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kAUMakeSubjectTokErr ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

int
audit_write_success_self(short event_code, token_t *tok)
{
	token_t *subject;
	char *func = "audit_write_success_self()";

	if ((subject = au_to_me()) == NULL) {
		syslog(LOG_ERR, "%s: au_to_me() failed", func);
		return (kAUMakeSubjectTokErr);
	}

	return (audit_write(event_code, subject, tok, 0, 0));
}