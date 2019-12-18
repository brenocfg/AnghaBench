#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ D_BRIEF ; 
 scalar_t__ D_CONTEXT ; 
 scalar_t__ D_EDIT ; 
 int D_EXPANDTABS ; 
 int D_FOLDBLANKS ; 
 int D_FORCEASCII ; 
 scalar_t__ D_GFORMAT ; 
 scalar_t__ D_IFDEF ; 
 int D_IGNOREBLANKS ; 
 int D_IGNORECASE ; 
 int D_MINIMAL ; 
 scalar_t__ D_NORMAL ; 
 scalar_t__ D_NREVERSE ; 
 int D_PROTOTYPE ; 
 scalar_t__ D_REVERSE ; 
 int D_SKIPBLANKLINES ; 
 int D_STRIPCR ; 
 scalar_t__ D_UNIFIED ; 
 int INT_MAX ; 
 int Nflag ; 
 int /*<<< orphan*/  OPTIONS ; 
#define  OPT_CHANGED_GROUP_FORMAT 134 
#define  OPT_HORIZON_LINES 133 
#define  OPT_IGN_FN_CASE 132 
#define  OPT_NORMAL 131 
#define  OPT_NO_IGN_FN_CASE 130 
#define  OPT_STRIPCR 129 
#define  OPT_TSIZE 128 
 int Pflag ; 
 int REG_EXTENDED ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int Tflag ; 
 int cflag ; 
 int diff_context ; 
 scalar_t__ diff_format ; 
 int /*<<< orphan*/  diffdir (char*,char*,int) ; 
 int /*<<< orphan*/  diffreg (char*,char*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int getopt_long (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * group_format ; 
 int /*<<< orphan*/ * ifdefname ; 
 int ignore_file_case ; 
 char* ignore_pats ; 
 int /*<<< orphan*/  ignore_re ; 
 int /*<<< orphan*/  isdigit (int) ; 
 int /*<<< orphan*/ ** label ; 
 int lflag ; 
 int /*<<< orphan*/  longopts ; 
 int /*<<< orphan*/ * optarg ; 
 int optind ; 
 int pledge (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_status (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  push_excludes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_ignore_pats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_excludes_file (int /*<<< orphan*/ *) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int rflag ; 
 int /*<<< orphan*/  set_argstr (char**,char**) ; 
 int sflag ; 
 char* splice (char*,char*) ; 
 int /*<<< orphan*/ * start ; 
 scalar_t__ stat (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  status ; 
 TYPE_1__ stb1 ; 
 TYPE_1__ stb2 ; 
 scalar_t__ strcmp (char*,char*) ; 
 long strtol (int /*<<< orphan*/ *,char**,int) ; 
 scalar_t__ strtonum (int /*<<< orphan*/ *,int,int,char const**) ; 
 int tabsize ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char **argv)
{
	const char *errstr = NULL;
	char *ep, **oargv;
	long  l;
	int   ch, dflags, lastch, gotstdin, prevoptind, newarg;

	oargv = argv;
	gotstdin = 0;
	dflags = 0;
	lastch = '\0';
	prevoptind = 1;
	newarg = 1;
	diff_context = 3;
	diff_format = 0;
	while ((ch = getopt_long(argc, argv, OPTIONS, longopts, NULL)) != -1) {
		switch (ch) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			if (newarg)
				usage();	/* disallow -[0-9]+ */
			else if (lastch == 'c' || lastch == 'u')
				diff_context = 0;
			else if (!isdigit(lastch) || diff_context > INT_MAX / 10)
				usage();
			diff_context = (diff_context * 10) + (ch - '0');
			break;
		case 'a':
			dflags |= D_FORCEASCII;
			break;
		case 'b':
			dflags |= D_FOLDBLANKS;
			break;
		case 'C':
		case 'c':
			cflag = 1;
			diff_format = D_CONTEXT;
			if (optarg != NULL) {
				l = strtol(optarg, &ep, 10);
				if (*ep != '\0' || l < 0 || l >= INT_MAX)
					usage();
				diff_context = (int)l;
			}
			break;
		case 'd':
			dflags |= D_MINIMAL;
			break;
		case 'D':
			diff_format = D_IFDEF;
			ifdefname = optarg;
			break;
		case 'e':
			diff_format = D_EDIT;
			break;
		case 'f':
			diff_format = D_REVERSE;
			break;
		case 'H':
			/* ignore but needed for compatibility with GNU diff */
			break;
		case 'h':
			/* silently ignore for backwards compatibility */
			break;
		case 'B':
			dflags |= D_SKIPBLANKLINES;
			break;
		case 'I':
			push_ignore_pats(optarg);
			break;
		case 'i':
			dflags |= D_IGNORECASE;
			break;
		case 'L':
			if (label[0] == NULL)
				label[0] = optarg;
			else if (label[1] == NULL)
				label[1] = optarg;
			else
				usage();
			break;
		case 'l':
			lflag = 1;
			break;
		case 'N':
			Nflag = 1;
			break;
		case 'n':
			diff_format = D_NREVERSE;
			break;
		case 'p':
			if (diff_format == 0)
				diff_format = D_CONTEXT;
			dflags |= D_PROTOTYPE;
			break;
		case 'P':
			Pflag = 1;
			break;
		case 'r':
			rflag = 1;
			break;
		case 'q':
			diff_format = D_BRIEF;
			break;
		case 'S':
			start = optarg;
			break;
		case 's':
			sflag = 1;
			break;
		case 'T':
			Tflag = 1;
			break;
		case 't':
			dflags |= D_EXPANDTABS;
			break;
		case 'U':
		case 'u':
			diff_format = D_UNIFIED;
			if (optarg != NULL) {
				l = strtol(optarg, &ep, 10);
				if (*ep != '\0' || l < 0 || l >= INT_MAX)
					usage();
				diff_context = (int)l;
			}
			break;
		case 'w':
			dflags |= D_IGNOREBLANKS;
			break;
		case 'X':
			read_excludes_file(optarg);
			break;
		case 'x':
			push_excludes(optarg);
			break;
		case OPT_CHANGED_GROUP_FORMAT:
			diff_format = D_GFORMAT;
			group_format = optarg;
			break;
		case OPT_HORIZON_LINES:
			break; /* XXX TODO for compatibility with GNU diff3 */
		case OPT_IGN_FN_CASE:
			ignore_file_case = 1;
			break;
		case OPT_NO_IGN_FN_CASE:
			ignore_file_case = 0;
			break;
		case OPT_NORMAL:
			diff_format = D_NORMAL;
			break;
		case OPT_TSIZE:
			tabsize = (int) strtonum(optarg, 1, INT_MAX, &errstr);
			if (errstr) {
				warnx("Invalid argument for tabsize");
				usage();
			}
			break;
		case OPT_STRIPCR:
			dflags |= D_STRIPCR;
			break;
		default:
			usage();
			break;
		}
		lastch = ch;
		newarg = optind != prevoptind;
		prevoptind = optind;
	}
	argc -= optind;
	argv += optind;

#ifdef __OpenBSD__
	if (pledge("stdio rpath tmppath", NULL) == -1)
		err(2, "pledge");
#endif

	/*
	 * Do sanity checks, fill in stb1 and stb2 and call the appropriate
	 * driver routine.  Both drivers use the contents of stb1 and stb2.
	 */
	if (argc != 2)
		usage();
	if (ignore_pats != NULL) {
		char buf[BUFSIZ];
		int error;

		if ((error = regcomp(&ignore_re, ignore_pats,
				     REG_NEWLINE | REG_EXTENDED)) != 0) {
			regerror(error, &ignore_re, buf, sizeof(buf));
			if (*ignore_pats != '\0')
				errx(2, "%s: %s", ignore_pats, buf);
			else
				errx(2, "%s", buf);
		}
	}
	if (strcmp(argv[0], "-") == 0) {
		fstat(STDIN_FILENO, &stb1);
		gotstdin = 1;
	} else if (stat(argv[0], &stb1) != 0)
		err(2, "%s", argv[0]);
	if (strcmp(argv[1], "-") == 0) {
		fstat(STDIN_FILENO, &stb2);
		gotstdin = 1;
	} else if (stat(argv[1], &stb2) != 0)
		err(2, "%s", argv[1]);
	if (gotstdin && (S_ISDIR(stb1.st_mode) || S_ISDIR(stb2.st_mode)))
		errx(2, "can't compare - to a directory");
	set_argstr(oargv, argv);
	if (S_ISDIR(stb1.st_mode) && S_ISDIR(stb2.st_mode)) {
		if (diff_format == D_IFDEF)
			errx(2, "-D option not supported with directories");
		diffdir(argv[0], argv[1], dflags);
	} else {
		if (S_ISDIR(stb1.st_mode)) {
			argv[0] = splice(argv[0], argv[1]);
			if (stat(argv[0], &stb1) < 0)
				err(2, "%s", argv[0]);
		}
		if (S_ISDIR(stb2.st_mode)) {
			argv[1] = splice(argv[1], argv[0]);
			if (stat(argv[1], &stb2) < 0)
				err(2, "%s", argv[1]);
		}
		print_status(diffreg(argv[0], argv[1], dflags, 1), argv[0],
		    argv[1], "");
	}
	exit(status);
}