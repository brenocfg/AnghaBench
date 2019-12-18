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
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPNG_ADD ; 
 int /*<<< orphan*/  CAPNG_CLEAR_BOUNDING ; 
 int CAPNG_EFFECTIVE ; 
 int CAPNG_PERMITTED ; 
 int /*<<< orphan*/  CAP_NET_BIND_SERVICE ; 
 int /*<<< orphan*/  CAP_SETPCAP ; 
 scalar_t__ capng_change_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capng_clear (int) ; 
 scalar_t__ capng_updatev (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ chroot (scalar_t__) ; 
 scalar_t__ chroot_string ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ geteuid () ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ initgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* runas_string ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
switch_environment(void)
{
#ifdef HAVE_GETEUID
    if ((runas_string || chroot_string) && geteuid() != 0)
	errx(1, "no running as root, can't switch user/chroot");

    if (chroot_string && chroot(chroot_string) != 0)
	errx(1, "chroot(%s)", "chroot_string failed");

    if (runas_string) {
	struct passwd *pw;

	pw = getpwnam(runas_string);
	if (pw == NULL)
	    errx(1, "unknown user %s", runas_string);

	if (initgroups(pw->pw_name, pw->pw_gid) < 0)
	    err(1, "initgroups failed");

#ifndef HAVE_CAPNG
	if (setgid(pw->pw_gid) < 0)
	    err(1, "setgid(%s) failed", runas_string);

	if (setuid(pw->pw_uid) < 0)
	    err(1, "setuid(%s)", runas_string);
#else
	capng_clear (CAPNG_EFFECTIVE | CAPNG_PERMITTED);
	if (capng_updatev (CAPNG_ADD, CAPNG_EFFECTIVE | CAPNG_PERMITTED,
	                   CAP_NET_BIND_SERVICE, CAP_SETPCAP, -1) < 0)
	    err(1, "capng_updateev");

	if (capng_change_id(pw->pw_uid, pw->pw_gid,
	                    CAPNG_CLEAR_BOUNDING) < 0)
	    err(1, "capng_change_id(%s)", runas_string);
#endif
    }
#endif
}