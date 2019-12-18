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
struct passwd {char const* pw_name; char const* pw_dir; char const* pw_shell; int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_gid; } ;
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 int LOGIN_SETALL ; 
 int LOGIN_SETENV ; 
 int LOGIN_SETGROUP ; 
 int LOGIN_SETLOGIN ; 
 int LOGIN_SETPATH ; 
 char const* _PATH_BSHELL ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  endpwent () ; 
 char** environ ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ execlp (char const*,char const*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_user_info (char const*,struct passwd const**,int /*<<< orphan*/ **) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int jail_attach (int) ; 
 int /*<<< orphan*/  jail_errmsg ; 
 int jail_getid (char*) ; 
 int /*<<< orphan*/  login_close (int /*<<< orphan*/ *) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  setenv (char*,char const*,int) ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 scalar_t__ setusercontext (int /*<<< orphan*/ *,struct passwd const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int jid;
	login_cap_t *lcap = NULL;
	int ch, clean, uflag, Uflag;
	char *cleanenv;
	const struct passwd *pwd = NULL;
	const char *username, *shell, *term;

	ch = clean = uflag = Uflag = 0;
	username = NULL;

	while ((ch = getopt(argc, argv, "lnu:U:")) != -1) {
		switch (ch) {
		case 'l':
			clean = 1;
			break;
		case 'n':
			/* Specified name, now unused */
			break;
		case 'u':
			username = optarg;
			uflag = 1;
			break;
		case 'U':
			username = optarg;
			Uflag = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (argc < 1)
		usage();
	if (uflag && Uflag)
		usage();
	if (uflag || (clean && !Uflag))
		/* User info from the home environment */
		get_user_info(username, &pwd, &lcap);

	/* Attach to the jail */
	jid = jail_getid(argv[0]);
	if (jid < 0)
		errx(1, "%s", jail_errmsg);
	if (jail_attach(jid) == -1)
		err(1, "jail_attach(%d)", jid);
	if (chdir("/") == -1)
		err(1, "chdir(): /");

	/* Set up user environment */
	if (clean || username != NULL) {
		if (Uflag)
			/* User info from the jail environment */
			get_user_info(username, &pwd, &lcap);
		if (clean) {
			term = getenv("TERM");
			cleanenv = NULL;
			environ = &cleanenv;
			setenv("PATH", "/bin:/usr/bin", 1);
			if (term != NULL)
				setenv("TERM", term, 1);
		}
		if (setgid(pwd->pw_gid) != 0)
			err(1, "setgid");
		if (setusercontext(lcap, pwd, pwd->pw_uid, username
		    ? LOGIN_SETALL & ~LOGIN_SETGROUP & ~LOGIN_SETLOGIN
		    : LOGIN_SETPATH | LOGIN_SETENV) != 0)
			err(1, "setusercontext");
		login_close(lcap);
		setenv("USER", pwd->pw_name, 1);
		setenv("HOME", pwd->pw_dir, 1);
		setenv("SHELL",
		    *pwd->pw_shell ? pwd->pw_shell : _PATH_BSHELL, 1);
		if (clean && chdir(pwd->pw_dir) < 0)
			err(1, "chdir: %s", pwd->pw_dir);
		endpwent();
	}

	/* Run the specified command, or the shell */
	if (argc > 1) {
		if (execvp(argv[1], argv + 1) < 0)
			err(1, "execvp: %s", argv[1]);
	} else {
		if (!(shell = getenv("SHELL")))
			shell = _PATH_BSHELL;
		if (execlp(shell, shell, "-i", NULL) < 0)
			err(1, "execlp: %s", shell);
	}
	exit(0);
}