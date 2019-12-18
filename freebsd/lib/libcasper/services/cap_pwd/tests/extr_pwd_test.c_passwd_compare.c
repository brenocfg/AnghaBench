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
struct passwd {scalar_t__ pw_uid; scalar_t__ pw_gid; scalar_t__ pw_change; scalar_t__ pw_expire; scalar_t__ pw_fields; int /*<<< orphan*/ * pw_shell; int /*<<< orphan*/ * pw_dir; int /*<<< orphan*/ * pw_gecos; int /*<<< orphan*/ * pw_class; int /*<<< orphan*/ * pw_passwd; int /*<<< orphan*/ * pw_name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
passwd_compare(const struct passwd *pwd0, const struct passwd *pwd1)
{

	if (pwd0 == NULL && pwd1 == NULL)
		return (true);
	if (pwd0 == NULL || pwd1 == NULL)
		return (false);

	if (strcmp(pwd0->pw_name, pwd1->pw_name) != 0)
		return (false);

	if (pwd0->pw_passwd != NULL || pwd1->pw_passwd != NULL) {
		if (pwd0->pw_passwd == NULL || pwd1->pw_passwd == NULL)
			return (false);
		if (strcmp(pwd0->pw_passwd, pwd1->pw_passwd) != 0)
			return (false);
	}

	if (pwd0->pw_uid != pwd1->pw_uid)
		return (false);

	if (pwd0->pw_gid != pwd1->pw_gid)
		return (false);

	if (pwd0->pw_change != pwd1->pw_change)
		return (false);

	if (pwd0->pw_class != NULL || pwd1->pw_class != NULL) {
		if (pwd0->pw_class == NULL || pwd1->pw_class == NULL)
			return (false);
		if (strcmp(pwd0->pw_class, pwd1->pw_class) != 0)
			return (false);
	}

	if (pwd0->pw_gecos != NULL || pwd1->pw_gecos != NULL) {
		if (pwd0->pw_gecos == NULL || pwd1->pw_gecos == NULL)
			return (false);
		if (strcmp(pwd0->pw_gecos, pwd1->pw_gecos) != 0)
			return (false);
	}

	if (pwd0->pw_dir != NULL || pwd1->pw_dir != NULL) {
		if (pwd0->pw_dir == NULL || pwd1->pw_dir == NULL)
			return (false);
		if (strcmp(pwd0->pw_dir, pwd1->pw_dir) != 0)
			return (false);
	}

	if (pwd0->pw_shell != NULL || pwd1->pw_shell != NULL) {
		if (pwd0->pw_shell == NULL || pwd1->pw_shell == NULL)
			return (false);
		if (strcmp(pwd0->pw_shell, pwd1->pw_shell) != 0)
			return (false);
	}

	if (pwd0->pw_expire != pwd1->pw_expire)
		return (false);

	if (pwd0->pw_fields != pwd1->pw_fields)
		return (false);

	return (true);
}