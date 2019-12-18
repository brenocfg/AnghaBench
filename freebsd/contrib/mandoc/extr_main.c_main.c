#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct winsize {int ws_col; } ;
struct tag_files {char* tagname; int /*<<< orphan*/  ofd; scalar_t__ tcpgid; int /*<<< orphan*/  ofn; } ;
struct TYPE_5__ {int synopsisonly; int width; int indent; char* tag; int /*<<< orphan*/  noval; } ;
struct TYPE_4__ {int /*<<< orphan*/ * paths; } ;
struct mansearch {char* outkey; int argmode; int outtype; char* os_s; char* arch; char* sec; int firstmatch; int /*<<< orphan*/  mp; int /*<<< orphan*/ * outdata; scalar_t__ wstop; TYPE_2__ output; TYPE_1__ manpath; int /*<<< orphan*/  os_e; TYPE_2__* outopts; } ;
struct manpage {char* file; char* names; char* output; size_t ipath; int sec; scalar_t__ form; scalar_t__ bits; } ;
struct manconf {char* outkey; int argmode; int outtype; char* os_s; char* arch; char* sec; int firstmatch; int /*<<< orphan*/  mp; int /*<<< orphan*/ * outdata; scalar_t__ wstop; TYPE_2__ output; TYPE_1__ manpath; int /*<<< orphan*/  os_e; TYPE_2__* outopts; } ;
struct curparse {char* outkey; int argmode; int outtype; char* os_s; char* arch; char* sec; int firstmatch; int /*<<< orphan*/  mp; int /*<<< orphan*/ * outdata; scalar_t__ wstop; TYPE_2__ output; TYPE_1__ manpath; int /*<<< orphan*/  os_e; TYPE_2__* outopts; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ pid_t ;
typedef  enum outmode { ____Placeholder_outmode } outmode ;
typedef  int /*<<< orphan*/  conf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* ARG_EXPR ; 
#define  ARG_FILE 135 
#define  ARG_NAME 134 
 void* ARG_WORD ; 
 char* BINM_APROPOS ; 
 char* BINM_MAKEWHATIS ; 
 char* BINM_MAN ; 
 char* BINM_WHATIS ; 
 scalar_t__ EINTR ; 
 scalar_t__ FORM_SRC ; 
 char* MACHINE ; 
 int /*<<< orphan*/  MANDOCERR_BADARG_BAD ; 
 int /*<<< orphan*/  MANDOCERR_BADARG_DUPE ; 
 int /*<<< orphan*/  MANDOCERR_BASE ; 
 int /*<<< orphan*/  MANDOCERR_OPEN ; 
 int /*<<< orphan*/  MANDOCERR_PLEDGE ; 
 int /*<<< orphan*/  MANDOCERR_WAIT ; 
 int /*<<< orphan*/  MANDOCERR_WRITE ; 
 int /*<<< orphan*/  MANDOCLEVEL_BADARG ; 
 scalar_t__ MANDOCLEVEL_OK ; 
 scalar_t__ MANDOCLEVEL_SYSERR ; 
 int MPARSE_LATIN1 ; 
 int MPARSE_MAN ; 
 int MPARSE_MDOC ; 
 int MPARSE_SO ; 
 int MPARSE_UTF8 ; 
 int MPARSE_VALIDATE ; 
 int OUTMODE_ALL ; 
 int OUTMODE_DEF ; 
 int OUTMODE_FLN ; 
 int OUTMODE_LST ; 
 int OUTMODE_ONE ; 
#define  OUTT_ASCII 133 
#define  OUTT_HTML 132 
 int OUTT_LINT ; 
#define  OUTT_LOCALE 131 
 int OUTT_MAN ; 
 int OUTT_MARKDOWN ; 
#define  OUTT_PDF 130 
#define  OUTT_PS 129 
 int OUTT_TREE ; 
#define  OUTT_UTF8 128 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  SANDBOX_NAMED ; 
 int SIGCONT ; 
 int SIGSTOP ; 
 int SIGTTIN ; 
 size_t SIZE_MAX ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 int WSTOPSIG (int) ; 
 int /*<<< orphan*/  WUNTRACED ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ascii_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fchdir (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fs_search (struct mansearch*,TYPE_1__*,int,char**,struct manpage**,size_t*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getpgid (int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  getppid () ; 
 char* getprogname () ; 
 char** help_argv ; 
 int /*<<< orphan*/  html_free (int /*<<< orphan*/ *) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 scalar_t__ isalpha (unsigned char) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  kSBXProfileNoInternet ; 
 int /*<<< orphan*/  kill (scalar_t__,int) ; 
 int /*<<< orphan*/  manconf_free (struct mansearch*) ; 
 int manconf_output (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manconf_parse (struct mansearch*,char*,char*,char*) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ mandoc_msg_getrc () ; 
 int /*<<< orphan*/  mandoc_msg_setinfilename (char const*) ; 
 int /*<<< orphan*/  mandoc_msg_setmin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mandoc_msg_setoutfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mandoc_msg_setrc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mandoc_msg_summary () ; 
 struct manpage* mandoc_reallocarray (struct manpage*,size_t,int) ; 
 void* mandoc_strdup (char*) ; 
 int /*<<< orphan*/  mandoc_xr_free () ; 
 int mandocdb (int,char**) ; 
 int /*<<< orphan*/  mansearch (struct mansearch*,TYPE_1__*,int,char**,struct manpage**,size_t*) ; 
 int /*<<< orphan*/  mansearch_free (struct manpage*,size_t) ; 
 int /*<<< orphan*/  mchars_alloc () ; 
 int /*<<< orphan*/  mchars_free () ; 
 int /*<<< orphan*/  memset (struct mansearch*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mparse_alloc (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mparse_free (int /*<<< orphan*/ ) ; 
 int mparse_open (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mparse_reset (int /*<<< orphan*/ ) ; 
 int open (char*,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  outdata_alloc (struct mansearch*) ; 
 int /*<<< orphan*/  parse (struct mansearch*,int,char const*) ; 
 int /*<<< orphan*/  passthrough (int,int) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int pledge (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  pspdf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int sandbox_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* sec_prios ; 
 int /*<<< orphan*/  setprogname (char const*) ; 
 scalar_t__ spawn_pager (struct tag_files*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcspn (char const*,char*) ; 
 char* strdup (char*) ; 
 char* strerror (scalar_t__) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  strsep (char**,char*) ; 
 struct tag_files* tag_init () ; 
 int /*<<< orphan*/  tag_unlink () ; 
 int /*<<< orphan*/  tag_write () ; 
 scalar_t__ tcgetpgrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcsetpgrp (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  terminal_sepline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int woptions (struct mansearch*,char*) ; 

int
main(int argc, char *argv[])
{
	struct manconf	 conf;
	struct mansearch search;
	struct curparse	 curp;
	struct winsize	 ws;
	struct tag_files *tag_files;
	struct manpage	*res, *resp;
	const char	*progname, *sec, *thisarg;
	char		*conf_file, *defpaths, *auxpaths;
	char		*oarg, *tagarg;
	unsigned char	*uc;
	size_t		 i, sz, ssz;
	int		 prio, best_prio;
	enum outmode	 outmode;
	int		 fd, startdir;
	int		 show_usage;
	int		 options;
	int		 use_pager;
	int		 status, signum;
	int		 c;
	pid_t		 pager_pid, tc_pgid, man_pgid, pid;

#if HAVE_PROGNAME
	progname = getprogname();
#else
	if (argc < 1)
		progname = mandoc_strdup("mandoc");
	else if ((progname = strrchr(argv[0], '/')) == NULL)
		progname = argv[0];
	else
		++progname;
	setprogname(progname);
#endif

	mandoc_msg_setoutfile(stderr);
	if (strncmp(progname, "mandocdb", 8) == 0 ||
	    strcmp(progname, BINM_MAKEWHATIS) == 0)
		return mandocdb(argc, argv);

#if HAVE_PLEDGE
	if (pledge("stdio rpath tmppath tty proc exec", NULL) == -1) {
		mandoc_msg(MANDOCERR_PLEDGE, 0, 0, "%s", strerror(errno));
		return mandoc_msg_getrc();
	}
#endif
#if HAVE_SANDBOX_INIT
	if (sandbox_init(kSBXProfileNoInternet, SANDBOX_NAMED, NULL) == -1)
		errx((int)MANDOCLEVEL_SYSERR, "sandbox_init");
#endif

	/* Search options. */

	memset(&conf, 0, sizeof(conf));
	conf_file = defpaths = NULL;
	auxpaths = NULL;

	memset(&search, 0, sizeof(struct mansearch));
	search.outkey = "Nd";
	oarg = NULL;

	if (strcmp(progname, BINM_MAN) == 0)
		search.argmode = ARG_NAME;
	else if (strcmp(progname, BINM_APROPOS) == 0)
		search.argmode = ARG_EXPR;
	else if (strcmp(progname, BINM_WHATIS) == 0)
		search.argmode = ARG_WORD;
	else if (strncmp(progname, "help", 4) == 0)
		search.argmode = ARG_NAME;
	else
		search.argmode = ARG_FILE;

	/* Parser and formatter options. */

	memset(&curp, 0, sizeof(struct curparse));
	curp.outtype = OUTT_LOCALE;
	curp.outopts = &conf.output;
	options = MPARSE_SO | MPARSE_UTF8 | MPARSE_LATIN1;

	use_pager = 1;
	tag_files = NULL;
	show_usage = 0;
	outmode = OUTMODE_DEF;

	while ((c = getopt(argc, argv,
	    "aC:cfhI:iK:klM:m:O:S:s:T:VW:w")) != -1) {
		if (c == 'i' && search.argmode == ARG_EXPR) {
			optind--;
			break;
		}
		switch (c) {
		case 'a':
			outmode = OUTMODE_ALL;
			break;
		case 'C':
			conf_file = optarg;
			break;
		case 'c':
			use_pager = 0;
			break;
		case 'f':
			search.argmode = ARG_WORD;
			break;
		case 'h':
			conf.output.synopsisonly = 1;
			use_pager = 0;
			outmode = OUTMODE_ALL;
			break;
		case 'I':
			if (strncmp(optarg, "os=", 3) != 0) {
				mandoc_msg(MANDOCERR_BADARG_BAD, 0, 0,
				    "-I %s", optarg);
				return mandoc_msg_getrc();
			}
			if (curp.os_s != NULL) {
				mandoc_msg(MANDOCERR_BADARG_DUPE, 0, 0,
				    "-I %s", optarg);
				return mandoc_msg_getrc();
			}
			curp.os_s = mandoc_strdup(optarg + 3);
			break;
		case 'K':
			options &= ~(MPARSE_UTF8 | MPARSE_LATIN1);
			if (strcmp(optarg, "utf-8") == 0)
				options |=  MPARSE_UTF8;
			else if (strcmp(optarg, "iso-8859-1") == 0)
				options |=  MPARSE_LATIN1;
			else if (strcmp(optarg, "us-ascii") != 0) {
				mandoc_msg(MANDOCERR_BADARG_BAD, 0, 0,
				    "-K %s", optarg);
				return mandoc_msg_getrc();
			}
			break;
		case 'k':
			search.argmode = ARG_EXPR;
			break;
		case 'l':
			search.argmode = ARG_FILE;
			outmode = OUTMODE_ALL;
			break;
		case 'M':
#ifdef __FreeBSD__
			defpaths = strdup(optarg);
			if (defpaths == NULL)
				err(1, "strdup");
#else
			defpaths = optarg;
#endif
			break;
		case 'm':
			auxpaths = optarg;
			break;
		case 'O':
			oarg = optarg;
			break;
		case 'S':
			search.arch = optarg;
			break;
		case 's':
			search.sec = optarg;
			break;
		case 'T':
			if (strcmp(optarg, "ascii") == 0)
				curp.outtype = OUTT_ASCII;
			else if (strcmp(optarg, "lint") == 0) {
				curp.outtype = OUTT_LINT;
				mandoc_msg_setoutfile(stdout);
				mandoc_msg_setmin(MANDOCERR_BASE);
			} else if (strcmp(optarg, "tree") == 0)
				curp.outtype = OUTT_TREE;
			else if (strcmp(optarg, "man") == 0)
				curp.outtype = OUTT_MAN;
			else if (strcmp(optarg, "html") == 0)
				curp.outtype = OUTT_HTML;
			else if (strcmp(optarg, "markdown") == 0)
				curp.outtype = OUTT_MARKDOWN;
			else if (strcmp(optarg, "utf8") == 0)
				curp.outtype = OUTT_UTF8;
			else if (strcmp(optarg, "locale") == 0)
				curp.outtype = OUTT_LOCALE;
			else if (strcmp(optarg, "ps") == 0)
				curp.outtype = OUTT_PS;
			else if (strcmp(optarg, "pdf") == 0)
				curp.outtype = OUTT_PDF;
			else {
				mandoc_msg(MANDOCERR_BADARG_BAD, 0, 0,
				    "-T %s", optarg);
				return mandoc_msg_getrc();
			}
			break;
		case 'W':
			if (woptions(&curp, optarg) == -1)
				return mandoc_msg_getrc();
			break;
		case 'w':
			outmode = OUTMODE_FLN;
			break;
		default:
			show_usage = 1;
			break;
		}
	}

	if (show_usage)
		usage(search.argmode);

	/* Postprocess options. */

	if (outmode == OUTMODE_DEF) {
		switch (search.argmode) {
		case ARG_FILE:
			outmode = OUTMODE_ALL;
			use_pager = 0;
			break;
		case ARG_NAME:
			outmode = OUTMODE_ONE;
			break;
		default:
			outmode = OUTMODE_LST;
			break;
		}
	}

	if (oarg != NULL) {
		if (outmode == OUTMODE_LST)
			search.outkey = oarg;
		else {
			while (oarg != NULL) {
				if (manconf_output(&conf.output,
				    strsep(&oarg, ","), 0) == -1)
					return mandoc_msg_getrc();
			}
		}
	}

	if (curp.outtype != OUTT_TREE || !curp.outopts->noval)
		options |= MPARSE_VALIDATE;

	if (outmode == OUTMODE_FLN ||
	    outmode == OUTMODE_LST ||
	    !isatty(STDOUT_FILENO))
		use_pager = 0;

	if (use_pager &&
	    (conf.output.width == 0 || conf.output.indent == 0) &&
	    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1 &&
	    ws.ws_col > 1) {
		if (conf.output.width == 0 && ws.ws_col < 79)
			conf.output.width = ws.ws_col - 1;
		if (conf.output.indent == 0 && ws.ws_col < 66)
			conf.output.indent = 3;
	}

#if HAVE_PLEDGE
	if (use_pager == 0) {
		if (pledge("stdio rpath", NULL) == -1) {
			mandoc_msg(MANDOCERR_PLEDGE, 0, 0,
			    "%s", strerror(errno));
			return mandoc_msg_getrc();
		}
	}
#endif

	/* Parse arguments. */

	if (argc > 0) {
		argc -= optind;
		argv += optind;
	}
	resp = NULL;

	/*
	 * Quirks for help(1)
	 * and for a man(1) section argument without -s.
	 */

	if (search.argmode == ARG_NAME) {
		if (*progname == 'h') {
			if (argc == 0) {
				argv = help_argv;
				argc = 1;
			}
		} else if (argc > 1 &&
		    ((uc = (unsigned char *)argv[0]) != NULL) &&
		    ((isdigit(uc[0]) && (uc[1] == '\0' ||
		      isalpha(uc[1]))) ||
		     (uc[0] == 'n' && uc[1] == '\0'))) {
			search.sec = (char *)uc;
			argv++;
			argc--;
		}
		if (search.arch == NULL)
			search.arch = getenv("MACHINE");
#ifdef MACHINE
		if (search.arch == NULL)
			search.arch = MACHINE;
#endif
	}

	/*
	 * Use the first argument for -O tag in addition to
	 * using it as a search term for man(1) or apropos(1).
	 */

	if (conf.output.tag != NULL && *conf.output.tag == '\0') {
		tagarg = argc > 0 && search.argmode == ARG_EXPR ?
		    strchr(*argv, '=') : NULL;
		conf.output.tag = tagarg == NULL ? *argv : tagarg + 1;
	}

	/* man(1), whatis(1), apropos(1) */

	if (search.argmode != ARG_FILE) {
		if (search.argmode == ARG_NAME &&
		    outmode == OUTMODE_ONE)
			search.firstmatch = 1;

#ifdef __FreeBSD__
		/*
		 * Use manpath(1) to populate defpaths if -M is not specified.
		 * Don't treat any failures as fatal.
		 */
		if (defpaths == NULL) {
			FILE *fp;
			size_t linecap = 0;
			ssize_t linelen;

			if ((fp = popen("/usr/bin/manpath -q", "r")) != NULL) {
				if ((linelen = getline(&defpaths,
				    &linecap, fp)) > 0) {
					/* Strip trailing newline */
					defpaths[linelen - 1] = '\0';
				}
				pclose(fp);
			}
		}
#endif

		/* Access the mandoc database. */

		manconf_parse(&conf, conf_file, defpaths, auxpaths);
#ifdef __FreeBSD__
		free(defpaths);
#endif

		if ( ! mansearch(&search, &conf.manpath,
		    argc, argv, &res, &sz))
			usage(search.argmode);

		if (sz == 0 && search.argmode == ARG_NAME)
			(void)fs_search(&search, &conf.manpath,
			    argc, argv, &res, &sz);

		if (search.argmode == ARG_NAME) {
			for (c = 0; c < argc; c++) {
				if (strchr(argv[c], '/') == NULL)
					continue;
				if (access(argv[c], R_OK) == -1) {
					mandoc_msg_setinfilename(argv[c]);
					mandoc_msg(MANDOCERR_BADARG_BAD,
					    0, 0, "%s", strerror(errno));
					mandoc_msg_setinfilename(NULL);
					continue;
				}
				res = mandoc_reallocarray(res,
				    sz + 1, sizeof(*res));
				res[sz].file = mandoc_strdup(argv[c]);
				res[sz].names = NULL;
				res[sz].output = NULL;
				res[sz].bits = 0;
				res[sz].ipath = SIZE_MAX;
				res[sz].sec = 10;
				res[sz].form = FORM_SRC;
				sz++;
			}
		}

		if (sz == 0) {
			if (search.argmode != ARG_NAME)
				warnx("nothing appropriate");
			mandoc_msg_setrc(MANDOCLEVEL_BADARG);
			goto out;
		}

		/*
		 * For standard man(1) and -a output mode,
		 * prepare for copying filename pointers
		 * into the program parameter array.
		 */

		if (outmode == OUTMODE_ONE) {
			argc = 1;
			best_prio = 40;
		} else if (outmode == OUTMODE_ALL)
			argc = (int)sz;

		/* Iterate all matching manuals. */

		resp = res;
		for (i = 0; i < sz; i++) {
			if (outmode == OUTMODE_FLN)
				puts(res[i].file);
			else if (outmode == OUTMODE_LST)
				printf("%s - %s\n", res[i].names,
				    res[i].output == NULL ? "" :
				    res[i].output);
			else if (outmode == OUTMODE_ONE) {
				/* Search for the best section. */
				sec = res[i].file;
				sec += strcspn(sec, "123456789");
				if (sec[0] == '\0')
					continue; /* No section at all. */
				prio = sec_prios[sec[0] - '1'];
				if (search.sec != NULL) {
					ssz = strlen(search.sec);
					if (strncmp(sec, search.sec, ssz) == 0)
						sec += ssz;
				} else
					sec++; /* Prefer without suffix. */
				if (*sec != '/')
					prio += 10; /* Wrong dir name. */
				if (search.sec != NULL &&
				    (strlen(sec) <= ssz  + 3 ||
				     strcmp(sec + strlen(sec) - ssz,
				      search.sec) != 0))
					prio += 20; /* Wrong file ext. */
				if (prio >= best_prio)
					continue;
				best_prio = prio;
				resp = res + i;
			}
		}

		/*
		 * For man(1), -a and -i output mode, fall through
		 * to the main mandoc(1) code iterating files
		 * and running the parsers on each of them.
		 */

		if (outmode == OUTMODE_FLN || outmode == OUTMODE_LST)
			goto out;
	}

	/* mandoc(1) */

#if HAVE_PLEDGE
	if (use_pager) {
		if (pledge("stdio rpath tmppath tty proc exec", NULL) == -1) {
			mandoc_msg(MANDOCERR_PLEDGE, 0, 0,
			    "%s", strerror(errno));
			return mandoc_msg_getrc();
		}
	} else {
		if (pledge("stdio rpath", NULL) == -1) {
			mandoc_msg(MANDOCERR_PLEDGE, 0, 0,
			    "%s", strerror(errno));
			return mandoc_msg_getrc();
		}
	}
#endif

	if (search.argmode == ARG_FILE && auxpaths != NULL) {
		if (strcmp(auxpaths, "doc") == 0)
			options |= MPARSE_MDOC;
		else if (strcmp(auxpaths, "an") == 0)
			options |= MPARSE_MAN;
	}

	mchars_alloc();
	curp.mp = mparse_alloc(options, curp.os_e, curp.os_s);

	if (argc < 1) {
		if (use_pager) {
			tag_files = tag_init();
			if (tag_files != NULL)
				tag_files->tagname = conf.output.tag;
		}
		thisarg = "<stdin>";
		mandoc_msg_setinfilename(thisarg);
		parse(&curp, STDIN_FILENO, thisarg);
		mandoc_msg_setinfilename(NULL);
	}

	/*
	 * Remember the original working directory, if possible.
	 * This will be needed if some names on the command line
	 * are page names and some are relative file names.
	 * Do not error out if the current directory is not
	 * readable: Maybe it won't be needed after all.
	 */
	startdir = open(".", O_RDONLY | O_DIRECTORY);

	while (argc > 0) {

		/*
		 * Changing directories is not needed in ARG_FILE mode.
		 * Do it on a best-effort basis.  Even in case of
		 * failure, some functionality may still work.
		 */
		if (resp != NULL) {
			if (resp->ipath != SIZE_MAX)
				(void)chdir(conf.manpath.paths[resp->ipath]);
			else if (startdir != -1)
				(void)fchdir(startdir);
			thisarg = resp->file;
		} else
			thisarg = *argv;

		mandoc_msg_setinfilename(thisarg);
		fd = mparse_open(curp.mp, thisarg);
		if (fd != -1) {
			if (use_pager) {
				use_pager = 0;
				tag_files = tag_init();
				if (tag_files != NULL)
					tag_files->tagname = conf.output.tag;
			}

			if (resp == NULL || resp->form == FORM_SRC)
				parse(&curp, fd, thisarg);
			else
				passthrough(fd, conf.output.synopsisonly);

			if (ferror(stdout)) {
				if (tag_files != NULL) {
					mandoc_msg(MANDOCERR_WRITE, 0, 0,
					    "%s: %s", tag_files->ofn,
					    strerror(errno));
					tag_unlink();
					tag_files = NULL;
				} else
					mandoc_msg(MANDOCERR_WRITE, 0, 0,
					    "%s", strerror(errno));
				break;
			}

			if (argc > 1 && curp.outtype <= OUTT_UTF8) {
				if (curp.outdata == NULL)
					outdata_alloc(&curp);
				terminal_sepline(curp.outdata);
			}
		} else
			mandoc_msg(resp == NULL ? MANDOCERR_BADARG_BAD :
			    MANDOCERR_OPEN, 0, 0, "%s", strerror(errno));

		mandoc_msg_setinfilename(NULL);

		if (curp.wstop && mandoc_msg_getrc() != MANDOCLEVEL_OK)
			break;

		if (resp != NULL)
			resp++;
		else
			argv++;
		if (--argc)
			mparse_reset(curp.mp);
	}
	if (startdir != -1) {
		(void)fchdir(startdir);
		close(startdir);
	}

	if (curp.outdata != NULL) {
		switch (curp.outtype) {
		case OUTT_HTML:
			html_free(curp.outdata);
			break;
		case OUTT_UTF8:
		case OUTT_LOCALE:
		case OUTT_ASCII:
			ascii_free(curp.outdata);
			break;
		case OUTT_PDF:
		case OUTT_PS:
			pspdf_free(curp.outdata);
			break;
		default:
			break;
		}
	}
	mandoc_xr_free();
	mparse_free(curp.mp);
	mchars_free();

out:
	if (search.argmode != ARG_FILE) {
		manconf_free(&conf);
		mansearch_free(res, sz);
	}

	free(curp.os_s);

	/*
	 * When using a pager, finish writing both temporary files,
	 * fork it, wait for the user to close it, and clean up.
	 */

	if (tag_files != NULL) {
		fclose(stdout);
		tag_write();
		man_pgid = getpgid(0);
		tag_files->tcpgid = man_pgid == getpid() ?
		    getpgid(getppid()) : man_pgid;
		pager_pid = 0;
		signum = SIGSTOP;
		for (;;) {

			/* Stop here until moved to the foreground. */

			tc_pgid = tcgetpgrp(tag_files->ofd);
			if (tc_pgid != man_pgid) {
				if (tc_pgid == pager_pid) {
					(void)tcsetpgrp(tag_files->ofd,
					    man_pgid);
					if (signum == SIGTTIN)
						continue;
				} else
					tag_files->tcpgid = tc_pgid;
				kill(0, signum);
				continue;
			}

			/* Once in the foreground, activate the pager. */

			if (pager_pid) {
				(void)tcsetpgrp(tag_files->ofd, pager_pid);
				kill(pager_pid, SIGCONT);
			} else
				pager_pid = spawn_pager(tag_files);

			/* Wait for the pager to stop or exit. */

			while ((pid = waitpid(pager_pid, &status,
			    WUNTRACED)) == -1 && errno == EINTR)
				continue;

			if (pid == -1) {
				mandoc_msg(MANDOCERR_WAIT, 0, 0,
				    "%s", strerror(errno));
				break;
			}
			if (!WIFSTOPPED(status))
				break;

			signum = WSTOPSIG(status);
		}
		tag_unlink();
	} else if (curp.outtype != OUTT_LINT &&
	    (search.argmode == ARG_FILE || sz > 0))
		mandoc_msg_summary();

	return (int)mandoc_msg_getrc();
}