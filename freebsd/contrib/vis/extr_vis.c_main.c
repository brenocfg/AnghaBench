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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int VIS_CSTYLE ; 
 int VIS_HTTPSTYLE ; 
 int VIS_MIMESTYLE ; 
 int VIS_NOSLASH ; 
 int VIS_OCTAL ; 
 int VIS_SAFE ; 
 int VIS_TAB ; 
 int VIS_WHITE ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int eflags ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  extra ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fold ; 
 int foldwidth ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  markeol ; 
 int /*<<< orphan*/  none ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char *argv[])
{
	FILE *fp;
	int ch;
	int rval;

	while ((ch = getopt(argc, argv, "bcde:F:fhlmnostw")) != -1)
		switch((char)ch) {
		case 'b':
			eflags |= VIS_NOSLASH;
			break;
		case 'c':
			eflags |= VIS_CSTYLE;
			break;
#ifdef DEBUG
		case 'd':
			debug++;
			break;
#endif
		case 'e':
			extra = optarg;
			break;
		case 'F':
			if ((foldwidth = atoi(optarg)) < 5) {
				errx(1, "can't fold lines to less than 5 cols");
				/* NOTREACHED */
			}
			markeol++;
			break;
		case 'f':
			fold++;		/* fold output lines to 80 cols */
			break;		/* using hidden newline */
		case 'h':
			eflags |= VIS_HTTPSTYLE;
			break;
		case 'l':
			markeol++;	/* mark end of line with \$ */
			break;
		case 'm':
			eflags |= VIS_MIMESTYLE;
			if (foldwidth == 80)
				foldwidth = 76;
			break;
		case 'n':
			none++;
			break;
		case 'o':
			eflags |= VIS_OCTAL;
			break;
		case 's':
			eflags |= VIS_SAFE;
			break;
		case 't':
			eflags |= VIS_TAB;
			break;
		case 'w':
			eflags |= VIS_WHITE;
			break;
		case '?':
		default:
			(void)fprintf(stderr, 
			    "Usage: %s [-bcfhlmnostw] [-e extra]" 
			    " [-F foldwidth] [file ...]\n", getprogname());
			return 1;
		}

	if ((eflags & (VIS_HTTPSTYLE|VIS_MIMESTYLE)) ==
	    (VIS_HTTPSTYLE|VIS_MIMESTYLE))
		errx(1, "Can't specify -m and -h at the same time");

	argc -= optind;
	argv += optind;

	rval = 0;

	if (*argv)
		while (*argv) {
			if ((fp = fopen(*argv, "r")) != NULL) {
				process(fp);
				(void)fclose(fp);
			} else {
				warn("%s", *argv);
				rval = 1;
			}
			argv++;
		}
	else
		process(stdin);
	return rval;
}