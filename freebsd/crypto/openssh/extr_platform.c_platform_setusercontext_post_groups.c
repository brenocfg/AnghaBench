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
struct passwd {int /*<<< orphan*/  pw_name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * chroot_directory; scalar_t__ use_pam; } ;

/* Variables and functions */
 int /*<<< orphan*/  aix_usrinfo (struct passwd*) ; 
 int /*<<< orphan*/  do_pam_setcred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  irix_setusercontext (struct passwd*) ; 
 TYPE_1__ options ; 
 int setpcred (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  ssh_selinux_setup_exec_context (int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  use_privsep ; 

void
platform_setusercontext_post_groups(struct passwd *pw)
{
#if !defined(HAVE_LOGIN_CAP) && defined(USE_PAM)
	/*
	 * PAM credentials may take the form of supplementary groups.
	 * These will have been wiped by the above initgroups() call.
	 * Reestablish them here.
	 */
	if (options.use_pam) {
		do_pam_setcred(use_privsep);
	}
#endif /* USE_PAM */

#if !defined(HAVE_LOGIN_CAP) && (defined(WITH_IRIX_PROJECT) || \
    defined(WITH_IRIX_JOBS) || defined(WITH_IRIX_ARRAY))
	irix_setusercontext(pw);
#endif /* defined(WITH_IRIX_PROJECT) || defined(WITH_IRIX_JOBS) || defined(WITH_IRIX_ARRAY) */

#ifdef _AIX
	aix_usrinfo(pw);
#endif /* _AIX */

#ifdef HAVE_SETPCRED
	/*
	 * If we have a chroot directory, we set all creds except real
	 * uid which we will need for chroot.  If we don't have a
	 * chroot directory, we don't override anything.
	 */
	{
		char **creds = NULL, *chroot_creds[] =
		    { "REAL_USER=root", NULL };

		if (options.chroot_directory != NULL &&
		    strcasecmp(options.chroot_directory, "none") != 0)
			creds = chroot_creds;

		if (setpcred(pw->pw_name, creds) == -1)
			fatal("Failed to set process credentials");
	}
#endif /* HAVE_SETPCRED */
#ifdef WITH_SELINUX
	ssh_selinux_setup_exec_context(pw->pw_name);
#endif
}