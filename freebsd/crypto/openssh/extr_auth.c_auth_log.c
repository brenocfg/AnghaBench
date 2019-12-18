#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_6__ {int max_authtries; int /*<<< orphan*/  use_dns; } ;
struct TYPE_5__ {int failures; scalar_t__ postponed; int /*<<< orphan*/  user; scalar_t__ valid; int /*<<< orphan*/ * auth_method_info; } ;
typedef  TYPE_1__ Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  BLACKLIST_AUTH_OK ; 
 int /*<<< orphan*/  BLACKLIST_NOTIFY (int /*<<< orphan*/ ,char*) ; 
 struct ssh* active_state ; 
 int /*<<< orphan*/  audit_classify_auth (char const*) ; 
 int /*<<< orphan*/  audit_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_get_canonical_hostname (struct ssh*,int /*<<< orphan*/ ) ; 
 char* format_method_key (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  loginmsg ; 
 void logit (char const*) ; 
 int /*<<< orphan*/  mm_is_monitor () ; 
 TYPE_2__ options ; 
 int /*<<< orphan*/  record_failed_login (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_port (struct ssh*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  sys_auth_record_login (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ use_privsep ; 
 void verbose (char const*) ; 
 char* xstrdup (int /*<<< orphan*/ *) ; 

void
auth_log(Authctxt *authctxt, int authenticated, int partial,
    const char *method, const char *submethod)
{
	struct ssh *ssh = active_state; /* XXX */
	void (*authlog) (const char *fmt,...) = verbose;
	const char *authmsg;
	char *extra = NULL;

	if (use_privsep && !mm_is_monitor() && !authctxt->postponed)
		return;

	/* Raise logging level */
	if (authenticated == 1 ||
	    !authctxt->valid ||
	    authctxt->failures >= options.max_authtries / 2 ||
	    strcmp(method, "password") == 0)
		authlog = logit;

	if (authctxt->postponed)
		authmsg = "Postponed";
	else if (partial)
		authmsg = "Partial";
	else {
		authmsg = authenticated ? "Accepted" : "Failed";
		if (authenticated)
			BLACKLIST_NOTIFY(BLACKLIST_AUTH_OK, "ssh");
	}

	if ((extra = format_method_key(authctxt)) == NULL) {
		if (authctxt->auth_method_info != NULL)
			extra = xstrdup(authctxt->auth_method_info);
	}

	authlog("%s %s%s%s for %s%.100s from %.200s port %d ssh2%s%s",
	    authmsg,
	    method,
	    submethod != NULL ? "/" : "", submethod == NULL ? "" : submethod,
	    authctxt->valid ? "" : "invalid user ",
	    authctxt->user,
	    ssh_remote_ipaddr(ssh),
	    ssh_remote_port(ssh),
	    extra != NULL ? ": " : "",
	    extra != NULL ? extra : "");

	free(extra);

#ifdef CUSTOM_FAILED_LOGIN
	if (authenticated == 0 && !authctxt->postponed &&
	    (strcmp(method, "password") == 0 ||
	    strncmp(method, "keyboard-interactive", 20) == 0 ||
	    strcmp(method, "challenge-response") == 0))
		record_failed_login(authctxt->user,
		    auth_get_canonical_hostname(ssh, options.use_dns), "ssh");
# ifdef WITH_AIXAUTHENTICATE
	if (authenticated)
		sys_auth_record_login(authctxt->user,
		    auth_get_canonical_hostname(ssh, options.use_dns), "ssh",
		    &loginmsg);
# endif
#endif
#ifdef SSH_AUDIT_EVENTS
	if (authenticated == 0 && !authctxt->postponed)
		audit_event(audit_classify_auth(method));
#endif
}