#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
typedef  int u_int ;
struct sigaction {void* sa_handler; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_flags; } ;
struct passwd {scalar_t__ pw_uid; char const* pw_name; char* pw_shell; char const* pw_dir; } ;
struct pam_conv {int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  shellbuf ;
typedef  int pid_t ;
struct TYPE_6__ {char* lc_class; } ;
typedef  TYPE_1__ login_cap_t ;
typedef  enum tristate { ____Placeholder_tristate } tristate ;
typedef  int /*<<< orphan*/  au_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_su ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  EPERM ; 
 int LOGIN_SETALL ; 
 int LOGIN_SETENV ; 
 int LOGIN_SETGROUP ; 
 int LOGIN_SETLOGIN ; 
 int LOGIN_SETMAC ; 
 int LOGIN_SETPATH ; 
 int LOGIN_SETPRIORITY ; 
 int LOGIN_SETRESOURCES ; 
 int LOGIN_SETUMASK ; 
 int LOG_AUTH ; 
 int /*<<< orphan*/  LOG_CONS ; 
 int LOG_ERR ; 
 int LOG_NOTICE ; 
 int LOG_WARNING ; 
 int MAXLOGNAME ; 
 int MAXPATHLEN ; 
 int NO ; 
 int /*<<< orphan*/  PAM_CHANGE_EXPIRED_AUTHTOK ; 
 int /*<<< orphan*/  PAM_END () ; 
 int /*<<< orphan*/  PAM_ESTABLISH_CRED ; 
 int PAM_NEW_AUTHTOK_REQD ; 
 int /*<<< orphan*/  PAM_RUSER ; 
 int /*<<< orphan*/  PAM_SET_ITEM (int /*<<< orphan*/ ,char const*) ; 
 int PAM_SUCCESS ; 
 int /*<<< orphan*/  PAM_TTY ; 
 int /*<<< orphan*/  PAM_USER ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTOU ; 
 void* SIG_DFL ; 
 void* SIG_IGN ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int UNSET ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WUNTRACED ; 
 int YES ; 
 char* _PATH_BSHELL ; 
 scalar_t__ audit_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  chdir (char const*) ; 
 int /*<<< orphan*/  chshell (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 char** environ ; 
 int /*<<< orphan*/  environ_pam ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  execv (char const*,char* const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  export_pam_environment () ; 
 int fork () ; 
 scalar_t__ getauid (int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 scalar_t__ geteuid () ; 
 char* getlogin () ; 
 int getopt (int,char**,char*) ; 
 int getpgid (int) ; 
 int getpgrp () ; 
 int getpid () ; 
 int getpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct passwd* getpwnam (char const*) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  login_close (TYPE_1__*) ; 
 TYPE_1__* login_getclass (char*) ; 
 TYPE_1__* login_getpwclass (struct passwd*) ; 
 char** malloc (int) ; 
 char const* ontty () ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  openpam_ttyconv ; 
 char* optarg ; 
 int optind ; 
 int pam_acct_mgmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pam_authenticate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pam_chauthtok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pam_get_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**) ; 
 char* pam_getenv (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pam_getenvlist (int /*<<< orphan*/ ) ; 
 int pam_open_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pam_setcred (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pam_start (char*,char const*,struct pam_conv*,int /*<<< orphan*/ *) ; 
 char* pam_strerror (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pamh ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  read (int,int*,int) ; 
 int /*<<< orphan*/  setenv (char*,char const*,int) ; 
 int /*<<< orphan*/  setpgid (int,int) ; 
 int /*<<< orphan*/  setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setusercontext (TYPE_1__*,struct passwd*,scalar_t__,int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  syslog (int,char*,char*,...) ; 
 int tcgetpgrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcsetpgrp (int /*<<< orphan*/ ,int) ; 
 char* ttyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	static char	*cleanenv;
	struct passwd	*pwd = NULL;
	struct pam_conv	conv = { openpam_ttyconv, NULL };
	enum tristate	iscsh;
	login_cap_t	*lc;
	union {
		const char	**a;
		char		* const *b;
	}		np;
	uid_t		ruid;
	pid_t		child_pid, child_pgrp, pid;
	int		asme, ch, asthem, fastlogin, prio, i, retcode,
			statusp, setmaclabel;
	u_int		setwhat;
	char		*username, *class, shellbuf[MAXPATHLEN];
	const char	*p, *user, *shell, *mytty, **nargv;
	const void	*v;
	struct sigaction sa, sa_int, sa_quit, sa_pipe;
	int temp, fds[2];
#ifdef USE_BSM_AUDIT
	const char	*aerr;
	au_id_t		 auid;
#endif

	p = shell = class = cleanenv = NULL;
	asme = asthem = fastlogin = statusp = 0;
	user = "root";
	iscsh = UNSET;
	setmaclabel = 0;

	while ((ch = getopt(argc, argv, "-flmsc:")) != -1)
		switch ((char)ch) {
		case 'f':
			fastlogin = 1;
			break;
		case '-':
		case 'l':
			asme = 0;
			asthem = 1;
			break;
		case 'm':
			asme = 1;
			asthem = 0;
			break;
		case 's':
			setmaclabel = 1;
			break;
		case 'c':
			class = optarg;
			break;
		case '?':
		default:
			usage();
		/* NOTREACHED */
		}

	if (optind < argc)
		user = argv[optind++];

	if (user == NULL)
		usage();
	/* NOTREACHED */

	/*
	 * Try to provide more helpful debugging output if su(1) is running
	 * non-setuid, or was run from a file system not mounted setuid.
	 */
	if (geteuid() != 0)
		errx(1, "not running setuid");

#ifdef USE_BSM_AUDIT
	if (getauid(&auid) < 0 && errno != ENOSYS) {
		syslog(LOG_AUTH | LOG_ERR, "getauid: %s", strerror(errno));
		errx(1, "Permission denied");
	}
#endif
	if (strlen(user) > MAXLOGNAME - 1) {
#ifdef USE_BSM_AUDIT
		if (audit_submit(AUE_su, auid,
		    EPERM, 1, "username too long: '%s'", user))
			errx(1, "Permission denied");
#endif
		errx(1, "username too long");
	}

	nargv = malloc(sizeof(char *) * (size_t)(argc + 4));
	if (nargv == NULL)
		errx(1, "malloc failure");

	nargv[argc + 3] = NULL;
	for (i = argc; i >= optind; i--)
		nargv[i + 3] = argv[i];
	np.a = &nargv[i + 3];

	argv += optind;

	errno = 0;
	prio = getpriority(PRIO_PROCESS, 0);
	if (errno)
		prio = 0;

	setpriority(PRIO_PROCESS, 0, -2);
	openlog("su", LOG_CONS, LOG_AUTH);

	/* get current login name, real uid and shell */
	ruid = getuid();
	username = getlogin();
	if (username != NULL)
		pwd = getpwnam(username);
	if (pwd == NULL || pwd->pw_uid != ruid)
		pwd = getpwuid(ruid);
	if (pwd == NULL) {
#ifdef USE_BSM_AUDIT
		if (audit_submit(AUE_su, auid, EPERM, 1,
		    "unable to determine invoking subject: '%s'", username))
			errx(1, "Permission denied");
#endif
		errx(1, "who are you?");
	}

	username = strdup(pwd->pw_name);
	if (username == NULL)
		err(1, "strdup failure");

	if (asme) {
		if (pwd->pw_shell != NULL && *pwd->pw_shell != '\0') {
			/* must copy - pwd memory is recycled */
			strlcpy(shellbuf, pwd->pw_shell,
			    sizeof(shellbuf));
			shell = shellbuf;
		}
		else {
			shell = _PATH_BSHELL;
			iscsh = NO;
		}
	}

	/* Do the whole PAM startup thing */
	retcode = pam_start("su", user, &conv, &pamh);
	if (retcode != PAM_SUCCESS) {
		syslog(LOG_ERR, "pam_start: %s", pam_strerror(pamh, retcode));
		errx(1, "pam_start: %s", pam_strerror(pamh, retcode));
	}

	PAM_SET_ITEM(PAM_RUSER, username);

	mytty = ttyname(STDERR_FILENO);
	if (!mytty)
		mytty = "tty";
	PAM_SET_ITEM(PAM_TTY, mytty);

	retcode = pam_authenticate(pamh, 0);
	if (retcode != PAM_SUCCESS) {
#ifdef USE_BSM_AUDIT
		if (audit_submit(AUE_su, auid, EPERM, 1, "bad su %s to %s on %s",
		    username, user, mytty))
			errx(1, "Permission denied");
#endif
		syslog(LOG_AUTH|LOG_WARNING, "BAD SU %s to %s on %s",
		    username, user, mytty);
		errx(1, "Sorry");
	}
#ifdef USE_BSM_AUDIT
	if (audit_submit(AUE_su, auid, 0, 0, "successful authentication"))
		errx(1, "Permission denied");
#endif
	retcode = pam_get_item(pamh, PAM_USER, &v);
	if (retcode == PAM_SUCCESS)
		user = v;
	else
		syslog(LOG_ERR, "pam_get_item(PAM_USER): %s",
		    pam_strerror(pamh, retcode));
	pwd = getpwnam(user);
	if (pwd == NULL) {
#ifdef USE_BSM_AUDIT
		if (audit_submit(AUE_su, auid, EPERM, 1,
		    "unknown subject: %s", user))
			errx(1, "Permission denied");
#endif
		errx(1, "unknown login: %s", user);
	}

	retcode = pam_acct_mgmt(pamh, 0);
	if (retcode == PAM_NEW_AUTHTOK_REQD) {
		retcode = pam_chauthtok(pamh,
			PAM_CHANGE_EXPIRED_AUTHTOK);
		if (retcode != PAM_SUCCESS) {
#ifdef USE_BSM_AUDIT
			aerr = pam_strerror(pamh, retcode);
			if (aerr == NULL)
				aerr = "Unknown PAM error";
			if (audit_submit(AUE_su, auid, EPERM, 1,
			    "pam_chauthtok: %s", aerr))
				errx(1, "Permission denied");
#endif
			syslog(LOG_ERR, "pam_chauthtok: %s",
			    pam_strerror(pamh, retcode));
			errx(1, "Sorry");
		}
	}
	if (retcode != PAM_SUCCESS) {
#ifdef USE_BSM_AUDIT
		if (audit_submit(AUE_su, auid, EPERM, 1, "pam_acct_mgmt: %s",
		    pam_strerror(pamh, retcode)))
			errx(1, "Permission denied");
#endif
		syslog(LOG_ERR, "pam_acct_mgmt: %s",
			pam_strerror(pamh, retcode));
		errx(1, "Sorry");
	}

	/* get target login information */
	if (class == NULL)
		lc = login_getpwclass(pwd);
	else {
		if (ruid != 0) {
#ifdef USE_BSM_AUDIT
			if (audit_submit(AUE_su, auid, EPERM, 1,
			    "only root may use -c"))
				errx(1, "Permission denied");
#endif
			errx(1, "only root may use -c");
		}
		lc = login_getclass(class);
		if (lc == NULL)
			err(1, "login_getclass");
		if (lc->lc_class == NULL || strcmp(class, lc->lc_class) != 0)
			errx(1, "unknown class: %s", class);
	}

	/* if asme and non-standard target shell, must be root */
	if (asme) {
		if (ruid != 0 && !chshell(pwd->pw_shell))
			errx(1, "permission denied (shell)");
	}
	else if (pwd->pw_shell && *pwd->pw_shell) {
		shell = pwd->pw_shell;
		iscsh = UNSET;
	}
	else {
		shell = _PATH_BSHELL;
		iscsh = NO;
	}

	/* if we're forking a csh, we want to slightly muck the args */
	if (iscsh == UNSET) {
		p = strrchr(shell, '/');
		if (p)
			++p;
		else
			p = shell;
		iscsh = strcmp(p, "csh") ? (strcmp(p, "tcsh") ? NO : YES) : YES;
	}
	setpriority(PRIO_PROCESS, 0, prio);

	/*
	 * PAM modules might add supplementary groups in pam_setcred(), so
	 * initialize them first.
	 */
	if (setusercontext(lc, pwd, pwd->pw_uid, LOGIN_SETGROUP) < 0)
		err(1, "setusercontext");

	retcode = pam_setcred(pamh, PAM_ESTABLISH_CRED);
	if (retcode != PAM_SUCCESS) {
		syslog(LOG_ERR, "pam_setcred: %s",
		    pam_strerror(pamh, retcode));
		errx(1, "failed to establish credentials.");
	}
	if (asthem) {
		retcode = pam_open_session(pamh, 0);
		if (retcode != PAM_SUCCESS) {
			syslog(LOG_ERR, "pam_open_session: %s",
			    pam_strerror(pamh, retcode));
			errx(1, "failed to open session.");
		}
	}

	/*
	 * We must fork() before setuid() because we need to call
	 * pam_setcred(pamh, PAM_DELETE_CRED) as root.
	 */
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, &sa_int);
	sigaction(SIGQUIT, &sa, &sa_quit);
	sigaction(SIGPIPE, &sa, &sa_pipe);
	sa.sa_handler = SIG_DFL;
	sigaction(SIGTSTP, &sa, NULL);
	statusp = 1;
	if (pipe(fds) == -1) {
		PAM_END();
		err(1, "pipe");
	}
	child_pid = fork();
	switch (child_pid) {
	default:
		sa.sa_handler = SIG_IGN;
		sigaction(SIGTTOU, &sa, NULL);
		close(fds[0]);
		setpgid(child_pid, child_pid);
		if (tcgetpgrp(STDERR_FILENO) == getpgrp())
			tcsetpgrp(STDERR_FILENO, child_pid);
		close(fds[1]);
		sigaction(SIGPIPE, &sa_pipe, NULL);
		while ((pid = waitpid(child_pid, &statusp, WUNTRACED)) != -1) {
			if (WIFSTOPPED(statusp)) {
				child_pgrp = getpgid(child_pid);
				if (tcgetpgrp(STDERR_FILENO) == child_pgrp)
					tcsetpgrp(STDERR_FILENO, getpgrp());
				kill(getpid(), SIGSTOP);
				if (tcgetpgrp(STDERR_FILENO) == getpgrp()) {
					child_pgrp = getpgid(child_pid);
					tcsetpgrp(STDERR_FILENO, child_pgrp);
				}
				kill(child_pid, SIGCONT);
				statusp = 1;
				continue;
			}
			break;
		}
		tcsetpgrp(STDERR_FILENO, getpgrp());
		if (pid == -1)
			err(1, "waitpid");
		PAM_END();
		exit(WEXITSTATUS(statusp));
	case -1:
		PAM_END();
		err(1, "fork");
	case 0:
		close(fds[1]);
		read(fds[0], &temp, 1);
		close(fds[0]);
		sigaction(SIGPIPE, &sa_pipe, NULL);
		sigaction(SIGINT, &sa_int, NULL);
		sigaction(SIGQUIT, &sa_quit, NULL);

		/*
		 * Set all user context except for: Environmental variables
		 * Umask Login records (wtmp, etc) Path
		 */
		setwhat = LOGIN_SETALL & ~(LOGIN_SETENV | LOGIN_SETUMASK |
			   LOGIN_SETLOGIN | LOGIN_SETPATH | LOGIN_SETGROUP |
			   LOGIN_SETMAC);
		/*
		 * If -s is present, also set the MAC label.
		 */
		if (setmaclabel)
			setwhat |= LOGIN_SETMAC;
		/*
		 * Don't touch resource/priority settings if -m has been used
		 * or -l and -c hasn't, and we're not su'ing to root.
		 */
		if ((asme || (!asthem && class == NULL)) && pwd->pw_uid)
			setwhat &= ~(LOGIN_SETPRIORITY | LOGIN_SETRESOURCES);
		if (setusercontext(lc, pwd, pwd->pw_uid, setwhat) < 0)
			err(1, "setusercontext");

		if (!asme) {
			if (asthem) {
				p = getenv("TERM");
				environ = &cleanenv;
			}

			if (asthem || pwd->pw_uid)
				setenv("USER", pwd->pw_name, 1);
			setenv("HOME", pwd->pw_dir, 1);
			setenv("SHELL", shell, 1);

			if (asthem) {
				/*
				 * Add any environmental variables that the
				 * PAM modules may have set.
				 */
				environ_pam = pam_getenvlist(pamh);
				if (environ_pam)
					export_pam_environment();

				/* set the su'd user's environment & umask */
				setusercontext(lc, pwd, pwd->pw_uid,
					LOGIN_SETPATH | LOGIN_SETUMASK |
					LOGIN_SETENV);
				if (p)
					setenv("TERM", p, 1);

				p = pam_getenv(pamh, "HOME");
				if (chdir(p ? p : pwd->pw_dir) < 0)
					errx(1, "no directory");
			}
		}
		login_close(lc);

		if (iscsh == YES) {
			if (fastlogin)
				*np.a-- = "-f";
			if (asme)
				*np.a-- = "-m";
		}
		/* csh strips the first character... */
		*np.a = asthem ? "-su" : iscsh == YES ? "_su" : "su";

		if (ruid != 0)
			syslog(LOG_NOTICE, "%s to %s%s", username, user,
			    ontty());

		execv(shell, np.b);
		err(1, "%s", shell);
	}
}