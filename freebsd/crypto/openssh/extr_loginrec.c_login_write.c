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
struct logininfo {scalar_t__ type; int /*<<< orphan*/  username; int /*<<< orphan*/  line; int /*<<< orphan*/  hostname; } ;

/* Variables and functions */
 scalar_t__ LTYPE_LOGIN ; 
 scalar_t__ LTYPE_LOGOUT ; 
 int /*<<< orphan*/  audit_session_close (struct logininfo*) ; 
 int /*<<< orphan*/  audit_session_open (struct logininfo*) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  lastlog_write_entry (struct logininfo*) ; 
 int /*<<< orphan*/  login_set_current_time (struct logininfo*) ; 
 int /*<<< orphan*/  loginmsg ; 
 int /*<<< orphan*/  logit (char*,...) ; 
 int /*<<< orphan*/  sys_auth_record_login (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslogin_write_entry (struct logininfo*) ; 
 int /*<<< orphan*/  utmp_write_entry (struct logininfo*) ; 
 int /*<<< orphan*/  utmpx_write_entry (struct logininfo*) ; 
 int /*<<< orphan*/  wtmp_write_entry (struct logininfo*) ; 
 int /*<<< orphan*/  wtmpx_write_entry (struct logininfo*) ; 

int
login_write(struct logininfo *li)
{
#ifndef HAVE_CYGWIN
	if (geteuid() != 0) {
		logit("Attempt to write login records by non-root user (aborting)");
		return (1);
	}
#endif

	/* set the timestamp */
	login_set_current_time(li);
#ifdef USE_LOGIN
	syslogin_write_entry(li);
#endif
#ifdef USE_LASTLOG
	if (li->type == LTYPE_LOGIN)
		lastlog_write_entry(li);
#endif
#ifdef USE_UTMP
	utmp_write_entry(li);
#endif
#ifdef USE_WTMP
	wtmp_write_entry(li);
#endif
#ifdef USE_UTMPX
	utmpx_write_entry(li);
#endif
#ifdef USE_WTMPX
	wtmpx_write_entry(li);
#endif
#ifdef CUSTOM_SYS_AUTH_RECORD_LOGIN
	if (li->type == LTYPE_LOGIN &&
	    !sys_auth_record_login(li->username,li->hostname,li->line,
	    &loginmsg))
		logit("Writing login record failed for %s", li->username);
#endif
#ifdef SSH_AUDIT_EVENTS
	if (li->type == LTYPE_LOGIN)
		audit_session_open(li);
	else if (li->type == LTYPE_LOGOUT)
		audit_session_close(li);
#endif
	return (0);
}