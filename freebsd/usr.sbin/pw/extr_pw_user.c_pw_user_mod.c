#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char* uintmax_t ;
typedef  scalar_t__ uid_t ;
typedef  void* time_t ;
struct userconf {char* nispasswd; char* dotdir; scalar_t__ homemode; int /*<<< orphan*/  default_password; int /*<<< orphan*/  shells; int /*<<< orphan*/  shelldir; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct passwd {char* pw_name; int pw_fields; scalar_t__ pw_uid; scalar_t__ pw_gid; void* pw_change; void* pw_expire; char* pw_shell; char* pw_class; char* pw_dir; char* pw_gecos; int /*<<< orphan*/  pw_passwd; } ;
struct group {scalar_t__ gr_gid; char** gr_mem; char* gr_name; } ;
typedef  scalar_t__ mode_t ;
typedef  int /*<<< orphan*/  login_cap_t ;
typedef  scalar_t__ intmax_t ;
struct TYPE_7__ {scalar_t__ _altdir; } ;
struct TYPE_6__ {int fd; int /*<<< orphan*/  rootfd; } ;
struct TYPE_5__ {size_t sl_cur; char** sl_str; } ;
typedef  TYPE_1__ StringList ;

/* Variables and functions */
 int /*<<< orphan*/  ENDGRENT () ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_NOPERM ; 
 int /*<<< orphan*/  EX_NOUSER ; 
 int /*<<< orphan*/  EX_OSFILE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 struct group* GETGRENT () ; 
 struct group* GETGRGID (scalar_t__) ; 
 struct group* GETGRNAM (char*) ; 
 struct passwd* GETPWNAM (char*) ; 
 struct passwd* GETPWUID (scalar_t__) ; 
 int /*<<< orphan*/  GID_MAX ; 
 int /*<<< orphan*/  M_UPDATE ; 
 scalar_t__ PWALTDIR () ; 
 TYPE_4__ PWF ; 
 scalar_t__ PWF_ALT ; 
 scalar_t__ PWF_REGULAR ; 
 int /*<<< orphan*/  SETGRENT () ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UID_MAX ; 
 int /*<<< orphan*/  W_USER ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int _PWF_FILES ; 
 int _PWF_NIS ; 
 int _PWF_SOURCE ; 
 int /*<<< orphan*/  chggrent (char*,struct group*) ; 
 TYPE_3__ conf ; 
 int /*<<< orphan*/  create_and_populate_homedir (struct userconf*,struct passwd*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct group*) ; 
 int /*<<< orphan*/  freopen (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int fstatat (int /*<<< orphan*/ ,char*,struct stat*,int /*<<< orphan*/ ) ; 
 struct userconf* get_userconfig (char const*) ; 
 scalar_t__ geteuid () ; 
 int getopt (int,char**,char*) ; 
 struct group* gr_add (struct group*,char*) ; 
 int /*<<< orphan*/  group_from_name_or_id (char*) ; 
 int /*<<< orphan*/  login_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * login_getpwclass (struct passwd*) ; 
 int /*<<< orphan*/ * login_setcryptfmt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ nis_update () ; 
 char* optarg ; 
 void* parse_date (void*,char*) ; 
 int /*<<< orphan*/  passwd_val (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perform_chgpwent (char*,struct passwd*,char*) ; 
 int print_user (struct passwd*,int,int) ; 
 int pw_checkfd (char*) ; 
 scalar_t__ pw_checkid (char*,int /*<<< orphan*/ ) ; 
 char* pw_checkname (char*,int) ; 
 int /*<<< orphan*/  pw_log (struct userconf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pw_password (struct userconf*,char*,int) ; 
 int pw_set_passwd (struct passwd*,int,int,int) ; 
 char* shell_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  split_groups (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strspn (char*,char*) ; 
 void* time (int /*<<< orphan*/ *) ; 
 scalar_t__ validate_mode (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
pw_user_mod(int argc, char **argv, char *arg1)
{
	struct userconf *cnf;
	struct passwd *pwd;
	struct group *grp;
	StringList *groups = NULL;
	char args[] = "C:qn:u:c:d:e:p:g:G:mM:l:k:s:w:L:h:H:NPYy:";
	const char *cfg = NULL;
	char *gecos, *homedir, *grname, *name, *newname, *walk, *skel, *shell;
	char *passwd, *class, *nispasswd;
	login_cap_t *lc;
	struct stat st;
	intmax_t id = -1;
	int ch, fd = -1;
	size_t i, j;
	bool quiet, createhome, pretty, dryrun, nis, edited;
	bool precrypted;
	mode_t homemode = 0;
	time_t expire_time, password_time, now;

	expire_time = password_time = -1;
	gecos = homedir = grname = name = newname = skel = shell =NULL;
	passwd = NULL;
	class = nispasswd = NULL;
	quiet = createhome = pretty = dryrun = nis = precrypted = false;
	edited = false;
	now = time(NULL);

	if (arg1 != NULL) {
		if (arg1[strspn(arg1, "0123456789")] == '\0')
			id = pw_checkid(arg1, UID_MAX);
		else
			name = arg1;
	}

	while ((ch = getopt(argc, argv, args)) != -1) {
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
		case 'c':
			gecos = pw_checkname(optarg, 1);
			break;
		case 'd':
			homedir = optarg;
			break;
		case 'e':
			expire_time = parse_date(now, optarg);
			break;
		case 'p':
			password_time = parse_date(now, optarg);
			break;
		case 'g':
			group_from_name_or_id(optarg);
			grname = optarg;
			break;
		case 'G':
			split_groups(&groups, optarg);
			break;
		case 'm':
			createhome = true;
			break;
		case 'M':
			homemode = validate_mode(optarg);
			break;
		case 'l':
			newname = optarg;
			break;
		case 'k':
			walk = skel = optarg;
			if (*walk == '/')
				walk++;
			if (fstatat(conf.rootfd, walk, &st, 0) == -1)
				errx(EX_OSFILE, "skeleton `%s' does not "
				    "exists", skel);
			if (!S_ISDIR(st.st_mode))
				errx(EX_OSFILE, "skeleton `%s' is not a "
				    "directory", skel);
			break;
		case 's':
			shell = optarg;
			break;
		case 'w':
			passwd = optarg;
			break;
		case 'L':
			class = pw_checkname(optarg, 0);
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
		case 'N':
			dryrun = true;
			break;
		case 'P':
			pretty = true;
			break;
		case 'y':
			nispasswd = optarg;
			break;
		case 'Y':
			nis = true;
			break;
		}
	}

	if (geteuid() != 0 && ! dryrun)
		errx(EX_NOPERM, "you must be root");

	if (quiet)
		freopen(_PATH_DEVNULL, "w", stderr);

	cnf = get_userconfig(cfg);

	if (id < 0 && name == NULL)
		errx(EX_DATAERR, "username or id required");

	pwd = (name != NULL) ? GETPWNAM(pw_checkname(name, 0)) : GETPWUID(id);
	if (pwd == NULL) {
		if (name == NULL)
			errx(EX_NOUSER, "no such uid `%ju'",
			    (uintmax_t) id);
		errx(EX_NOUSER, "no such user `%s'", name);
	}

	if (name == NULL)
		name = pwd->pw_name;

	if (nis && nispasswd == NULL)
		nispasswd = cnf->nispasswd;

	if (PWF._altdir == PWF_REGULAR &&
	    ((pwd->pw_fields & _PWF_SOURCE) != _PWF_FILES)) {
		if ((pwd->pw_fields & _PWF_SOURCE) == _PWF_NIS) {
			if (!nis && nispasswd && *nispasswd != '/')
				errx(EX_NOUSER, "Cannot modify NIS user `%s'",
				    name);
		} else {
			errx(EX_NOUSER, "Cannot modify non local user `%s'",
			    name);
		}
	}

	if (newname) {
		if (strcmp(pwd->pw_name, "root") == 0)
			errx(EX_DATAERR, "can't rename `root' account");
		if (strcmp(pwd->pw_name, newname) != 0) {
			pwd->pw_name = pw_checkname(newname, 0);
			edited = true;
		}
	}

	if (id >= 0 && pwd->pw_uid != id) {
		pwd->pw_uid = id;
		edited = true;
		if (pwd->pw_uid != 0 && strcmp(pwd->pw_name, "root") == 0)
			errx(EX_DATAERR, "can't change uid of `root' account");
		if (pwd->pw_uid == 0 && strcmp(pwd->pw_name, "root") != 0)
			warnx("WARNING: account `%s' will have a uid of 0 "
			    "(superuser access!)", pwd->pw_name);
	}

	if (grname && pwd->pw_uid != 0) {
		grp = GETGRNAM(grname);
		if (grp == NULL)
			grp = GETGRGID(pw_checkid(grname, GID_MAX));
		if (grp->gr_gid != pwd->pw_gid) {
			pwd->pw_gid = grp->gr_gid;
			edited = true;
		}
	}


	if (password_time >= 0 && pwd->pw_change != password_time) {
		pwd->pw_change = password_time;
		edited = true;
	}

	if (expire_time >= 0 && pwd->pw_expire != expire_time) {
		pwd->pw_expire = expire_time;
		edited = true;
	}

	if (shell) {
		shell = shell_path(cnf->shelldir, cnf->shells, shell);
		if (shell == NULL)
			shell = "";
		if (strcmp(shell, pwd->pw_shell) != 0) {
			pwd->pw_shell = shell;
			edited = true;
		}
	}

	if (class && strcmp(pwd->pw_class, class) != 0) {
		pwd->pw_class = class;
		edited = true;
	}

	if (homedir && strcmp(pwd->pw_dir, homedir) != 0) {
		pwd->pw_dir = homedir;
		edited = true;
		if (fstatat(conf.rootfd, pwd->pw_dir, &st, 0) == -1) {
			if (!createhome)
				warnx("WARNING: home `%s' does not exist",
				    pwd->pw_dir);
		} else if (!S_ISDIR(st.st_mode)) {
			warnx("WARNING: home `%s' is not a directory",
			    pwd->pw_dir);
		}
	}

	if (passwd && conf.fd == -1) {
		lc = login_getpwclass(pwd);
		if (lc == NULL || login_setcryptfmt(lc, "sha512", NULL) == NULL)
			warn("setting crypt(3) format");
		login_close(lc);
		cnf->default_password = passwd_val(passwd,
		    cnf->default_password);
		pwd->pw_passwd = pw_password(cnf, pwd->pw_name, dryrun);
		edited = true;
	}

	if (gecos && strcmp(pwd->pw_gecos, gecos) != 0) {
		pwd->pw_gecos = gecos;
		edited = true;
	}

	if (fd != -1)
		edited = pw_set_passwd(pwd, fd, precrypted, true);

	if (dryrun)
		return (print_user(pwd, pretty, false));

	if (edited) /* Only updated this if required */
		perform_chgpwent(name, pwd, nis ? nispasswd : NULL);
	/* Now perform the needed changes concern groups */
	if (groups != NULL) {
		/* Delete User from groups using old name */
		SETGRENT();
		while ((grp = GETGRENT()) != NULL) {
			if (grp->gr_mem == NULL)
				continue;
			for (i = 0; grp->gr_mem[i] != NULL; i++) {
				if (strcmp(grp->gr_mem[i] , name) != 0)
					continue;
				for (j = i; grp->gr_mem[j] != NULL ; j++)
					grp->gr_mem[j] = grp->gr_mem[j+1];
				chggrent(grp->gr_name, grp);
				break;
			}
		}
		ENDGRENT();
		/* Add the user to the needed groups */
		for (i = 0; i < groups->sl_cur; i++) {
			grp = GETGRNAM(groups->sl_str[i]);
			grp = gr_add(grp, pwd->pw_name);
			if (grp == NULL)
				continue;
			chggrent(grp->gr_name, grp);
			free(grp);
		}
	}
	/* In case of rename we need to walk over the different groups */
	if (newname) {
		SETGRENT();
		while ((grp = GETGRENT()) != NULL) {
			if (grp->gr_mem == NULL)
				continue;
			for (i = 0; grp->gr_mem[i] != NULL; i++) {
				if (strcmp(grp->gr_mem[i], name) != 0)
					continue;
				grp->gr_mem[i] = newname;
				chggrent(grp->gr_name, grp);
				break;
			}
		}
	}

	/* go get a current version of pwd */
	if (newname)
		name = newname;
	pwd = GETPWNAM(name);
	if (pwd == NULL)
		errx(EX_NOUSER, "user '%s' disappeared during update", name);
	grp = GETGRGID(pwd->pw_gid);
	pw_log(cnf, M_UPDATE, W_USER, "%s(%ju):%s(%ju):%s:%s:%s",
	    pwd->pw_name, (uintmax_t)pwd->pw_uid,
	    grp ? grp->gr_name : "unknown",
	    (uintmax_t)(grp ? grp->gr_gid : (uid_t)-1),
	    pwd->pw_gecos, pwd->pw_dir, pwd->pw_shell);

	/*
	 * Let's create and populate the user's home directory. Note
	 * that this also `works' for editing users if -m is used, but
	 * existing files will *not* be overwritten.
	 */
	if (PWALTDIR() != PWF_ALT && createhome && pwd->pw_dir &&
	    *pwd->pw_dir == '/' && pwd->pw_dir[1]) {
		if (!skel)
			skel = cnf->dotdir;
		if (homemode == 0)
			homemode = cnf->homemode;
		create_and_populate_homedir(cnf, pwd, skel, homemode, true);
	}

	if (nis && nis_update() == 0)
		pw_log(cnf, M_UPDATE, W_USER, "NIS maps updated");

	return (EXIT_SUCCESS);
}