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
struct servent {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_dir; } ;
typedef  int /*<<< orphan*/  homedir ;

/* Variables and functions */
 int MaxPathLen ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SO_DEBUG ; 
 int autologin ; 
 int /*<<< orphan*/  cmdscanner (int) ; 
 scalar_t__ cpend ; 
 int crflag ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ debug_flag ; 
 int doglob ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ fromatty ; 
 int ftp_do_gss_bindings ; 
 scalar_t__ getarg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,int*) ; 
 int /*<<< orphan*/  getargs ; 
 scalar_t__ getprogname () ; 
 struct servent* getservbyname (char*,char*) ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ help_flag ; 
 char* home ; 
 int interactive ; 
 int /*<<< orphan*/  intr ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 struct passwd* k_getpwuid (int /*<<< orphan*/ ) ; 
 int lineedit ; 
 int /*<<< orphan*/  lostpeer ; 
 int /*<<< orphan*/  num_args ; 
 int /*<<< orphan*/  options ; 
 scalar_t__ passivemode ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 scalar_t__ proxy ; 
 int sendport ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpeer (int,char**) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  toplevel ; 
 int /*<<< orphan*/  usage (int) ; 
 int use_kerberos ; 
 int /*<<< orphan*/  verbose ; 
 scalar_t__ version_flag ; 

int
main(int argc, char **argv)
{
	int top;
	struct passwd *pw = NULL;
	char homedir[MaxPathLen];
	struct servent *sp;
	int optind = 0;

	setprogname(argv[0]);

	sp = getservbyname("ftp", "tcp");
	if (sp == 0)
		errx(1, "ftp/tcp: unknown service");
	doglob = 1;
	interactive = 1;
	autologin = 1;
	lineedit = 1;
	passivemode = 0; /* passive mode not active */
        use_kerberos = 1;
#ifdef KRB5
	ftp_do_gss_bindings = 1;
#endif

	if(getarg(getargs, num_args, argc, argv, &optind))
		usage(1);
	if(help_flag)
		usage(0);
	if(version_flag) {
		print_version(NULL);
		exit(0);
	}

	if (debug_flag) {
		options |= SO_DEBUG;
		debug++;
	}

	argc -= optind;
	argv += optind;

	fromatty = isatty(fileno(stdin));
	if (fromatty)
		verbose++;
	cpend = 0;	/* no pending replies */
	proxy = 0;	/* proxy not active */
	crflag = 1;	/* strip c.r. on ascii gets */
	sendport = -1;	/* not using ports */
	/*
	 * Set up the home directory in case we're globbing.
	 */
	pw = k_getpwuid(getuid());
	if (pw != NULL) {
		strlcpy(homedir, pw->pw_dir, sizeof(homedir));
		home = homedir;
	}
	if (argc > 0) {
	    char *xargv[5];

	    if (setjmp(toplevel))
		exit(0);
	    signal(SIGINT, intr);
	    signal(SIGPIPE, lostpeer);
	    xargv[0] = (char*)getprogname();
	    xargv[1] = argv[0];
	    xargv[2] = argv[1];
	    xargv[3] = argv[2];
	    xargv[4] = NULL;
	    setpeer(argc+1, xargv);
	}
	if(setjmp(toplevel) == 0)
	    top = 1;
	else
	    top = 0;
	if (top) {
	    signal(SIGINT, intr);
	    signal(SIGPIPE, lostpeer);
	}
	for (;;) {
	    cmdscanner(top);
	    top = 1;
	}
}