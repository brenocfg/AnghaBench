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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  ExitProgram (int) ; 
 int FALSE ; 
 scalar_t__ OK ; 
 scalar_t__ SIZEOF (char**) ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int TRUE ; 
 int /*<<< orphan*/  UChar (char) ; 
 char* _nc_rootname (char*) ; 
 int /*<<< orphan*/  check_aliases (char*) ; 
 int /*<<< orphan*/  curses_version () ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ is_init ; 
 scalar_t__ is_reset ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 char* prg_name ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quit (int,char*,...) ; 
 scalar_t__ setupterm (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ tput (int,char**) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  use_env (int) ; 

int
main(int argc, char **argv)
{
    char *term;
    int errret;
    bool cmdline = TRUE;
    int c;
    char buf[BUFSIZ];
    int result = 0;

    check_aliases(prg_name = _nc_rootname(argv[0]));

    term = getenv("TERM");

    while ((c = getopt(argc, argv, "ST:V")) != -1) {
	switch (c) {
	case 'S':
	    cmdline = FALSE;
	    break;
	case 'T':
	    use_env(FALSE);
	    term = optarg;
	    break;
	case 'V':
	    puts(curses_version());
	    ExitProgram(EXIT_SUCCESS);
	default:
	    usage();
	    /* NOTREACHED */
	}
    }

    /*
     * Modify the argument list to omit the options we processed.
     */
    if (is_reset || is_init) {
	if (optind-- < argc) {
	    argc -= optind;
	    argv += optind;
	}
	argv[0] = prg_name;
    } else {
	argc -= optind;
	argv += optind;
    }

    if (term == 0 || *term == '\0')
	quit(2, "No value for $TERM and no -T specified");

    if (setupterm(term, STDOUT_FILENO, &errret) != OK && errret <= 0)
	quit(3, "unknown terminal \"%s\"", term);

    if (cmdline) {
	if ((argc <= 0) && !is_reset && !is_init)
	    usage();
	ExitProgram(tput(argc, argv));
    }

    while (fgets(buf, sizeof(buf), stdin) != 0) {
	char *argvec[16];	/* command, 9 parms, null, & slop */
	int argnum = 0;
	char *cp;

	/* crack the argument list into a dope vector */
	for (cp = buf; *cp; cp++) {
	    if (isspace(UChar(*cp))) {
		*cp = '\0';
	    } else if (cp == buf || cp[-1] == 0) {
		argvec[argnum++] = cp;
		if (argnum >= (int) SIZEOF(argvec) - 1)
		    break;
	    }
	}
	argvec[argnum] = 0;

	if (argnum != 0
	    && tput(argnum, argvec) != 0) {
	    if (result == 0)
		result = 4;	/* will return value >4 */
	    ++result;
	}
    }

    ExitProgram(result);
}