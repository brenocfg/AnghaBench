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
typedef  char const* uid_t ;
struct passwd {char const* pw_name; int /*<<< orphan*/  pw_gid; } ;
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 struct passwd* getpwnam (char const*) ; 
 struct passwd* getpwuid (char const*) ; 
 char* getuid () ; 
 scalar_t__ initgroups (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * login_getpwclass (struct passwd const*) ; 

__attribute__((used)) static void
get_user_info(const char *username, const struct passwd **pwdp,
    login_cap_t **lcapp)
{
	uid_t uid;
	const struct passwd *pwd;

	errno = 0;
	if (username) {
		pwd = getpwnam(username);
		if (pwd == NULL) {
			if (errno)
				err(1, "getpwnam: %s", username);
			else
				errx(1, "%s: no such user", username);
		}
	} else {
		uid = getuid();
		pwd = getpwuid(uid);
		if (pwd == NULL) {
			if (errno)
				err(1, "getpwuid: %d", uid);
			else
				errx(1, "unknown uid: %d", uid);
		}
	}
	*pwdp = pwd;
	*lcapp = login_getpwclass(pwd);
	if (*lcapp == NULL)
		err(1, "getpwclass: %s", pwd->pw_name);
	if (initgroups(pwd->pw_name, pwd->pw_gid) < 0)
		err(1, "initgroups: %s", pwd->pw_name);
}