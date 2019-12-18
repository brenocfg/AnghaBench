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
struct userconf {int dummy; } ;
typedef  int intmax_t ;
struct TYPE_2__ {int checkduplicate; } ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/ * GETGRNAM (char*) ; 
 int /*<<< orphan*/  GID_MAX ; 
 int /*<<< orphan*/  M_ADD ; 
 int /*<<< orphan*/  W_GROUP ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freopen (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct userconf* get_userconfig (char const*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  gr_gidpolicy (struct userconf*,int) ; 
 int groupadd (struct userconf*,char*,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 scalar_t__ nis_update () ; 
 char* optarg ; 
 int pw_checkfd (char*) ; 
 int pw_checkid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pw_log (struct userconf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strspn (char*,char*) ; 

int
pw_group_add(int argc, char **argv, char *arg1)
{
	struct userconf *cnf = NULL;
	char *name = NULL;
	char *members = NULL;
	const char *cfg = NULL;
	intmax_t id = -1;
	int ch, rc, fd = -1;
	bool quiet, precrypted, dryrun, pretty, nis;

	quiet = precrypted = dryrun = pretty = nis = false;

	if (arg1 != NULL) {
		if (arg1[strspn(arg1, "0123456789")] == '\0')
			id = pw_checkid(arg1, GID_MAX);
		else
			name = arg1;
	}

	while ((ch = getopt(argc, argv, "C:qn:g:h:H:M:oNPY")) != -1) {
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
		case 'H':
			if (fd != -1)
				errx(EX_USAGE, "'-h' and '-H' are mutually "
				    "exclusive options");
			fd = pw_checkfd(optarg);
			precrypted = true;
			if (fd == '-')
				errx(EX_USAGE, "-H expects a file descriptor");
			break;
		case 'h':
			if (fd != -1)
				errx(EX_USAGE, "'-h' and '-H' are mutually "
				    "exclusive options");
			fd = pw_checkfd(optarg);
			break;
		case 'M':
			members = optarg;
			break;
		case 'o':
			conf.checkduplicate = false;
			break;
		case 'N':
			dryrun = true;
			break;
		case 'P':
			pretty = true;
			break;
		case 'Y':
			nis = true;
			break;
		}
	}

	if (quiet)
		freopen(_PATH_DEVNULL, "w", stderr);
	if (name == NULL)
		errx(EX_DATAERR, "group name required");
	if (GETGRNAM(name) != NULL)
		errx(EX_DATAERR, "group name `%s' already exists", name);
	cnf = get_userconfig(cfg);
	rc = groupadd(cnf, name, gr_gidpolicy(cnf, id), members, fd, dryrun,
	    pretty, precrypted);
	if (nis && rc == EXIT_SUCCESS && nis_update() == 0)
		pw_log(cnf, M_ADD, W_GROUP, "NIS maps updated");

	return (rc);
}