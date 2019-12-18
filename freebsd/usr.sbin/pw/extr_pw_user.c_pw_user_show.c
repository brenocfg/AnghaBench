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
typedef  char* uintmax_t ;
struct passwd {int dummy; } ;
typedef  scalar_t__ intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPWENT () ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_NOUSER ; 
 struct passwd* GETPWENT () ; 
 struct passwd* GETPWNAM (int /*<<< orphan*/ ) ; 
 struct passwd* GETPWUID (scalar_t__) ; 
 int /*<<< orphan*/  SETPWENT () ; 
 int /*<<< orphan*/  UID_MAX ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 struct passwd fakeuser ; 
 int /*<<< orphan*/  freopen (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int print_user (struct passwd*,int,int) ; 
 scalar_t__ pw_checkid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pw_checkname (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strspn (char*,char*) ; 

int
pw_user_show(int argc, char **argv, char *arg1)
{
	struct passwd *pwd = NULL;
	char *name = NULL;
	intmax_t id = -1;
	int ch;
	bool all = false;
	bool pretty = false;
	bool force = false;
	bool v7 = false;
	bool quiet = false;

	if (arg1 != NULL) {
		if (arg1[strspn(arg1, "0123456789")] == '\0')
			id = pw_checkid(arg1, UID_MAX);
		else
			name = arg1;
	}

	while ((ch = getopt(argc, argv, "C:qn:u:FPa7")) != -1) {
		switch (ch) {
		case 'C':
			/* ignore compatibility */
			break;
		case 'q':
			quiet = true;
			break;
		case 'n':
			name = optarg;
			break;
		case 'u':
			id = pw_checkid(optarg, UID_MAX);
			break;
		case 'F':
			force = true;
			break;
		case 'P':
			pretty = true;
			break;
		case 'a':
			all = true;
			break;
		case '7':
			v7 = true;
			break;
		}
	}

	if (quiet)
		freopen(_PATH_DEVNULL, "w", stderr);

	if (all) {
		SETPWENT();
		while ((pwd = GETPWENT()) != NULL)
			print_user(pwd, pretty, v7);
		ENDPWENT();
		return (EXIT_SUCCESS);
	}

	if (id < 0 && name == NULL)
		errx(EX_DATAERR, "username or id required");

	pwd = (name != NULL) ? GETPWNAM(pw_checkname(name, 0)) : GETPWUID(id);
	if (pwd == NULL) {
		if (force) {
			pwd = &fakeuser;
		} else {
			if (name == NULL)
				errx(EX_NOUSER, "no such uid `%ju'",
				    (uintmax_t) id);
			errx(EX_NOUSER, "no such user `%s'", name);
		}
	}

	return (print_user(pwd, pretty, v7));
}