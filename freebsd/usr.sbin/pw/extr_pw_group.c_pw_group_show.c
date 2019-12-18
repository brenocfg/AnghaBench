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
struct group {char* member_0; char* member_1; int member_2; int /*<<< orphan*/ * member_3; } ;
typedef  int intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENDGRENT () ; 
 int EXIT_SUCCESS ; 
 struct group* GETGRENT () ; 
 int /*<<< orphan*/  GID_MAX ; 
 int /*<<< orphan*/  SETGRENT () ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  freopen (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct group* getgroup (char*,int,int) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int print_group (struct group*,int) ; 
 int pw_checkid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strspn (char*,char*) ; 

int
pw_group_show(int argc, char **argv, char *arg1)
{
	struct group *grp = NULL;
	char *name = NULL;
	intmax_t id = -1;
	int ch;
	bool all, force, quiet, pretty;

	all = force = quiet = pretty = false;

	struct group fakegroup = {
		"nogroup",
		"*",
		-1,
		NULL
	};

	if (arg1 != NULL) {
		if (arg1[strspn(arg1, "0123456789")] == '\0')
			id = pw_checkid(arg1, GID_MAX);
		else
			name = arg1;
	}

	while ((ch = getopt(argc, argv, "C:qn:g:FPa")) != -1) {
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
		case 'g':
			id = pw_checkid(optarg, GID_MAX);
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
		}
	}

	if (quiet)
		freopen(_PATH_DEVNULL, "w", stderr);

	if (all) {
		SETGRENT();
		while ((grp = GETGRENT()) != NULL)
			print_group(grp, pretty);
		ENDGRENT();
		return (EXIT_SUCCESS);
	}

	grp = getgroup(name, id, !force);
	if (grp == NULL)
		grp = &fakegroup;

	return (print_group(grp, pretty));
}