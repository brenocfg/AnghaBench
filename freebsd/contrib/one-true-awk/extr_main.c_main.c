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

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,...) ; 
 int /*<<< orphan*/ * FS ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  MAX_PFILE ; 
 int NSYMTAB ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  WARNING (char*,...) ; 
 int /*<<< orphan*/  arginit (int,char**) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  bracecheck () ; 
 char* cmdname ; 
 int compile_time ; 
 scalar_t__ dbg ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  envinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  environ ; 
 scalar_t__ errorflag ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fpecatch ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  isclvar (char*) ; 
 char* lexprog ; 
 int /*<<< orphan*/  makesymtab (int) ; 
 scalar_t__ npfile ; 
 char** pfile ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  qstring (char const*,char) ; 
 int /*<<< orphan*/  recinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recsize ; 
 int /*<<< orphan*/  run (int /*<<< orphan*/ ) ; 
 int safe ; 
 int /*<<< orphan*/  setclvar (char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int srand_seed ; 
 int /*<<< orphan*/  srandom (unsigned long) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  syminit () ; 
 int /*<<< orphan*/  symtab ; 
 char* version ; 
 int /*<<< orphan*/  winner ; 
 int /*<<< orphan*/ * yyin ; 
 int /*<<< orphan*/  yyparse () ; 

int main(int argc, char *argv[])
{
	const char *fs = NULL;

	setlocale(LC_CTYPE, "");
	setlocale(LC_COLLATE, "");
	setlocale(LC_NUMERIC, "C"); /* for parsing cmdline & prog */
	cmdname = argv[0];
	if (argc == 1) {
		fprintf(stderr, 
		  "usage: %s [-F fs] [-v var=value] [-f progfile | 'prog'] [file ...]\n", 
		  cmdname);
		exit(1);
	}
	signal(SIGFPE, fpecatch);
	/*signal(SIGSEGV, segvcatch); experiment */

	srand_seed = 1;
	srandom((unsigned long) srand_seed);

	yyin = NULL;
	symtab = makesymtab(NSYMTAB/NSYMTAB);
	while (argc > 1 && argv[1][0] == '-' && argv[1][1] != '\0') {
		if (strcmp(argv[1],"-version") == 0 || strcmp(argv[1],"--version") == 0) {
			printf("awk %s\n", version);
			exit(0);
			break;
		}
		if (strcmp(argv[1], "--") == 0) {	/* explicit end of args */
			argc--;
			argv++;
			break;
		}
		switch (argv[1][1]) {
		case 's':
			if (strcmp(argv[1], "-safe") == 0)
				safe = 1;
			break;
		case 'f':	/* next argument is program filename */
			if (argv[1][2] != 0) {  /* arg is -fsomething */
				if (npfile >= MAX_PFILE - 1)
					FATAL("too many -f options"); 
				pfile[npfile++] = &argv[1][2];
			} else {		/* arg is -f something */
				argc--; argv++;
				if (argc <= 1)
					FATAL("no program filename");
				if (npfile >= MAX_PFILE - 1)
					FATAL("too many -f options"); 
				pfile[npfile++] = argv[1];
			}
			break;
		case 'F':	/* set field separator */
			if (argv[1][2] != 0) {	/* arg is -Fsomething */
				if (argv[1][2] == 't' && argv[1][3] == 0)	/* wart: t=>\t */
					fs = "\t";
				else if (argv[1][2] != 0)
					fs = &argv[1][2];
			} else {		/* arg is -F something */
				argc--; argv++;
				if (argc > 1 && argv[1][0] == 't' && argv[1][1] == 0)	/* wart: t=>\t */
					fs = "\t";
				else if (argc > 1 && argv[1][0] != 0)
					fs = &argv[1][0];
			}
			if (fs == NULL || *fs == '\0')
				WARNING("field separator FS is empty");
			break;
		case 'v':	/* -v a=1 to be done NOW.  one -v for each */
			if (argv[1][2] != 0) {  /* arg is -vsomething */
				if (isclvar(&argv[1][2]))
					setclvar(&argv[1][2]);
				else
					FATAL("invalid -v option argument: %s", &argv[1][2]);
			} else {		/* arg is -v something */
				argc--; argv++;
				if (argc <= 1)
					FATAL("no variable name");
				if (isclvar(argv[1]))
					setclvar(argv[1]);
				else
					FATAL("invalid -v option argument: %s", argv[1]);
			}
			break;
		case 'd':
			dbg = atoi(&argv[1][2]);
			if (dbg == 0)
				dbg = 1;
			printf("awk %s\n", version);
			break;
		default:
			WARNING("unknown option %s ignored", argv[1]);
			break;
		}
		argc--;
		argv++;
	}
	/* argv[1] is now the first argument */
	if (npfile == 0) {	/* no -f; first argument is program */
		if (argc <= 1) {
			if (dbg)
				exit(0);
			FATAL("no program given");
		}
		   dprintf( ("program = |%s|\n", argv[1]) );
		lexprog = argv[1];
		argc--;
		argv++;
	}
	recinit(recsize);
	syminit();
	compile_time = 1;
	argv[0] = cmdname;	/* put prog name at front of arglist */
	   dprintf( ("argc=%d, argv[0]=%s\n", argc, argv[0]) );
	arginit(argc, argv);
	if (!safe)
		envinit(environ);
	yyparse();
	setlocale(LC_NUMERIC, ""); /* back to whatever it is locally */
	if (fs)
		*FS = qstring(fs, '\0');
	   dprintf( ("errorflag=%d\n", errorflag) );
	if (errorflag == 0) {
		compile_time = 0;
		run(winner);
	} else
		bracecheck();
	return(errorflag);
}