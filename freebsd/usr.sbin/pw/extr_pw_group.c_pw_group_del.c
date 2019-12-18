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
typedef  int /*<<< orphan*/  uintmax_t ;
struct userconf {int dummy; } ;
struct group {int dummy; } ;
typedef  int intmax_t ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  EX_IOERR ; 
 int /*<<< orphan*/  GID_MAX ; 
 int /*<<< orphan*/  M_DELETE ; 
 int /*<<< orphan*/  W_GROUP ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int delgrent (struct group*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freopen (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct userconf* get_userconfig (char const*) ; 
 struct group* getgroup (char*,int,int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ nis_update () ; 
 char* optarg ; 
 int pw_checkid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pw_log (struct userconf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strspn (char*,char*) ; 

int
pw_group_del(int argc, char **argv, char *arg1)
{
	struct userconf *cnf = NULL;
	struct group *grp = NULL;
	char *name;
	const char *cfg = NULL;
	intmax_t id = -1;
	int ch, rc;
	bool quiet = false;
	bool nis = false;

	if (arg1 != NULL) {
		if (arg1[strspn(arg1, "0123456789")] == '\0')
			id = pw_checkid(arg1, GID_MAX);
		else
			name = arg1;
	}

	while ((ch = getopt(argc, argv, "C:qn:g:Y")) != -1) {
		switch (ch) {
		case 'C':
			cfg = optarg;
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
		case 'Y':
			nis = true;
			break;
		}
	}

	if (quiet)
		freopen(_PATH_DEVNULL, "w", stderr);
	grp = getgroup(name, id, true);
	cnf = get_userconfig(cfg);
	rc = delgrent(grp);
	if (rc == -1)
		err(EX_IOERR, "group '%s' not available (NIS?)", name);
	else if (rc != 0)
		err(EX_IOERR, "group update");
	pw_log(cnf, M_DELETE, W_GROUP, "%s(%ju) removed", name,
	    (uintmax_t)id);

	if (nis && nis_update() == 0)
		pw_log(cnf, M_DELETE, W_GROUP, "NIS maps updated");

	return (EXIT_SUCCESS);
}