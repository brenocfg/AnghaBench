#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_name; } ;
struct connection_info {char const* user; } ;
typedef  int /*<<< orphan*/  login_cap_t ;
typedef  int /*<<< orphan*/  auth_session_t ;
struct TYPE_4__ {int /*<<< orphan*/  use_dns; int /*<<< orphan*/  log_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLACKLIST_BAD_USER ; 
 int /*<<< orphan*/  BLACKLIST_NOTIFY (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  SSH_INVALID_USER ; 
 struct ssh* active_state ; 
 int /*<<< orphan*/  aix_restoreauthdb () ; 
 int /*<<< orphan*/  aix_setauthdb (char const*) ; 
 int /*<<< orphan*/  allowed_user (struct passwd*) ; 
 int /*<<< orphan*/  audit_event (int /*<<< orphan*/ ) ; 
 scalar_t__ auth_approval (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  auth_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auth_get_canonical_hostname (struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * auth_open () ; 
 scalar_t__ auth_setpwd (int /*<<< orphan*/ *,struct passwd*) ; 
 int /*<<< orphan*/  debug (char*,char const*) ; 
 struct connection_info* get_connection_info (int,int /*<<< orphan*/ ) ; 
 struct passwd* getpwnam (char const*) ; 
 int /*<<< orphan*/  log_change_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * login_getpwclass (struct passwd*) ; 
 int /*<<< orphan*/  logit (char*,char const*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  parse_server_match_config (TYPE_1__*,struct connection_info*) ; 
 int /*<<< orphan*/  process_permitopen (struct ssh*,TYPE_1__*) ; 
 struct passwd* pwcopy (struct passwd*) ; 
 int /*<<< orphan*/  record_failed_login (char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_port (struct ssh*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

struct passwd *
getpwnamallow(const char *user)
{
	struct ssh *ssh = active_state; /* XXX */
#ifdef HAVE_LOGIN_CAP
	extern login_cap_t *lc;
#ifdef BSD_AUTH
	auth_session_t *as;
#endif
#endif
	struct passwd *pw;
	struct connection_info *ci = get_connection_info(1, options.use_dns);

	ci->user = user;
	parse_server_match_config(&options, ci);
	log_change_level(options.log_level);
	process_permitopen(ssh, &options);

#if defined(_AIX) && defined(HAVE_SETAUTHDB)
	aix_setauthdb(user);
#endif

	pw = getpwnam(user);

#if defined(_AIX) && defined(HAVE_SETAUTHDB)
	aix_restoreauthdb();
#endif
#ifdef HAVE_CYGWIN
	/*
	 * Windows usernames are case-insensitive.  To avoid later problems
	 * when trying to match the username, the user is only allowed to
	 * login if the username is given in the same case as stored in the
	 * user database.
	 */
	if (pw != NULL && strcmp(user, pw->pw_name) != 0) {
		logit("Login name %.100s does not match stored username %.100s",
		    user, pw->pw_name);
		pw = NULL;
	}
#endif
	if (pw == NULL) {
		BLACKLIST_NOTIFY(BLACKLIST_BAD_USER, user);
		logit("Invalid user %.100s from %.100s port %d",
		    user, ssh_remote_ipaddr(ssh), ssh_remote_port(ssh));
#ifdef CUSTOM_FAILED_LOGIN
		record_failed_login(user,
		    auth_get_canonical_hostname(ssh, options.use_dns), "ssh");
#endif
#ifdef SSH_AUDIT_EVENTS
		audit_event(SSH_INVALID_USER);
#endif /* SSH_AUDIT_EVENTS */
		return (NULL);
	}
	if (!allowed_user(pw))
		return (NULL);
#ifdef HAVE_LOGIN_CAP
	if ((lc = login_getpwclass(pw)) == NULL) {
		debug("unable to get login class: %s", user);
		return (NULL);
	}
#ifdef BSD_AUTH
	if ((as = auth_open()) == NULL || auth_setpwd(as, pw) != 0 ||
	    auth_approval(as, lc, pw->pw_name, "ssh") <= 0) {
		debug("Approval failure for %s", user);
		pw = NULL;
	}
	if (as != NULL)
		auth_close(as);
#endif
#endif
	if (pw != NULL)
		return (pwcopy(pw));
	return (NULL);
}