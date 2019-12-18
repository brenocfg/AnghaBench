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
typedef  int /*<<< orphan*/  uidstr ;
typedef  int /*<<< orphan*/  u_int ;
struct passwd {scalar_t__ pw_uid; int /*<<< orphan*/  pw_name; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_gid; } ;
struct TYPE_2__ {char* chroot_directory; } ;

/* Variables and functions */
 int LOGIN_SETALL ; 
 int LOGIN_SETENV ; 
 int LOGIN_SETPATH ; 
 int LOGIN_SETUMASK ; 
 int LOGIN_SETUSER ; 
 int /*<<< orphan*/  endgrent () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getuid () ; 
 int in_chroot ; 
 scalar_t__ initgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lc ; 
 TYPE_1__ options ; 
 char* percent_expand (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  permanently_set_uid (struct passwd*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ platform_privileged_uidswap () ; 
 int /*<<< orphan*/  platform_setusercontext (struct passwd*) ; 
 int /*<<< orphan*/  platform_setusercontext_post_groups (struct passwd*) ; 
 int /*<<< orphan*/  safely_chroot (char*,scalar_t__) ; 
 scalar_t__ set_id (int /*<<< orphan*/ ) ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 scalar_t__ setlogin (int /*<<< orphan*/ ) ; 
 scalar_t__ setusercontext (int /*<<< orphan*/ ,struct passwd*,scalar_t__,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* tilde_expand_filename (char*,scalar_t__) ; 

void
do_setusercontext(struct passwd *pw)
{
	char uidstr[32], *chroot_path, *tmp;

	platform_setusercontext(pw);

	if (platform_privileged_uidswap()) {
#ifdef HAVE_LOGIN_CAP
		if (setusercontext(lc, pw, pw->pw_uid,
		    (LOGIN_SETALL & ~(LOGIN_SETENV|LOGIN_SETPATH|LOGIN_SETUSER))) < 0) {
			perror("unable to set user context");
			exit(1);
		}
#else
		if (setlogin(pw->pw_name) < 0)
			error("setlogin failed: %s", strerror(errno));
		if (setgid(pw->pw_gid) < 0) {
			perror("setgid");
			exit(1);
		}
		/* Initialize the group list. */
		if (initgroups(pw->pw_name, pw->pw_gid) < 0) {
			perror("initgroups");
			exit(1);
		}
		endgrent();
#endif

		platform_setusercontext_post_groups(pw);

		if (!in_chroot && options.chroot_directory != NULL &&
		    strcasecmp(options.chroot_directory, "none") != 0) {
                        tmp = tilde_expand_filename(options.chroot_directory,
			    pw->pw_uid);
			snprintf(uidstr, sizeof(uidstr), "%llu",
			    (unsigned long long)pw->pw_uid);
			chroot_path = percent_expand(tmp, "h", pw->pw_dir,
			    "u", pw->pw_name, "U", uidstr, (char *)NULL);
			safely_chroot(chroot_path, pw->pw_uid);
			free(tmp);
			free(chroot_path);
			/* Make sure we don't attempt to chroot again */
			free(options.chroot_directory);
			options.chroot_directory = NULL;
			in_chroot = 1;
		}

#ifdef HAVE_LOGIN_CAP
		if (setusercontext(lc, pw, pw->pw_uid, LOGIN_SETUSER) < 0) {
			perror("unable to set user context (setuser)");
			exit(1);
		}
		/* 
		 * FreeBSD's setusercontext() will not apply the user's
		 * own umask setting unless running with the user's UID.
		 */
		(void) setusercontext(lc, pw, pw->pw_uid, LOGIN_SETUMASK);
#else
# ifdef USE_LIBIAF
		/*
		 * In a chroot environment, the set_id() will always fail;
		 * typically because of the lack of necessary authentication
		 * services and runtime such as ./usr/lib/libiaf.so,
		 * ./usr/lib/libpam.so.1, and ./etc/passwd We skip it in the
		 * internal sftp chroot case.  We'll lose auditing and ACLs but
		 * permanently_set_uid will take care of the rest.
		 */
		if (!in_chroot && set_id(pw->pw_name) != 0)
			fatal("set_id(%s) Failed", pw->pw_name);
# endif /* USE_LIBIAF */
		/* Permanently switch to the desired uid. */
		permanently_set_uid(pw);
#endif
	} else if (options.chroot_directory != NULL &&
	    strcasecmp(options.chroot_directory, "none") != 0) {
		fatal("server lacks privileges to chroot to ChrootDirectory");
	}

	if (getuid() != pw->pw_uid || geteuid() != pw->pw_uid)
		fatal("Failed to set uids to %u.", (u_int) pw->pw_uid);
}