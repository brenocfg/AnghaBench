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
struct group {char* gr_name; scalar_t__ gr_gid; int /*<<< orphan*/ * gr_mem; } ;
typedef  scalar_t__ intmax_t ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  EX_IOERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 struct group* GETGRNAM (char*) ; 
 int /*<<< orphan*/  GID_MAX ; 
 int /*<<< orphan*/  M_UPDATE ; 
 int /*<<< orphan*/  W_GROUP ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int chggrent (char*,struct group*) ; 
 int /*<<< orphan*/  delete_members (struct group*,char*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freopen (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct userconf* get_userconfig (char const*) ; 
 struct group* getgroup (char*,scalar_t__,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  grp_add_members (struct group**,char*) ; 
 int /*<<< orphan*/  grp_set_passwd (struct group*,int,int,int) ; 
 scalar_t__ nis_update () ; 
 char* optarg ; 
 int /*<<< orphan*/  print_group (struct group*,int) ; 
 int pw_checkfd (char*) ; 
 scalar_t__ pw_checkid (char*,int /*<<< orphan*/ ) ; 
 char* pw_checkname (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pw_log (struct userconf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strspn (char*,char*) ; 

int
pw_group_mod(int argc, char **argv, char *arg1)
{
	struct userconf *cnf;
	struct group *grp = NULL;
	const char *cfg = NULL;
	char *oldmembers = NULL;
	char *members = NULL;
	char *newmembers = NULL;
	char *newname = NULL;
	char *name = NULL;
	intmax_t id = -1;
	int ch, rc, fd = -1;
	bool quiet, pretty, dryrun, nis, precrypted;

	quiet = pretty = dryrun = nis = precrypted = false;

	if (arg1 != NULL) {
		if (arg1[strspn(arg1, "0123456789")] == '\0')
			id = pw_checkid(arg1, GID_MAX);
		else
			name = arg1;
	}

	while ((ch = getopt(argc, argv, "C:qn:d:g:l:h:H:M:m:NPY")) != -1) {
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
		case 'd':
			oldmembers = optarg;
			break;
		case 'l':
			newname = optarg;
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
		case 'm':
			newmembers = optarg;
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
	cnf = get_userconfig(cfg);
	grp = getgroup(name, id, true);
	if (name == NULL)
		name = grp->gr_name;
	if (id > 0)
		grp->gr_gid = id;

	if (newname != NULL)
		grp->gr_name = pw_checkname(newname, 0);

	grp_set_passwd(grp, true, fd, precrypted);
	/*
	 * Keep the same logic as old code for now:
	 * if -M is passed, -d and -m are ignored
	 * then id -d, -m is ignored
	 * last is -m
	 */

	if (members) {
		grp->gr_mem = NULL;
		grp_add_members(&grp, members);
	} else if (oldmembers) {
		delete_members(grp, oldmembers);
	} else if (newmembers) {
		grp_add_members(&grp, newmembers);
	}

	if (dryrun) {
		print_group(grp, pretty);
		return (EXIT_SUCCESS);
	}

	if ((rc = chggrent(name, grp)) != 0) {
		if (rc == -1)
			errx(EX_IOERR, "group '%s' not available (NIS?)",
			    grp->gr_name);
		else
			err(EX_IOERR, "group update");
	}

	if (newname)
		name = newname;

	/* grp may have been invalidated */
	if ((grp = GETGRNAM(name)) == NULL)
		errx(EX_SOFTWARE, "group disappeared during update");

	pw_log(cnf, M_UPDATE, W_GROUP, "%s(%ju)", grp->gr_name,
	    (uintmax_t)grp->gr_gid);

	if (nis && nis_update() == 0)
		pw_log(cnf, M_UPDATE, W_GROUP, "NIS maps updated");

	return (EXIT_SUCCESS);
}