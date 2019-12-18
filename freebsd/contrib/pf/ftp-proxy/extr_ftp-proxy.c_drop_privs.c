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
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHROOT_DIR ; 
 int /*<<< orphan*/  NOPRIV_USER ; 
 scalar_t__ chdir (char*) ; 
 scalar_t__ chroot (int /*<<< orphan*/ ) ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 scalar_t__ setgroups (int,int /*<<< orphan*/ *) ; 
 scalar_t__ setresgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setresuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tzset () ; 

int
drop_privs(void)
{
	struct passwd *pw;

	pw = getpwnam(NOPRIV_USER);
	if (pw == NULL)
		return (0);

	tzset();
	if (chroot(CHROOT_DIR) != 0 || chdir("/") != 0 ||
	    setgroups(1, &pw->pw_gid) != 0 ||
	    setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) != 0 ||
	    setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid) != 0)
		return (0);

	return (1);
}