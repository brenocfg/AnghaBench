#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct userconf {char* nispasswd; } ;
struct stat {int dummy; } ;
struct passwd {int pw_fields; scalar_t__ pw_uid; char* pw_name; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_dir; } ;
struct group {char** gr_mem; int /*<<< orphan*/  gr_name; } ;
typedef  scalar_t__ intmax_t ;
typedef  int /*<<< orphan*/  home ;
typedef  int /*<<< orphan*/  file ;
struct TYPE_4__ {scalar_t__ _altdir; } ;
struct TYPE_3__ {int /*<<< orphan*/  rootfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDGRENT () ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_IOERR ; 
 int /*<<< orphan*/  EX_NOUSER ; 
 int /*<<< orphan*/  F_OK ; 
 struct group* GETGRENT () ; 
 struct group* GETGRGID (int /*<<< orphan*/ ) ; 
 struct group* GETGRNAM (char*) ; 
 struct passwd* GETPWNAM (int /*<<< orphan*/ ) ; 
 struct passwd* GETPWUID (scalar_t__) ; 
 int LOGNAMESIZE ; 
 int MAXLOGNAME ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  M_DELETE ; 
 scalar_t__ PWALTDIR () ; 
 TYPE_2__ PWF ; 
 scalar_t__ PWF_ALT ; 
 scalar_t__ PWF_REGULAR ; 
 int /*<<< orphan*/  SETGRENT () ; 
 int /*<<< orphan*/  UID_MAX ; 
 int /*<<< orphan*/  W_USER ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 char* _PATH_MAILDIR ; 
 int _PWF_FILES ; 
 int _PWF_NIS ; 
 int _PWF_SOURCE ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chggrent (char*,struct group*) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  delgrent (struct group*) ; 
 int delnispwent (char*,char*) ; 
 int delpwent (struct passwd*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freopen (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int fstatat (int /*<<< orphan*/ ,char*,struct stat*,int /*<<< orphan*/ ) ; 
 struct userconf* get_userconfig (char const*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * getpwuid (scalar_t__) ; 
 char* optarg ; 
 scalar_t__ pw_checkid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pw_checkname (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pw_log (struct userconf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rm_r (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  rmat (scalar_t__) ; 
 int /*<<< orphan*/  rmopie (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 size_t strspn (char*,char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  unlinkat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
pw_user_del(int argc, char **argv, char *arg1)
{
	struct userconf *cnf = NULL;
	struct passwd *pwd = NULL;
	struct group *gr, *grp;
	char *name = NULL;
	char grname[MAXLOGNAME];
	char *nispasswd = NULL;
	char file[MAXPATHLEN];
	char home[MAXPATHLEN];
	const char *cfg = NULL;
	struct stat st;
	intmax_t id = -1;
	int ch, rc;
	bool nis = false;
	bool deletehome = false;
	bool quiet = false;

	if (arg1 != NULL) {
		if (arg1[strspn(arg1, "0123456789")] == '\0')
			id = pw_checkid(arg1, UID_MAX);
		else
			name = arg1;
	}

	while ((ch = getopt(argc, argv, "C:qn:u:rYy:")) != -1) {
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
		case 'u':
			id = pw_checkid(optarg, UID_MAX);
			break;
		case 'r':
			deletehome = true;
			break;
		case 'y':
			nispasswd = optarg;
			break;
		case 'Y':
			nis = true;
			break;
		}
	}

	if (quiet)
		freopen(_PATH_DEVNULL, "w", stderr);

	if (id < 0 && name == NULL)
		errx(EX_DATAERR, "username or id required");

	cnf = get_userconfig(cfg);

	if (nispasswd == NULL)
		nispasswd = cnf->nispasswd;

	pwd = (name != NULL) ? GETPWNAM(pw_checkname(name, 0)) : GETPWUID(id);
	if (pwd == NULL) {
		if (name == NULL)
			errx(EX_NOUSER, "no such uid `%ju'", (uintmax_t) id);
		errx(EX_NOUSER, "no such user `%s'", name);
	}

	if (PWF._altdir == PWF_REGULAR &&
	    ((pwd->pw_fields & _PWF_SOURCE) != _PWF_FILES)) {
		if ((pwd->pw_fields & _PWF_SOURCE) == _PWF_NIS) {
			if (!nis && nispasswd && *nispasswd != '/')
				errx(EX_NOUSER, "Cannot remove NIS user `%s'",
				    name);
		} else {
			errx(EX_NOUSER, "Cannot remove non local user `%s'",
			    name);
		}
	}

	id = pwd->pw_uid;
	if (name == NULL)
		name = pwd->pw_name;

	if (strcmp(pwd->pw_name, "root") == 0)
		errx(EX_DATAERR, "cannot remove user 'root'");

	/* Remove opie record from /etc/opiekeys */
	if (PWALTDIR() != PWF_ALT)
		rmopie(pwd->pw_name);

	if (!PWALTDIR()) {
		/* Remove crontabs */
		snprintf(file, sizeof(file), "/var/cron/tabs/%s", pwd->pw_name);
		if (access(file, F_OK) == 0) {
			snprintf(file, sizeof(file), "crontab -u %s -r",
			    pwd->pw_name);
			system(file);
		}
	}

	/*
	 * Save these for later, since contents of pwd may be
	 * invalidated by deletion
	 */
	snprintf(file, sizeof(file), "%s/%s", _PATH_MAILDIR, pwd->pw_name);
	strlcpy(home, pwd->pw_dir, sizeof(home));
	gr = GETGRGID(pwd->pw_gid);
	if (gr != NULL)
		strlcpy(grname, gr->gr_name, LOGNAMESIZE);
	else
		grname[0] = '\0';

	rc = delpwent(pwd);
	if (rc == -1)
		err(EX_IOERR, "user '%s' does not exist", pwd->pw_name);
	else if (rc != 0)
		err(EX_IOERR, "passwd update");

	if (nis && nispasswd && *nispasswd=='/') {
		rc = delnispwent(nispasswd, name);
		if (rc == -1)
			warnx("WARNING: user '%s' does not exist in NIS passwd",
			    pwd->pw_name);
		else if (rc != 0)
			warn("WARNING: NIS passwd update");
	}

	grp = GETGRNAM(name);
	if (grp != NULL &&
	    (grp->gr_mem == NULL || *grp->gr_mem == NULL) &&
	    strcmp(name, grname) == 0)
		delgrent(GETGRNAM(name));
	SETGRENT();
	while ((grp = GETGRENT()) != NULL) {
		int i, j;
		char group[MAXLOGNAME];
		if (grp->gr_mem == NULL)
			continue;

		for (i = 0; grp->gr_mem[i] != NULL; i++) {
			if (strcmp(grp->gr_mem[i], name) != 0)
				continue;

			for (j = i; grp->gr_mem[j] != NULL; j++)
				grp->gr_mem[j] = grp->gr_mem[j+1];
			strlcpy(group, grp->gr_name, MAXLOGNAME);
			chggrent(group, grp);
		}
	}
	ENDGRENT();

	pw_log(cnf, M_DELETE, W_USER, "%s(%ju) account removed", name,
	    (uintmax_t)id);

	/* Remove mail file */
	if (PWALTDIR() != PWF_ALT)
		unlinkat(conf.rootfd, file + 1, 0);

	/* Remove at jobs */
	if (!PWALTDIR() && getpwuid(id) == NULL)
		rmat(id);

	/* Remove home directory and contents */
	if (PWALTDIR() != PWF_ALT && deletehome && *home == '/' &&
	    GETPWUID(id) == NULL &&
	    fstatat(conf.rootfd, home + 1, &st, 0) != -1) {
		rm_r(conf.rootfd, home, id);
		pw_log(cnf, M_DELETE, W_USER, "%s(%ju) home '%s' %s"
		    "removed", name, (uintmax_t)id, home,
		     fstatat(conf.rootfd, home + 1, &st, 0) == -1 ? "" : "not "
		     "completely ");
	}

	return (EXIT_SUCCESS);
}