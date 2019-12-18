#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct passwd {int /*<<< orphan*/  pw_uid; } ;
struct TYPE_2__ {scalar_t__ use_pam; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_pam_setcred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ geteuid () ; 
 int getluid () ; 
 scalar_t__ getuid () ; 
 TYPE_1__ options ; 
 int setluid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solaris_set_default_project (struct passwd*) ; 
 int /*<<< orphan*/  ssh_selinux_enabled () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_privsep ; 

void
platform_setusercontext(struct passwd *pw)
{
#ifdef WITH_SELINUX
	/* Cache selinux status for later use */
	(void)ssh_selinux_enabled();
#endif

#ifdef USE_SOLARIS_PROJECTS
	/*
	 * If solaris projects were detected, set the default now, unless
	 * we are using PAM in which case it is the responsibility of the
	 * PAM stack.
	 */
	if (!options.use_pam && (getuid() == 0 || geteuid() == 0))
		solaris_set_default_project(pw);
#endif

#if defined(HAVE_LOGIN_CAP) && defined (__bsdi__)
	if (getuid() == 0 || geteuid() == 0)
		setpgid(0, 0);
# endif

#if defined(HAVE_LOGIN_CAP) && defined(USE_PAM)
	/*
	 * If we have both LOGIN_CAP and PAM, we want to establish creds
	 * before calling setusercontext (in session.c:do_setusercontext).
	 */
	if (getuid() == 0 || geteuid() == 0) {
		if (options.use_pam) {
			do_pam_setcred(use_privsep);
		}
	}
# endif /* USE_PAM */

#if !defined(HAVE_LOGIN_CAP) && defined(HAVE_GETLUID) && defined(HAVE_SETLUID)
	if (getuid() == 0 || geteuid() == 0) {
		/* Sets login uid for accounting */
		if (getluid() == -1 && setluid(pw->pw_uid) == -1)
			error("setluid: %s", strerror(errno));
	}
#endif
}