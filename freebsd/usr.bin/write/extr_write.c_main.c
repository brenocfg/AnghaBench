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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  time_t ;
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FCNTL ; 
 int /*<<< orphan*/  CAP_FCNTL_GETFL ; 
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_IOCTL ; 
 int /*<<< orphan*/  CAP_LOOKUP ; 
 int /*<<< orphan*/  CAP_PWRITE ; 
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 unsigned long FIODGNAME ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 unsigned long TIOCGETA ; 
 unsigned long TIOCGWINSZ ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 int /*<<< orphan*/  caph_cache_tzdata () ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_fcntls_limit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_ioctls_limit (int,unsigned long*,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_rights_limit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_write (int,char*,char*,char const*) ; 
 int /*<<< orphan*/  done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fileno (int /*<<< orphan*/ ) ; 
 char* getlogin () ; 
 int getopt (int,char**,char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ isatty (int) ; 
 int /*<<< orphan*/  nitems (unsigned long*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  search_utmp (int,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setutxent () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ term_chk (int,char*,int*,int /*<<< orphan*/ *,int) ; 
 char* ttyname (int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  utmp_chk (char*,char*) ; 

int
main(int argc, char **argv)
{
	unsigned long cmds[] = { TIOCGETA, TIOCGWINSZ, FIODGNAME };
	cap_rights_t rights;
	struct passwd *pwd;
	time_t atime;
	uid_t myuid;
	int msgsok, myttyfd;
	char tty[MAXPATHLEN], *mytty;
	const char *login;
	int devfd;

	(void)setlocale(LC_CTYPE, "");

	devfd = open(_PATH_DEV, O_RDONLY);
	if (devfd < 0)
		err(1, "open(/dev)");
	cap_rights_init(&rights, CAP_FCNTL, CAP_FSTAT, CAP_IOCTL, CAP_LOOKUP,
	    CAP_PWRITE);
	if (caph_rights_limit(devfd, &rights) < 0)
		err(1, "can't limit devfd rights");

	/*
	 * Can't use capsicum helpers here because we need the additional
	 * FIODGNAME ioctl.
	 */
	cap_rights_init(&rights, CAP_FCNTL, CAP_FSTAT, CAP_IOCTL, CAP_READ,
	    CAP_WRITE);
	if (caph_rights_limit(STDIN_FILENO, &rights) < 0 ||
	    caph_rights_limit(STDOUT_FILENO, &rights) < 0 ||
	    caph_rights_limit(STDERR_FILENO, &rights) < 0 ||
	    caph_ioctls_limit(STDIN_FILENO, cmds, nitems(cmds)) < 0 ||
	    caph_ioctls_limit(STDOUT_FILENO, cmds, nitems(cmds)) < 0 ||
	    caph_ioctls_limit(STDERR_FILENO, cmds, nitems(cmds)) < 0 ||
	    caph_fcntls_limit(STDIN_FILENO, CAP_FCNTL_GETFL) < 0 ||
	    caph_fcntls_limit(STDOUT_FILENO, CAP_FCNTL_GETFL) < 0 ||
	    caph_fcntls_limit(STDERR_FILENO, CAP_FCNTL_GETFL) < 0)
		err(1, "can't limit stdio rights");

	caph_cache_catpages();
	caph_cache_tzdata();

	/*
	 * Cache UTX database fds.
	 */
	setutxent();

	/*
	 * Determine our login name before we reopen() stdout
	 * and before entering capability sandbox.
	 */
	myuid = getuid();
	if ((login = getlogin()) == NULL) {
		if ((pwd = getpwuid(myuid)))
			login = pwd->pw_name;
		else
			login = "???";
	}

	if (caph_enter() < 0)
		err(1, "cap_enter");

	while (getopt(argc, argv, "") != -1)
		usage();
	argc -= optind;
	argv += optind;

	/* check that sender has write enabled */
	if (isatty(fileno(stdin)))
		myttyfd = fileno(stdin);
	else if (isatty(fileno(stdout)))
		myttyfd = fileno(stdout);
	else if (isatty(fileno(stderr)))
		myttyfd = fileno(stderr);
	else
		errx(1, "can't find your tty");
	if (!(mytty = ttyname(myttyfd)))
		errx(1, "can't find your tty's name");
	if (!strncmp(mytty, _PATH_DEV, strlen(_PATH_DEV)))
		mytty += strlen(_PATH_DEV);
	if (term_chk(devfd, mytty, &msgsok, &atime, 1))
		exit(1);
	if (!msgsok)
		errx(1, "you have write permission turned off");

	/* check args */
	switch (argc) {
	case 1:
		search_utmp(devfd, argv[0], tty, mytty, myuid);
		do_write(devfd, tty, mytty, login);
		break;
	case 2:
		if (!strncmp(argv[1], _PATH_DEV, strlen(_PATH_DEV)))
			argv[1] += strlen(_PATH_DEV);
		if (utmp_chk(argv[0], argv[1]))
			errx(1, "%s is not logged in on %s", argv[0], argv[1]);
		if (term_chk(devfd, argv[1], &msgsok, &atime, 1))
			exit(1);
		if (myuid && !msgsok)
			errx(1, "%s has messages disabled on %s", argv[0], argv[1]);
		do_write(devfd, argv[1], mytty, login);
		break;
	default:
		usage();
	}
	done(0);
	return (0);
}