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
struct passwd {int /*<<< orphan*/  pw_name; int /*<<< orphan*/  pw_gid; } ;
struct cfjail {int dummy; } ;
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 scalar_t__ errno ; 
 struct passwd* getpwnam (char const*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ initgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jail_warnx (struct cfjail*,char*,char const*,...) ; 
 int /*<<< orphan*/ * login_getpwclass (struct passwd const*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static int
get_user_info(struct cfjail *j, const char *username,
    const struct passwd **pwdp, login_cap_t **lcapp)
{
	const struct passwd *pwd;

	errno = 0;
	*pwdp = pwd = username ? getpwnam(username) : getpwuid(getuid());
	if (pwd == NULL) {
		if (errno)
			jail_warnx(j, "getpwnam%s%s: %s", username ? " " : "",
			    username ? username : "", strerror(errno));
		else if (username)
			jail_warnx(j, "%s: no such user", username);
		else
			jail_warnx(j, "unknown uid %d", getuid());
		return -1;
	}
	*lcapp = login_getpwclass(pwd);
	if (*lcapp == NULL) {
		jail_warnx(j, "getpwclass %s: %s", pwd->pw_name,
		    strerror(errno));
		return -1;
	}
	/* Set the groups while the group file is still available */
	if (initgroups(pwd->pw_name, pwd->pw_gid) < 0) {
		jail_warnx(j, "initgroups %s: %s", pwd->pw_name,
		    strerror(errno));
		return -1;
	}
	return 0;
}