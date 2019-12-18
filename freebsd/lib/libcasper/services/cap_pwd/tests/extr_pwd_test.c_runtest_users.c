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
typedef  scalar_t__ uid_t ;
struct passwd {scalar_t__ const pw_uid; int /*<<< orphan*/  pw_name; } ;
typedef  int /*<<< orphan*/  cap_channel_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct passwd* cap_getpwent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_getpwent_r (int /*<<< orphan*/ *,struct passwd*,char*,int,struct passwd**) ; 
 struct passwd* cap_getpwnam (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  cap_getpwnam_r (int /*<<< orphan*/ *,char const*,struct passwd*,char*,int,struct passwd**) ; 
 struct passwd* cap_getpwuid (int /*<<< orphan*/ *,scalar_t__ const) ; 
 int /*<<< orphan*/  cap_getpwuid_r (int /*<<< orphan*/ *,scalar_t__ const,struct passwd*,char*,int,struct passwd**) ; 
 int /*<<< orphan*/  cap_setpwent (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
runtest_users(cap_channel_t *cappwd, const char **names, const uid_t *uids,
    size_t nusers)
{
	char buf[1024];
	struct passwd *pwd;
	struct passwd st;
	unsigned int i, got;

	cap_setpwent(cappwd);
	got = 0;
	for (;;) {
		pwd = cap_getpwent(cappwd);
		if (pwd == NULL)
			break;
		got++;
		for (i = 0; i < nusers; i++) {
			if (strcmp(names[i], pwd->pw_name) == 0 &&
			    uids[i] == pwd->pw_uid) {
				break;
			}
		}
		if (i == nusers)
			return (false);
	}
	if (got != nusers)
		return (false);

	cap_setpwent(cappwd);
	got = 0;
	for (;;) {
		cap_getpwent_r(cappwd, &st, buf, sizeof(buf), &pwd);
		if (pwd == NULL)
			break;
		got++;
		for (i = 0; i < nusers; i++) {
			if (strcmp(names[i], pwd->pw_name) == 0 &&
			    uids[i] == pwd->pw_uid) {
				break;
			}
		}
		if (i == nusers)
			return (false);
	}
	if (got != nusers)
		return (false);

	for (i = 0; i < nusers; i++) {
		pwd = cap_getpwnam(cappwd, names[i]);
		if (pwd == NULL)
			return (false);
	}

	for (i = 0; i < nusers; i++) {
		cap_getpwnam_r(cappwd, names[i], &st, buf, sizeof(buf), &pwd);
		if (pwd == NULL)
			return (false);
	}

	for (i = 0; i < nusers; i++) {
		pwd = cap_getpwuid(cappwd, uids[i]);
		if (pwd == NULL)
			return (false);
	}

	for (i = 0; i < nusers; i++) {
		cap_getpwuid_r(cappwd, uids[i], &st, buf, sizeof(buf), &pwd);
		if (pwd == NULL)
			return (false);
	}

	return (true);
}