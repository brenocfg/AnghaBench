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
 int FTS_COMFOLLOW ; 
 int FTS_LOGICAL ; 
 int FTS_NOCHDIR ; 
 int FTS_NOSTAT ; 
 int FTS_PHYSICAL ; 
 int FTS_XDEV ; 
 int /*<<< orphan*/  LC_ALL ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 int /*<<< orphan*/  dotfd ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_execute (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  find_formplan (char**) ; 
 int ftsoptions ; 
 int getopt (int,char**,char*) ; 
 int isdepth ; 
 int issort ; 
 int isxargs ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  regexp_flags ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	char **p, **start;
	int Hflag, Lflag, ch;

	(void)setlocale(LC_ALL, "");

	(void)time(&now);	/* initialize the time-of-day */

	p = start = argv;
	Hflag = Lflag = 0;
	ftsoptions = FTS_NOSTAT | FTS_PHYSICAL;
	while ((ch = getopt(argc, argv, "EHLPXdf:sx")) != -1)
		switch (ch) {
		case 'E':
			regexp_flags |= REG_EXTENDED;
			break;
		case 'H':
			Hflag = 1;
			Lflag = 0;
			break;
		case 'L':
			Lflag = 1;
			Hflag = 0;
			break;
		case 'P':
			Hflag = Lflag = 0;
			break;
		case 'X':
			isxargs = 1;
			break;
		case 'd':
			isdepth = 1;
			break;
		case 'f':
			*p++ = optarg;
			break;
		case 's':
			issort = 1;
			break;
		case 'x':
			ftsoptions |= FTS_XDEV;
			break;
		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (Hflag)
		ftsoptions |= FTS_COMFOLLOW;
	if (Lflag) {
		ftsoptions &= ~FTS_PHYSICAL;
		ftsoptions |= FTS_LOGICAL;
	}

	/*
	 * Find first option to delimit the file list.  The first argument
	 * that starts with a -, or is a ! or a ( must be interpreted as a
	 * part of the find expression, according to POSIX .2.
	 */
	for (; *argv != NULL; *p++ = *argv++) {
		if (argv[0][0] == '-')
			break;
		if ((argv[0][0] == '!' || argv[0][0] == '(') &&
		    argv[0][1] == '\0')
			break;
	}

	if (p == start)
		usage();
	*p = NULL;

	if ((dotfd = open(".", O_RDONLY | O_CLOEXEC, 0)) < 0)
		ftsoptions |= FTS_NOCHDIR;

	exit(find_execute(find_formplan(argv), start));
}